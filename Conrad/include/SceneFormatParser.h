#ifndef SCENEFORMATPARSER_H
#define SCENEFORMATPARSER_H

#include <fstream>
#include <algorithm>
#include <vector>
#include "StaticMesh.h"

#include "PointLight.h"
#include "SunLight.h"
#include "SpotLight.h"


#include "AbstractMaterial.h"
#include <string>
#include <map>
//#include "scope.h"

 /* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Object codes */
#define MESH_OBJECT_CODE    0
#define MATERIAL_OBJECT_CODE 1

#define LIGHT_OBJECT_CODE   2
    #define LIGHT_POINT_CODE 0
    #define LIGHT_SUN_CODE 1
    #define LIGHT_SPOT_CODE 2

#define CAMERA_OBJECT_CODE  3

#define VEC_ARRAY_OBJECT_CODE   255
#define VEC_OBJECT_CODE         254 // Vectors of float
#define STR_OBJECT_CODE         253

#define OBJTYPE_STATIC 0
#define OBJTYPE_DYNAMIC 1
#define OBJTYPE_STREAM 2

/* IMPORTANT : BY DEFAULT, EVERYTHING CONTAINED IN A VECTOR OR AN ARRAY VECTOR ARE FLOAT TYPES */

class SceneFormatParser
{
    public:
        SceneFormatParser();
        SceneFormatParser(std::string filepath);
        virtual ~SceneFormatParser();

        bool load(std::string filepath);
        bool parse();

        std::vector<StaticMesh *> *getMeshes();
        std::map<std::string, AbstractMaterial *> *getMaterials();
        std::vector<AbstractLight *> *getLights();

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
        inline char *extractString(char *data_pointer, std::string &target);

        StaticMesh *parseMesh(Object meshObject); /* IMPORTANT : MUST COPY THE DATA FROM THE DATA_POINTER (NOT JUST FORWARD THE POINTER), IT WILL BE DELETED RIGHT AFTER !!! */
        AbstractMaterial *parseMaterial(Object materialObject); /* SAME */
        AbstractLight *parseLight(Object lightObject); /* SAME */

    private:
        std::ifstream m_file;
        size_t m_filesize; // in bytes

        bool m_loaded = false;

        char *m_iterator;

        std::vector<StaticMesh *>  m_meshes;
        std::map<std::string, AbstractMaterial *> m_materials;
        std::vector<AbstractLight *> m_lights;

};

// Inline functions must be in the same scope file as their definition

// Note that we could have used a &*data_pointer to directly modify the pointer instead of returning it, but returning it allows for more flexibility
template<typename T>
inline char *SceneFormatParser::extract(char *data_pointer, T &target)
{
    target = *reinterpret_cast<T*>(data_pointer); // Treats data_pointer as a pointing at a T type value
    return data_pointer + sizeof(T);
}

inline char *SceneFormatParser::extractVectorArray(char *data_pointer, int &count, int &dimension, float *&target_pointer)
{
    data_pointer = extract(data_pointer, count);
    data_pointer = extract(data_pointer, dimension);
    target_pointer = reinterpret_cast<float*>(data_pointer);

    return data_pointer + sizeof(float) * count * dimension;
}

inline char *SceneFormatParser::extractVector(char *data_pointer, int &dimension, float *&target_pointer)
{
    data_pointer = extract(data_pointer, dimension);
    target_pointer = reinterpret_cast<float*>(data_pointer);

    return data_pointer + sizeof(float) * dimension;
}

inline char *SceneFormatParser::extractString(char *data_pointer, std::string &target)
{
    target = std::string(data_pointer); // .scene format includes the end of sequence '\0' character so this should work fine.
    return data_pointer + target.length() + 1; // +1 to count the null terminator '\0'
}

#endif // SCENEFORMATPARSER_H
