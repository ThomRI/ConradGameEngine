#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "TestCube.h"
#include "TestTriangle.h"
#include "utilities.hpp"
#include "scope.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;

    Application *app = new Application("Sexer", 1280, 720);
    if(!app->init()) {
        cout << "Error setting up SDL or context" << endl;
    }

    Shader shader(string("shaders/basic/light.vert"), string("shaders/basic/light.frag"));
    app->getRenderer()->setShader(shader); // loads the shader

    /* Test scene */

    cout << "Loading scene.obj..." << endl;
    vector<StaticMesh*> meshlist = loadOBJ_static("objects/scene.obj", false, true);
    cout << "Loaded the file" << endl;


    StaticMesh *cone = meshlist[0];
    StaticMesh *gun = meshlist[1];
    StaticMesh *cylinder = meshlist[2];
    StaticMesh *ground = meshlist[3];

    cout << "Associated meshes" << endl;

    AbstractTexture *tex_grass = new AbstractTexture("textures/veg010.jpg");
    AbstractTexture *tex_wood = new AbstractTexture("textures/wooden.png");
    AbstractTexture *tex_torus = new AbstractTexture("textures/torus.png");
    AbstractTexture *tex_gun = new AbstractTexture("textures/handgun_C.jpg");
    AbstractTexture *tex_cone = new AbstractTexture("textures/wall068b.jpg");

    cout << "Created textures" << endl;

    cylinder->setTexture(tex_wood);
    ground->setTexture(tex_grass);
    gun->setTexture(tex_gun);
    cone->setTexture(tex_cone);


    cout << "Associated textures" << endl;

    cylinder->load();
    ground->load();
    gun->load();
    cone->load();

    cout << "Loaded meshes" << endl;

    app->getRenderer()->addMesh(cylinder);
    app->getRenderer()->addMesh(ground);
    app->getRenderer()->addMesh(gun);
    app->getRenderer()->addMesh(cone);


    cout << "Ready!" << endl;
    app->loop(120); // 120 fps

    return 0;
}
