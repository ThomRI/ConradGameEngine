#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "TestCube.h"
#include "TestTriangle.h"
#include "OBJ_Static_Handler.h"
#include "scope.h"
#include "FreeCamera.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;

    Application *app = new Application("Sexer", 1280, 720);
    if(!app->init()) {
        cout << "Error setting up SDL or context" << endl;
    }

    FreeCamera *camera = new FreeCamera(app->getInputManager());
    app->getRenderer()->setCamera(camera);

    Shader shader(string("shaders/advanced/materials.vert"), string("shaders/advanced/materials.frag"));
    //Shader shader(string("shaders/basic/light.vert"), string("shaders/basic/light.frag"));
    app->getRenderer()->setShader(shader); // loads the shader

    OBJ_Static_Handler sceneHandler("objects/nature.obj", "objects/nature.mtl");
    sceneHandler.load(true, true, true);

    app->getRenderer()->addMesh(sceneHandler.getMesh("Ground"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("BaseTree"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Tree"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cylinder"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Gun"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("tower"));

    app->loop(120); // 120 fps

    return 0;
}
