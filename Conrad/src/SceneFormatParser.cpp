#include "SceneFormatParser.h"

using namespace std;
using namespace glm;

SceneFormatParser::SceneFormatParser()
{
    //ctor
}

SceneFormatParser::SceneFormatParser(string filepath)
{
    cout << "Will parse " << filepath << endl;
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

    cout << "Starting parsing" << endl;

    Object object_buffer;
    while(read_object(object_buffer)) {
        switch(object_buffer.type) {
            case MESH_OBJECT_CODE:
            {
                StaticMesh *mesh = parseMesh(object_buffer);
                cout << "Found mesh." << endl;
                m_meshes.push_back(mesh);
                break;
            }

            case MATERIAL_OBJECT_CODE:
            {
                AbstractMaterial *material = parseMaterial(object_buffer);

                m_materials[material->getName()] = material;
                cout << "Found material " << material->getName() << endl;
                break;
            }

            case LIGHT_OBJECT_CODE:
            {
                m_lights.push_back(parseLight(object_buffer));
                cout << "Found light" << endl;
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

    m_file.close();

}

bool SceneFormatParser::read_object(Object &object)
{
    char type; m_file.get(type);
    if(m_file.eof()) return false;

    char *buffer = new char[4];
    m_file.read(buffer, 4);
    size_t size = *reinterpret_cast<unsigned int*>(buffer);
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

    int specularExponent;
    materialObject.data_pointer = extract(materialObject.data_pointer, specularExponent);

    // Texture path
    string texture_path;
    materialObject.data_pointer = extractString(materialObject.data_pointer, texture_path);

    AbstractMaterial *material = new AbstractMaterial(ambientColor, diffuseColor, specularColor, emitColor, specularExponent, 1.0, 0.01, 1.0, specularIntensity, 1.0, material_name);

    AbstractTexture *texture = new AbstractTexture(texture_path);
    texture->load();

    material->setDiffuseTexture(texture);

    return material;
}

StaticMesh *SceneFormatParser::parseMesh(Object meshObject)
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

    StaticMesh *mesh = new StaticMesh(verticesCount, vertices, colors, texCoords, vertexNormals);
    mesh->setMaterial(m_materials.at(material_name));
    mesh->load(); // <<-- LOADS IT FOR NOW

    return mesh;
}

AbstractLight *SceneFormatParser::parseLight(Object lightObject)
{
    char light_type;
    lightObject.data_pointer = extract(lightObject.data_pointer, light_type);

    float *vec3_buffer;
    int dimension;

    /* Position */
    lightObject.data_pointer = extractVector(lightObject.data_pointer, dimension, vec3_buffer);
    vec3 position(vec3_buffer[0], vec3_buffer[1], vec3_buffer[2]);
    cout << vec3_buffer[0] << " " << vec3_buffer[1] << " " << vec3_buffer[2] << endl;

    /* Color */
    lightObject.data_pointer = extractVector(lightObject.data_pointer, dimension, vec3_buffer);
    vec3 color(vec3_buffer[0], vec3_buffer[1], vec3_buffer[2]);

    /* Direction */
    lightObject.data_pointer = extractVector(lightObject.data_pointer, dimension, vec3_buffer);
    vec3 direction(vec3_buffer[0], vec3_buffer[1], vec3_buffer[2]);
    cout << vec3_buffer[0] << " " << vec3_buffer[1] << " " << vec3_buffer[2] << endl;

    /* Maximum angle */
    float intensity;
    lightObject.data_pointer = extract(lightObject.data_pointer, intensity);

    /* Cast Shadow */
    bool castShadow;
    lightObject.data_pointer = extract(lightObject.data_pointer, castShadow);
    cout << "Cast shadow : " << castShadow << endl;

    switch(light_type)
    {
        case LIGHT_POINT_CODE:
        {
            cout << "Type : point" << endl;
            PointLight *light = new PointLight(position, color, intensity, castShadow);
            return light;

            break;
        }

        case LIGHT_SUN_CODE:
        {
            cout << "Type : sun" << endl;
            SunLight *light = new SunLight(position, direction, color, intensity, castShadow);
            return light;

            break;
        }

        case LIGHT_SPOT_CODE:
        {
            cout << "Type : spot" << endl;
            SpotLight *light = new SpotLight(position, color, direction, 45, 60, intensity, castShadow, 0.08, 0.08, 100.0);
            return light;

            break;
        }

    }
}

vector<StaticMesh *> *SceneFormatParser::getMeshes()
{
    return &m_meshes;
}

map<string, AbstractMaterial *> *SceneFormatParser::getMaterials()
{
    return &m_materials;
}

vector<AbstractLight *> *SceneFormatParser::getLights()
{
    return &m_lights;
}

SceneFormatParser::~SceneFormatParser()
{
    //dtor
}
