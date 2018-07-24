#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "TestCube.h"
#include "TestTriangle.h"
#include "OBJ_Static_Handler.h"
#include "scope.h"
#include "FreeCamera.h"
#include "PointLight.h"
#include "SpotLight.h"

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

    PointLight *light1 = new PointLight(glm::vec3(-7.0, 6.0, 3.5), glm::vec3(1.0), 1.5, 0.05);
    PointLight *light2 = new PointLight(glm::vec3(11.0, -10.0, 3.5), glm::vec3(1.0), 1.5, 0.05);
    SpotLight *light3 = new SpotLight(glm::vec3(0.0, 0.0, 4.0), glm::vec3(1.0), glm::vec3(0.0, 0.0, -1.0), 45.0f, 1.5f, 0.05f);
    app->getRenderer()->addLight(light1);
    app->getRenderer()->addLight(light2);
    app->getRenderer()->addLight(light3);

    OBJ_Static_Handler sceneHandler("objects/plane.obj", "objects/plane.mtl");
    sceneHandler.load(true, true, true);

    app->getRenderer()->addMesh(sceneHandler.getMesh("Ground"));
    /*app->getRenderer()->addMesh(sceneHandler.getMesh("BaseTree"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Tree"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cylinder"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Gun"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("tower"));*/

    app->loop(120); // 120 fps

    return 0;
}
