#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>

#include "StaticMesh.h"

#define X_coord 0
#define Y_coord 1
#define Z_coord 2

#define VERTEX 0
#define TEXTURE 1
#define NORMAL 2
#define FACE 3

using namespace std;
using coordinate3d = tuple<float, float, float>;
using coordinate2d = tuple<float, float>;
//using Face = tuple<int, int, int,  int, int, int,  int, int, int>; // v1,vt1,vn1    , v2,vt2,vn2,   v3,vt3,vn3

/*!
 *  \file utilities.hpp
 *  \brief This file is used to define useful static functions for (for now) the rendering engine
 */

/*!
 *  \brief Loads a .obj file treated as a static mesh (environment, terrain, ...)
 *  \return (StaticMesh) The mesh, loaded or not depending on the load parameter value.
 *  \warning Only accepts triangulated meshes ! In other cases, the function behavior is not determined.
 *  \warning Meshes MUST HAVE UV TEXTURE INFOS. This is crucial : the engine works based on textures.
 */
static StaticMesh *loadOBJ_static(string filepath, bool load = true)
{
    ifstream file(filepath.c_str());
    if(!file) {
        cout << "Can't load (" << filepath << ")" << endl;
        return nullptr;
    }

    /* Getting the file in memory */
    string line;
    vector<string> lines;
    while(getline(file, line)) {
        lines.push_back(line);
    } file.close();

    /* Parsing the .obj lines */
    vector<coordinate3d> vertices;
    vector<coordinate2d> tex;
    vector<coordinate3d> normals;

    vector<int> faces_vertex_index;
    vector<int> faces_tex_index;
    vector<int> faces_normal_index;

    for(vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
        line = (*it);
        stringstream stream(line);
        string c; stream >> c; // First char of the string

        int index = -1;
        if(c == "v")        index = VERTEX;
        else if(c == "vt")  index = TEXTURE;
        else if(c == "vn")  index = NORMAL;
        else if(c == "f")   index = FACE;
        switch(index) { // First char of the line
            case VERTEX: // Vertex
            {
                float x, y, z;
                stream >> x >> y >> z;
                vertices.push_back(make_tuple(x, y, z));

                break;
            }

            case TEXTURE:  // Texture coordinate
            {
                float u, v;
                stream >> u >> v;
                tex.push_back(make_tuple(u, v));

                break;
            }

            case NORMAL: // Normal
            {
                float x, y, z;
                stream >> x >> y >> z;
                normals.push_back(make_tuple(x, y, z));

                break;
            }

            case FACE: // Face
            {
                string vert[3];
                stream >> vert[0] >> vert[1] >> vert[2];

                for(int i = 0;i < 3;i++) { // One vertex
                    stringstream sub_stream(vert[i]);
                    int indexes[3];

                    /* Parsing "1/2/3" */
                    int value, j = 0;
                    while(sub_stream >> value) {
                        indexes[j] = value;

                        if(sub_stream.peek() == '/') sub_stream.ignore();
                        j++;
                    }
                    /* Now indexes[0] is vertex ; indexes[1] is texture ; indexes[2] is normal */

                    // Indexes start at 1 on .obj. The indexes now stored are the real indexes ready to be accessed from.

                    faces_vertex_index.push_back(indexes[0] - 1);   // One vertex  (3 coords)
                    faces_tex_index.push_back(indexes[1] - 1);      // One texture (2 coords)
                    faces_normal_index.push_back(indexes[2] - 1);   // One normal  (3 coords)
                }

                break;
            }

            default: break;
        }
    }

    /* Finished parsing the file */
    /* Creating the mesh */
    float *vertices_array;
    float *colors_array;
    float *tex_array;
    vertices_array = (float*) malloc(faces_vertex_index.size() * 3 * sizeof(float));
    colors_array = (float*) malloc(faces_vertex_index.size() * 3 * sizeof(float));
    tex_array = (float*) malloc(faces_tex_index.size() * 2 * sizeof(float));

    if(vertices_array == 0 || colors_array == 0 || tex_array == 0) {
        std::cout << "Error parsing .obj : out of memory" << std::endl;
        return nullptr;
    }

    std::fill_n(colors_array, faces_vertex_index.size() * 3, 1.0); // Colors aren't used for textured materials

    /* Filling arrays with faces order */
    for(int i = 0;i < faces_vertex_index.size();i++) { // One vertex
        coordinate3d vertex_coords = vertices[faces_vertex_index[i]];

        vertices_array[3*i]     = get<X_coord>(vertex_coords);
        vertices_array[3*i + 1] = get<Y_coord>(vertex_coords);
        vertices_array[3*i + 2] = get<Z_coord>(vertex_coords);
    }

    for(int i = 0;i < faces_tex_index.size();i++) { // One texture
        coordinate2d tex_coords = tex[faces_tex_index[i]];

        tex_array[2*i]      = get<X_coord>(tex_coords); // U
        tex_array[2*i + 1]  = get<Y_coord>(tex_coords); // V
    }

    /* Normals not supported for now */

    StaticMesh *mesh = new StaticMesh(faces_vertex_index.size(), vertices_array, colors_array, tex_array);


    if(load) mesh->load();
    return mesh;
}

#endif // UTILITIES_HPP_INCLUDED
