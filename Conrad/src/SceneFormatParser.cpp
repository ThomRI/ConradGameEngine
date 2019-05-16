#include "SceneFormatParser.h"

SceneFormatParser::SceneFormatParser()
{
    //ctor
}

SceneFormatParser::SceneFormatParser(string filepath)
{
    load(filepath);
    parse();
}

bool SceneFormatParser::load(string filepath)
{
    m_file.open(filepath.c_str(), ios::in | ios::binary);
    if(!m_file.good()) {
        m_loaded = false;
        return false;
    }

    /* Retrieving the size of the file */
    m_file.seekg(0, m_file.end);
    m_filesize = m_file.tellg();
    m_file.seekg(0, m_file.beg);

    m_loaded = true;
    return true;
}

bool SceneFormatParser::parse()
{
    if(!m_loaded) {
        return false;
    }

    Object object_buffer;
    while(read_object(object_buffer)) {
        switch(object_buffer.type) {
            case MESH_OBJECT_CODE:
            {
                m_meshes->push_back(parseMesh(object_buffer));
                break;
            }

            case MATERIAL_OBJECT_CODE:
            {
                AbstractMaterial *material = parseMaterial(object_buffer);
                m_materials->at(material->getName()) = material;
                break;
            }

            case LIGHT_OBJECT_CODE:
            {
                //m_lights->push_back(parseLight(object_buffer));
                break;
            }

            case CAMERA_OBJECT_CODE:
            {

                break;
            }

            case VEC_ARRAY_OBJECT_CODE:
            {

                break;
            }

            case VEC_OBJECT_CODE:
            {

                break;
            }

            case STR_OBJECT_CODE:
            {

                break;
            }

        }

        free(object_buffer.data_pointer);
    }

}

bool SceneFormatParser::read_object(Object &object)
{
    char type; m_file.get(type);
    if(m_file.eof()) return false;

    int size; m_file >> size;
    if(m_file.eof()) return false;

    char *data_pointer;
    data_pointer = (char *) malloc(size);
    m_file.read(data_pointer, size);
    if(m_file.eof()) return false;

    object.type = type;
    object.datasize = size;
    object.data_pointer = data_pointer;

    return true;
}

// Note that we could have used a &*data_pointer to directly modify the pointer instead of returning it, but returning it allows for more flexibility
template<typename T>
char *SceneFormatParser::extract(char *data_pointer, T &target)
{
    target = *reinterpret_cast<T*>(data_pointer); // Treats data_pointer as a pointing at a T type value
    return data_pointer + sizeof(T);
}

char *SceneFormatParser::extractVectorArray(char *data_pointer, int &count, int &dimension, float *&target_pointer)
{
    data_pointer = extract(data_pointer, count);
    data_pointer = extract(data_pointer, dimension);
    target_pointer = reinterpret_cast<float*>(data_pointer);

    return data_pointer + sizeof(float) * count * dimension;
}

char *SceneFormatParser::extractVector(char *data_pointer, int &dimension, float *&target_pointer)
{
    data_pointer = extract(data_pointer, dimension);
    target_pointer = reinterpret_cast<float*>(target_pointer);

    return data_pointer + sizeof(float) * dimension;
}

char *SceneFormatParser::extractString(char *data_pointer, string &target)
{
    target = string(data_pointer); // .scene format includes the end of sequence '\0' character so this should work fine.
    return data_pointer + target.length() + 1; // +1 to count the null terminator '\0'
}

AbstractMaterial *SceneFormatParser::parseMaterial(Object materialObject)
{
    string material_name;
    materialObject.data_pointer = extractString(materialObject.data_pointer, material_name);

    int dimension;
    float *color_pointer;

    // Ambient color
    materialObject.data_pointer = extractVector(materialObject.data_pointer, dimension, color_pointer);
    RGB ambientColor(color_pointer[0], color_pointer[1], color_pointer[2]);

    // Diffuse color
    materialObject.data_pointer = extractVector(materialObject.data_pointer, dimension, color_pointer);
    RGB diffuseColor(color_pointer[0], color_pointer[1], color_pointer[2]);

    // Specular intensity
    float specularIntensity;
    materialObject.data_pointer = extract(materialObject.data_pointer, specularIntensity);

    // Specular color
    materialObject.data_pointer = extractVector(materialObject.data_pointer, dimension, color_pointer);
    RGB specularColor(color_pointer[0], color_pointer[1], color_pointer[2]);

    // Emit color
    materialObject.data_pointer = extractVector(materialObject.data_pointer, dimension, color_pointer);
    RGB emitColor(color_pointer[0], color_pointer[1], color_pointer[2]);

    // Texture path
    string texture_path;
    materialObject.data_pointer = extractString(materialObject.data_pointer, texture_path);

    AbstractMaterial *material = new AbstractMaterial(ambientColor, diffuseColor, specularColor, emitColor, specularIntensity, 1.0, 0.01, 1.0, 1.0, 1.0, material_name);

    AbstractTexture *texture = new AbstractTexture(texture_path);
    texture->load();

    material->setDiffuseTexture(texture);

    return material;
}

AbstractMesh *SceneFormatParser::parseMesh(Object meshObject)
{
    char mesh_type;
    meshObject.data_pointer = extract(meshObject.data_pointer, mesh_type);

    GLenum meshType;
    switch(mesh_type) {
        case OBJTYPE_STATIC:
        {
            meshType = GL_STATIC_DRAW;
            break;
        }

        case OBJTYPE_DYNAMIC:
        {
            meshType = GL_DYNAMIC_DRAW;
            break;
        }

        case OBJTYPE_STREAM:
        {
            meshType = GL_STREAM_DRAW;
            break;
        }
    }

    string mesh_name;
    meshObject.data_pointer = extractString(meshObject.data_pointer, mesh_name);

    // Vertices
    int verticesCount, dimension;
    float *vertices;
    meshObject.data_pointer = extractVectorArray(meshObject.data_pointer, verticesCount, dimension, vertices);

    // Material name
    string material_name;
    meshObject.data_pointer = extractString(meshObject.data_pointer, material_name);

    // Textures (dimension 2 vector array)
    int texCount;
    float *texCoords;
    meshObject.data_pointer = extractVectorArray(meshObject.data_pointer, texCount, dimension, texCoords);

    // Normals
    int normalsCount;
    float *vertexNormals;
    meshObject.data_pointer = extractVectorArray(meshObject.data_pointer, normalsCount, dimension, vertexNormals);

    float *colors = (float *) malloc(verticesCount * 3 * sizeof(float));
    fill_n(colors, verticesCount * 3, 1.0);

    AbstractMesh *mesh = new AbstractMesh(verticesCount, vertices, verticesCount, colors, texCount, texCoords, vertexNormals, meshType);
    mesh->setMaterial(m_materials->at(material_name));

    return mesh;
}

/*
AbstractLight *SceneFromParser::parseLight(Object lightObject)
{

}
*/

vector<AbstractMesh *> *SceneFormatParser::getMeshes()
{
    return m_meshes;
}

map<string, AbstractMaterial *> *SceneFormatParser::getMaterials()
{
    return m_materials;
}

vector<AbstractLight *> *SceneFormatParser::getLights()
{
    return m_lights;
}

SceneFormatParser::~SceneFormatParser()
{
    //dtor
}
