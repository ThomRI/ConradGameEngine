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

    Shader shader(string("shaders/basic/texture.vert"), string("shaders/basic/texture.frag"));
    app->getRenderer()->setShader(shader); // loads the shader

    /* Test scene */
    vector<StaticMesh*> meshlist = loadOBJ_static("objects/scene.obj", false);
    StaticMesh *box = meshlist[2];
    StaticMesh *cylinder = meshlist[0];
    StaticMesh *ground = meshlist[1];

    AbstractTexture *tex_grass = new AbstractTexture("textures/veg010.jpg");
    AbstractTexture *tex_concrete = new AbstractTexture("textures/cylinder.png");
    AbstractTexture *tex_crate = new AbstractTexture("textures/box.png");

    box->setTexture(tex_crate);
    cylinder->setTexture(tex_concrete);
    ground->setTexture(tex_grass);

    box->load();
    cylinder->load();
    ground->load();

    app->getRenderer()->addMesh(box);
    app->getRenderer()->addMesh(cylinder);
    app->getRenderer()->addMesh(ground);



    app->loop(120); // 120 fps

    return 0;
}
