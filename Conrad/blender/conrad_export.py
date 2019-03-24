# This file is a custom exporter for blender compatible with the ConradEngine.
# Command line executable script.
# Automatically exports the current .blend file into a ConradEngine readable format WHEN EXECUTED.

import bpy
import os
import struct

class ConradExporter:
    def __init__(self, filetarget):
        self.filetarget = filetarget
        self.file = open(filetarget, 'wb') # write in bytes

    def writeInt(self, value): # 4 bytes written left to right
        barray = [struct.pack('b', value >> i & 0xff) for i (24, 16, 8, 0)]
        self.file.write(bytes(barray))
        #file.write('{}'.format(value))
    
    def writeString(self, str):
        self.writeInt(len(str)) # Size
        self.file.write(bytes(str, 'utf-8'))
        
    def writeVecArray(vec_array):
        if len(vec_array) == 0:
            return
        
        self.writeInt(len(vec_array)) # Count
        self.writeInt(len(vec_array[0])) # Dimension
        
        for vec in vec_array:
            self.file.write(bytes([float(c) for c in vec])) # Writing floats
    
    def writeMesh(type, name, points_coord, colors_coord, tex_coord, normals_coord):
        
        
    def close(self):
        self.file.close()
    

def export(filepath):
    ConradExporter ex(filepath)

    for mesh in bpy.data.meshes:
        ex
        