# This file is a custom exporter for blender compatible with the ConradEngine.
# Command line executable script.
# Automatically exports the current .blend file into a ConradEngine readable format WHEN EXECUTED.

import bpy
import bmesh
import os
import struct
import sys

OBJTYPE_STATIC = 0
OBJTYPE_DYNAMIC = 1
OBJTYPE_STREAM = 2

MESH_OBJECT_CODE = 0
MATERIAL_OBJECT_CODE = 1
LIGHT_OBJECT_CODE = 2
CAMERA_OBJECT_CODE = 3

VEC_ARRAY_OBJECT_CODE = 255
VEC_OBJECT_CODE = 254
STR_OBJECT_CODE = 253
IMG_OBJECT_CODE = 252

def triangulate_mesh(mesh):
    bm = bmesh.new()
    bm.from_mesh(mesh)
    
    bmesh.ops.triangulate(bm, faces=bm.faces[:], quad_method='BEAUTY', ngon_method='BEAUTY') # 'FIXED' for faster mode
    
    bm.to_mesh(mesh)
    bm.free()

class ConradExporter:
    def __init__(self, filetarget):
        self.filetarget = filetarget
        self.file = open(filetarget, 'wb') # write in bytes

    def writeInt(self, value): # 4 bytes written left to right
        l = list(struct.unpack('4B', struct.pack('I', value)))
        l.reverse()
        self.file.write(bytes(l))
        
    def writeFloat(self, value):
        l = list(struct.unpack('4B', struct.pack('f', value)))
        l.reverse()
        self.file.write(bytes(l))
        
    def writeChar(self, c):
        try:
            self.file.write(bytes(chr(c), 'utf-8'))
        except TypeError:
            self.file.write(bytes(c, 'utf-8'))        

        
    def writeString(self, string): # 4 bytes of meta
        self.writeInt(len(string)) # Size
        self.file.write(bytes(string, 'utf-8'))
        self.writeChar('\0')
                    
        
    def writeVec(self, vec): # 5 bytes of meta
        if len(vec) == 0:
            return
        
        self.writeChar(VEC_OBJECT_CODE)
        self.writeInt(len(vec)) # Dimension
        
        for c in vec:
            self.writeFloat(c)

    
    def writeVecArray(self, vec_array): # 6 bytes of meta
        if len(vec_array) == 0:
            return
        
        self.writeChar(VEC_ARRAY_OBJECT_CODE)
        
        self.writeInt(len(vec_array)) # Count (number of sub vectors)
        self.writeChar(len(vec_array[0])) # Dimension
        
        for vec in vec_array:
            for c in vec:
                self.writeFloat(c)
                
    def writeImage(self, image): # 9 bytes of meta
        self.writeChar(IMG_OBJECT_CODE)
        
        ''' WRITING THE ACTUAL IMAGE PIXELS : NOT SUPPORTED YET
        sizeX = image.size[0]
        sizeY = image.size[1]
        self.writeInt(sizeX) # x size
        self.writeInt(sizeY) # y size
        
        self.file.write(bytes([int(p*255) for p in image.pixels]))
        '''
        
        self.writeString(image.filepath_from_user()) # Writing the path instead for now
    
    def writeMaterial(self, material): # 1 byte of meta
        print("Writing material:", material.name_full)
        
        self.writeChar(MATERIAL_OBJECT_CODE)
        self.writeString(material.name_full)
        
        ambient_color = [1.0, 1.0, 1.0] # Not supported for now
        diffuse_color = [material.diffuse_color[i] for i in range(3)]
        specular_intensity = material.specular_intensity
        specular_color = [material.specular_color[i] for i in range(3)]
        emit_color = [0.0, 0.0, 0.0] # Not supported for now
        
        self.writeVec(ambient_color)
        self.writeVec(diffuse_color)
        self.writeFloat(specular_intensity)
        self.writeVec(specular_color)
        self.writeVec(emit_color)
        
        # Texture
        try:
            img = material.node_tree.nodes['Image Texture'].image
        except KeyError:
            print("ERROR : Please add a texture to '", material.name_full, "'")
            return -1
            
        #self.writeImage(img)
        filepath = img.filepath_from_user()
        self.writeString(filepath) # For now
        
        datasize = 1 + len(material.name_full) + (4*3)*4 + 1 + 6 + len(filepath) + 1 # Size used in bytes
        print("\t Material data size :", datasize / 1000, "kB")
        return datasize
        
    def writeMesh(self, mesh, type = OBJTYPE_STATIC):
        self.writeChar(MESH_OBJECT_CODE)
        
        # Extracting datas
        name = mesh.name
        print("Writing mesh:", name)
        
        # Geometry
        points_coord = []
        normals_coord = []
        triangulate_mesh(mesh) # Triangulating the mesh
        for v in mesh.vertices:
            normals_coord.append([c for c in v.normal])
            points_coord.append([component for component in v.co])
    
        # Material
        material_name = mesh.materials[0].name_full

        # Texture
        tex_coord = [[vertex_uv.uv[i] for i in range(2)] for vertex_uv in mesh.uv_layers['UVMap'].data] # UV Map
        
        # Writing into file
        ''' Size : size + type + name + (...)*float '''
        datasize = 4 + 1 + len(name) + (3*len(points_coord) + 3*len(normals_coord) + 3 + 3 + 1 + 3 + 3 + 2*len(tex_coord) + 1 + 1) * 4 + len(material_name)+ (18+20)
        self.writeInt(datasize) # Data size in bytes
        print("\tGeometry data size :", (datasize / 1000), "kB")
        
        self.writeChar(type)
        self.writeString(name)
        
        self.writeVecArray(points_coord)
        
        self.writeString(material_name)
        self.writeVecArray(tex_coord)
        self.writeVecArray(normals_coord)
        
        return datasize # size written
    
    def writeLight(self, light):
        self.writeChar(LIGHT_OBJECT_CODE)
            
    def close(self):
        self.file.close()
    

def export(filepath):
    print("Exporting...")
    ex = ConradExporter(filepath)
    
    totalSize = 0
    
    
    # Writing materials (must be done before meshes)
    for material in bpy.data.materials:
        size = ex.writeMaterial(material)
        if size < 0:
            return (False, 0)
        totalSize += size
    
    # Writing meshes
    for mesh in bpy.data.meshes:
        if mesh.users == 0: # Deleted object
            continue
        
        size = ex.writeMesh(mesh)
        if size < 0:
            return (False, 0)
                
        totalSize += size
    
    # Writing lights
    '''
    for light in bpy.data.lights:
        if light.users == 0: # Deleted light
            continue
        
        size = ex.writeLight(light)
        if size < 0:
            return (False, 0)
        
        totalSize += size
    '''
    
    ex.close()
        
    return (True, totalSize) # Success


success, totalSize = export("C:/Users/Thom/Documents/Projets/C++/ConradGameEngine/Conrad/blender/testfile.scene")
if success:
    print("Done exporting", totalSize/1000, "kB.")
else:
    print("An error occured. Exported file will be corrupted.")
