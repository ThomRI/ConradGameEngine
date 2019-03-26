# This file is a custom exporter for blender compatible with the ConradEngine.
# Command line executable script.
# Automatically exports the current .blend file into a ConradEngine readable format WHEN EXECUTED.

import bpy
import os
import struct

OBJTYPE_STATIC = 0
OBJTYPE_DYNAMIC = 1
OBJTYPE_STREAM = 2

MESH_OBJECT_CODE = 0
LIGHT_OBJECT_CODE = 1
CAMERA_OBJECT_CODE = 2
VEC_ARRAY_OBJECT_CODE = 255
STR_OBJECT_CODE = 254

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
    
    def writeString(self, string):
        self.writeInt(len(string)) # Size
        self.file.write(bytes(string, 'utf-8'))
        
    def writeChar(self, c):
        self.file.write(bytes([c]))
        
    def writeVecArray(self, vec_array):
        if len(vec_array) == 0:
            return
        
        self.writeChar(VEC_ARRAY_OBJECT_CODE)
        
        self.writeInt(len(vec_array)) # Count
        self.writeChar(len(vec_array[0])) # Dimension
        
        for vec in vec_array:
            self.writeFloat(vec[0])
            self.writeFloat(vec[1])
            self.writeFloat(vec[2])
    
    def writeMesh(self, mesh, type = OBJTYPE_STATIC):
        self.writeChar(MESH_OBJECT_CODE)
        
        # Extracting datas
        name = mesh.name
        print("Writing", name)
        
        points_coord = []
        for v in mesh.vertices:
            points_coord.append([component for component in v.co])
        
        colors_coord = []
        tex_coord = []
        normals_coord = []
        
        self.writeInt(1 + len(name) + 3*len(points_coord) + 3*len(colors_coord) + 2*len(tex_coord) + 3*len(normals_coord)) # Data size
        print("Mesh data size = ", 1 + len(name) + 3*len(points_coord) + 3*len(colors_coord) + 2*len(tex_coord) + 3*len(normals_coord))
        
        self.writeChar(type)
        self.writeString(name)
        
        self.writeVecArray(points_coord)
        self.writeVecArray(colors_coord)    
        self.writeVecArray(tex_coord)
        self.writeVecArray(normals_coord)
            
    def close(self):
        self.file.close()
    

def export(filepath):
    ex = ConradExporter(filepath)
    
    for mesh in bpy.data.meshes:
        if mesh.users == 0: # Deleted object
            continue
        ex.writeMesh(mesh)
    
    ex.close()

export("C:/Users/Thom/Documents/Projets/C++/ConradGameEngine/Conrad/blender/testfile.txt")