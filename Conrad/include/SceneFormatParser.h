#ifndef SCENEFORMATPARSER_H
#define SCENEFORMATPARSER_H

#include <fstream>
#include <algorithm>
#include <vector>
#include "AbstractMesh.h"
#include "AbstractLight.h"
#include "AbstractMaterial.h"
#include <string>
#include <map>
#include "scope.h"

/* Object codes */
#define MESH_OBJECT_CODE    0
#define MATERIAL_OBJECT_CODE 1
#define LIGHT_OBJECT_CODE   2
#define CAMERA_OBJECT_CODE  3

#define VEC_ARRAY_OBJECT_CODE   255
#define VEC_OBJECT_CODE         254 // Vectors of float
#define STR_OBJECT_CODE         253

#define OBJTYPE_STATIC 0
#define OBJTYPE_DYNAMIC 1
#define OBJTYPE_STREAM 2

/* IMPORTANT : BY DEFAULT, EVERYTHING CONTAINED IN A VECTOR OR AN ARRAY VECTOR ARE FLOAT TYPES */

using namespace std;

class SceneFormatParser
{
    public:
        SceneFormatParser();
        SceneFormatParser(string filepath);
        virtual ~SceneFormatParser();

        bool load(string filepath);
        bool parse();

        vector<AbstractMesh *> *getMeshes();
        map<string, AbstractMaterial *> *getMaterials();
        vector<AbstractLight *> *getLights();

    protected:
        /* ##### TYPE STRUCTURES ##### */

        /* An abstract structure for any block of data */
        struct Object {
            char type;
            int datasize = 0;

            char *data_pointer = nullptr;
        };

        /* ##### METHODS #####*/

        /* Reads an object as stored in the .scene format */
        bool read_object(Object &object);

        template<typename T>
        inline char *extract(char *data_pointer, T &target); // Extracts a T type from the data_pointer. Returns the forwarded data pointer
        inline char *extractVectorArray(char *data_pointer, int &count, int &dimension, float *&target_pointer);
        inline char *extractVector(char *data_pointer, int &dimension, float *&target_pointer);
        inline char *extractString(char *data_pointer, string &target);

        AbstractMesh *parseMesh(Object meshObject); /* IMPORTANT : MUST COPY THE DATA FROM THE DATA_POINTER (NOT JUST FORWARD THE POINTER), IT WILL BE DELETED RIGHT AFTER !!! */
        AbstractMaterial *parseMaterial(Object materialObject); /* SAME */
        //AbstractLight *parseLight(Object lightObject); /* SAME */

    private:
        ifstream m_file;
        size_t m_filesize; // in bytes

        bool m_loaded = false;

        char *m_iterator;

        vector<AbstractMesh *>  *m_meshes;
        map<string, AbstractMaterial *> *m_materials;
        vector<AbstractLight *> *m_lights;

};

#endif // SCENEFORMATPARSER_H
