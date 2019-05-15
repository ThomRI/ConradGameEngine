#include "SceneFormatParser.h"

SceneFormatParser::SceneFormatParser()
{
    //ctor
}

bool SceneFormatParser::load(string filepath)
{
    if(!m_file.open(filepath.c_str(), ios::in | ios::binary)) {
        m_loaded = false;
        return false;
    }

    /* Retrieving the size of the file */
    m_file.seekg(0, m_file.end());
    m_filesize = m_file.tellg();
    m_file.seekg(0, m_file.begin());

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

            case LIGHT_OBJECT_CODE:
            {
                m_lights->push_back(parseLight(object_buffer));
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

    int size; m_file.get(size);
    if(m_file.eof()) return false;

    char *data_pointer;
    data_pointer = (char *) malloc(size);
    m_file.read(data_pointer, size);
    if(m_file.eof()) return false;

    object = {type, size, data_pointer};
    return true;
}

AbstractMesh *SceneFormatParser::parseMesh(Object meshObject)
{
    AbstractMesh *mesh = new AbstractMesh(/*...*/);
}

AbstractLight *SceneFromParser::parseLight(Object lightObject)
{
    AbstractLight *light = new AbstractLight(/*...*/);
}

SceneFormatParser::~SceneFormatParser()
{
    //dtor
}
