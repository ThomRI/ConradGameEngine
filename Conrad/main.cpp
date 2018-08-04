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
#include "SunLight.h"

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

    Shader shader("shaders/advanced/materials.vert", "shaders/advanced/materials.frag");
    Shader depthShader("shaders/advanced/depth.vert", "shaders/advanced/depth.frag");

    app->getRenderer()->setShader(shader); // loads the shader
    app->getRenderer()->setDepthShader(depthShader);

    //SpotLight *light3 = new SpotLight(glm::vec3(0.0, 0.0, 4.0), glm::vec3(1.0), glm::vec3(0.0, 0.0, -1.0), 45.0f, 1.5f, 0.05f);
    //app->getRenderer()->addLight(light1);

    OBJ_Static_Handler sceneHandler("objects/shadow_testscene.obj", "objects/shadow_testscene.mtl");
    sceneHandler.load(true, true, true);

    app->getRenderer()->addMesh(sceneHandler.getMesh("Ground"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cube"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cube1"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cube2"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Spaceship"));


    SunLight *sun = new SunLight(glm::vec3(3.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, -1.0), glm::vec3(1.0), 1.0, true);
    //PointLight *light = new PointLight(glm::vec3(1.0, 0.0, 2.0), glm::vec3(1.0), 1.0, 0.005, true);
    SpotLight *spot = new SpotLight(glm::vec3(6.0, 0.2, 9.0), glm::vec3(1.0, 0.2, 0.2), glm::vec3(-1.0, 1.0, -1.5), 20.0, 1.0, 0.005, false);
    app->getRenderer()->addLight(spot);
    app->getRenderer()->addLight(sun);
    app->getRenderer()->generateShadowMap(spot);
    app->getRenderer()->generateShadowMap(sun);

    app->loop(120); // 120 fps

    return 0;
}
