#include "OBJ_Static_Handler.h"

using namespace std;

OBJ_Static_Handler::OBJ_Static_Handler(string OBJ_path, string MTL_path) :
    m_OBJ_path(OBJ_path), m_MTL_path(MTL_path)
{
    //ctor
}

void OBJ_Static_Handler::load(bool loadTextures, bool loadMeshes, bool computeVertexNormals)
{
    // First load .MTL then associate the correct materials
    loadMTL(loadTextures);

    loadOBJ(loadMeshes, computeVertexNormals);
}

/* IF OUT OF RANGE : REMEMBER, FACES LINES MUST HAVE A TEXTURE COORD ! */
void OBJ_Static_Handler::loadOBJ(bool loadMeshes, bool computeVertexNormals)
{
    ifstream file(m_OBJ_path.c_str());
    if(!file) {
        cout << "Can't load (" << m_OBJ_path << ")" << endl;
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

    vector<mapper> vertex_normals_mapper; // (vertex index, normal index)

    vector<int> faces_vertex_index;
    vector<int> faces_tex_index;
    vector<int> faces_normal_index;

    AbstractMaterial *currentMaterial = nullptr;
    string name;

    bool firstO = true; // Checks if the first "o.." has been read (in order not to create an invalid mesh with the infos above the first object). true = we are still at the first one
    for(vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
        line = (*it);
        stringstream stream(line);
        string c; stream >> c; // First char of the string

        int index = -1;
        if(c == "v")            index = VERTEX;
        else if(c == "vt")      index = TEXTURE;
        else if(c == "vn")      index = NORMAL;
        else if(c == "f")       index = FACE;
        else if(c == "o")       index = OBJECT;
        else if(c == "usemtl")  index = USEMTL;

        switch(index) { // First char of the line
            case OBJECT: // Next object has been detected
            {
                if(firstO)  { // We don't want to create "last" object if it's the first one
                    firstO = false;
                    stream >> name;
                    break;
                }

                // Creating last object
                StaticMesh *mesh;
                if(computeVertexNormals)    mesh = StaticMeshFromArrays(&vertices, &tex, &normals, &faces_vertex_index, &faces_tex_index, &faces_normal_index, &vertex_normals_mapper);
                else                        mesh = StaticMeshFromArrays(&vertices, &tex, &normals, &faces_vertex_index, &faces_tex_index, &faces_normal_index);

                if(m_MTL_loaded && currentMaterial != nullptr) mesh->setMaterial(currentMaterial);
                if(loadMeshes) mesh->load();

                m_meshes[name] = mesh;

                stream >> name;

                /* Reseting everything for next mesh */
                faces_vertex_index.clear();
                faces_tex_index.clear();
                faces_normal_index.clear();
                vertex_normals_mapper.clear();
                currentMaterial = nullptr;

                break;
            }

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

                    // Associating the corresponding vertex index with the normal index (for calculating vertex normals)
                    vertex_normals_mapper.push_back(make_tuple(indexes[0] - 1, indexes[2] - 1));
                }

                break;
            }

            case USEMTL:
            {
                if(!m_MTL_loaded) break;

                string materialName;
                stream >> materialName;

                currentMaterial = m_materials[materialName];
                break;
            }

            default: break;
        }
    }

    /* Don't forget the very last one ! (there is no "o" to trigger it ! */
    StaticMesh *mesh;
    if(computeVertexNormals)    mesh = StaticMeshFromArrays(&vertices, &tex, &normals, &faces_vertex_index, &faces_tex_index, &faces_normal_index, &vertex_normals_mapper);
    else                        mesh = StaticMeshFromArrays(&vertices, &tex, &normals, &faces_vertex_index, &faces_tex_index, &faces_normal_index);

    if(m_MTL_loaded && currentMaterial != nullptr) mesh->setMaterial(currentMaterial);
    if(loadMeshes) mesh->load();

    m_meshes[name] = mesh;
}

void OBJ_Static_Handler::loadMTL(bool loadTextures)
{
    ifstream file(m_MTL_path.c_str());
    if(!file) {
        cout << "Can't load (" << m_MTL_path << ")" << endl;
    }

    /* Getting the file in memory */
    string line;
    vector<string> lines;
    while(getline(file, line)) {
        lines.push_back(line);
    } file.close();

    RGB Ka, Kd, Ks, Ke;
    float Ns, d;
    string name;

    AbstractTexture *diffuseTexture, *specularTexture;
    bool setDiffTex(false), setSpecTex(false);

    bool first(true); // Are we still at the first one ?

    for(vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
        line = (*it);
        stringstream stream(line);
        string c; stream >> c; // identifier

        int index = -1;
        if(c == "Ka")           index = AMBIENT;
        else if(c == "Kd")      index = DIFFUSE;
        else if(c == "Ks")      index = SPECULAR;
        else if(c == "Ke")      index = EMIT;
        else if(c == "Ns")      index = SPEC_EXP;
        else if(c == "d")       index = ALPHA;
        else if(c == "newmtl")  index = NEWMTL;
        else if(c == "map_Kd")  index = DIFFUSE_TEX;
        else if(c == "map_Ks")  index = SPECULAR_TEX;

        switch(index) {
            case NEWMTL:
            {
                if(first) {
                    first = false;
                    stream >> name;
                    break;
                }

                // Treating last material
                AbstractMaterial *material = new AbstractMaterial(Ka, Kd, Ks, Ke, Ns, d);

                if(setDiffTex)  material->setDiffuseTexture(diffuseTexture);
                if(setSpecTex)  material->setSpecularTexture(specularTexture);

                m_materials[name] = material;
                stream >> name;
                // No need to reset : the values will be overwritten

                setDiffTex = false;
                setSpecTex = false;

                break;
            }

            case AMBIENT:
            {
                float x, y, z;
                stream >> x >> y >> z;

                Ka = {x, y, z};
                break;
            }

            case DIFFUSE:
            {
                float x, y, z;
                stream >> x >> y >> z;

                Kd = {x, y, z};
                break;
            }

            case SPECULAR:
            {
                float x, y, z;
                stream >> x >> y >> z;

                Ks = {x, y, z};
                break;
            }

            case EMIT:
            {
                float x, y, z;
                stream >> x >> y >> z;

                Ke = {x, y, z};
                break;
            }

            case SPEC_EXP:
            {
                float value;
                stream >> value;

                Ns = value;
                break;
            }

            case ALPHA:
            {
                float value;
                stream >> value;

                d = value;
                break;
            }

            case DIFFUSE_TEX:
            {
                string path;
                stream >> path;

                diffuseTexture = new AbstractTexture(path);
                if(loadTextures)   diffuseTexture->load();

                setDiffTex = true;
                break;
            }

            case SPECULAR_TEX:
            {
                string path;
                stream >> path;

                specularTexture = new AbstractTexture(path);
                if(loadTextures)   specularTexture->load();

                setSpecTex = true;
                break;
            }
        }
    }

    // Very last material
    AbstractMaterial *material = new AbstractMaterial(Ka, Kd, Ks, Ke, Ns, d);

    if(setDiffTex)  material->setDiffuseTexture(diffuseTexture);
    if(setSpecTex)  material->setSpecularTexture(specularTexture);

    m_materials[name] = material;
    m_MTL_loaded = true;
}

StaticMesh *OBJ_Static_Handler::getMesh(string meshname)
{
    return m_meshes.at(meshname); // ->at() checks existence
}

vector<StaticMesh *> OBJ_Static_Handler::getAllMeshes()
{
    vector<StaticMesh *> v;
    for(map<string, StaticMesh *>::iterator it = m_meshes.begin();it != m_meshes.end();it++) {
        v.push_back(it->second);
    }

    return v;
}

OBJ_Static_Handler::~OBJ_Static_Handler()
{
    //dtor
}
