#ifndef SCENEFORMATPARSER_H
#define SCENEFORMATPARSER_H

#include <ifstream>
#include <algorithm>
#include <vector>
#include <AbstractMesh.h>
#include <string>

/* Object codes */
#define MESH_OBJECT_CODE    0
#define LIGHT_OBJECT_CODE   1
#define CAMERA_OBJECT_CODE  2

#define VEC_ARRAY_OBJECT_CODE   255
#define VEC_OBJECT_CODE         254 // Vectors of float
#define STR_OBJECT_CODE         253

using namespace std;

class SceneFormatParser
{
    public:
        SceneFormatParser();
        virtual ~SceneFormatParser();

        bool load(string filepath);
        bool parse();

        vector<AbstractMesh *> *getMeshes();
        vector<AbstractLight *> *getLights();

    protected:
        /* An abstract structure for any block of data */
        struct Object {
            char code;
            int datasize = 0;

            char *data_pointer = nullptr;
        };

        /* Reads an object as stored in the .scene format */
        bool read_object(Object &object);

        AbstractMesh *parseMesh(Object meshObject); /* IMPORTANT : MUST COPY THE DATA FROM THE DATA_POINTER (NOT JUST FORWARD THE POINTER), IT WILL BE DELETED RIGHT AFTER !!! */
        AbstractLight *parseLight(Object lightObject); /* SAME */

        vector<

    private:
        ifstream m_file;
        size_t m_filesize; // in bytes

        bool m_loaded = false;

        char *m_iterator;

        vector<AbstractMesh *>  *m_meshes;
        vector<AbstractLight *> *m_lights;

};

#endif // SCENEFORMATPARSER_H
