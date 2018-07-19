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
    cout << "Loading scene.obj..." << endl;
    vector<StaticMesh*> meshlist = loadOBJ_static("objects/cube.obj", false, true);
    cout << "Loaded the file" << endl;


    /*StaticMesh *torus = meshlist[0];
    StaticMesh *cylinder = meshlist[1];
    StaticMesh *gun = meshlist[2];
    StaticMesh *box = meshlist[3];
    StaticMesh *ground = meshlist[4];

    AbstractTexture *tex_grass = new AbstractTexture("textures/veg010.jpg");
    AbstractTexture *tex_concrete = new AbstractTexture("textures/cylinder.png");
    AbstractTexture *tex_crate = new AbstractTexture("textures/box.png");
    AbstractTexture *tex_torus = new AbstractTexture("textures/torus.png");
    AbstractTexture *tex_gun = new AbstractTexture("textures/handgun_C.jpg");

    box->setTexture(tex_crate);
    cylinder->setTexture(tex_concrete);
    ground->setTexture(tex_grass);
    torus->setTexture(tex_torus);
    gun->setTexture(tex_gun);

    box->load();
    cylinder->load();
    ground->load();
    torus->load();
    gun->load();

    app->getRenderer()->addMesh(box);
    app->getRenderer()->addMesh(cylinder);
    app->getRenderer()->addMesh(ground);
    app->getRenderer()->addMesh(torus);
    app->getRenderer()->addMesh(gun);*/
    cout << "\t Loaded!" << endl;


    app->loop(120); // 120 fps

    return 0;
}
