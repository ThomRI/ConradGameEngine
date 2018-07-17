#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>

#include "StaticMesh.h"

using namespace std;
using coordinate3d = tuple<float, float, float>;
using coordinate2d = tuple<float, float>;
using Face = tuple<int, int, int,  int, int, int,  int, int, int>; // v1,vt1,vn1    , v2,vt2,vn2,   v3,vt3,vn3

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
    vector<Face> faces;

    for(vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
        line = (*it);
        stringstream stream(line);
        char c; stream >> c; // First char of the string
        switch(c) { // First char of the line
            case 'v': // Vertex
                float x, y, z;
                stream >> x >> y >> z;
                vertices.push_back(make_tuple(x, y, z));
            break;

            case 'vt': // Texture coordinate
                float u, v;
                stream >> u >> v;
                tex.push_back(make_tuple(u, v));
            break;

            case 'vn': // Normal
                float x, y, z;
                stream >> x >> y >> z;
                normals.push_back(make_tuple(x, y, z));
            break;

            case 'f': // Face
                string[3] vert;
                stream >> vert[0] >> vert[1] >> vert[2];

                int v[3];   //v1, v2, v3
                int vt[3];  //vt1, vt2, vt3
                int vn[3];  //vn1, vn2, vn3
                for(int i = 0;i < 3;i++) {
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

                    v[i]    = indexes[0]; // Vertex
                    vt[i]   = indexes[1]; // Texture
                    vn[i]   = indexes[2]; // Normal
                }

                Face f = make_tuple(v[0], vt[0], vn[0],
                                    v[1], vt[1], vn[1],
                                    v[2], vt[2], vn[2]);
                faces.push_back(f);
            break;

            default: break;
        }
    }

    /* Finished parsing the file */
    /* Creating the mesh */
    float *vertices_array = malloc(vertices.size());
    copy(vertices.begin(), vertices.end(), vertices_array);

    float *colors_array = malloc(vertices.size());
    memset(colors_array, 1.0, vertices.size()); // Colors have no effect

    float *tex_array = malloc(tex.size());
    copy(tex.begin(), tex.end(), tex_array);

    StaticMesh *mesh = new StaticMesh(vertices.size(), vertices_array, colors_array, tex_array);

    if(load) mesh->load();
    return mesh;
}

#endif // UTILITIES_HPP_INCLUDED
