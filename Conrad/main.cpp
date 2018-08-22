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

    OBJ_Static_Handler sceneHandler("objects/lowpolymill.obj", "objects/lowpolymill.mtl");
    Uint32 start = SDL_GetTicks();
    sceneHandler.load(true, true, true);
    cout << "Loaded in " << SDL_GetTicks() - start << " ms" << endl;

    /*app->getRenderer()->addMesh(sceneHandler.getMesh("Ground"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cube"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cube1"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cube2"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Spaceship"));

    app->getRenderer()->addMesh(sceneHandler.getMesh("BaseTree"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Cylinder"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Tree"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Gun"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("tower"));
    app->getRenderer()->addMesh(sceneHandler.getMesh("Ground"));*/

    vector<StaticMesh *> meshes = sceneHandler.getAllMeshes();
    for(int i = 0;i < meshes.size();i++) {
        app->getRenderer()->addMesh(meshes.at(i));
    }


    //PointLight *light = new PointLight(glm::vec3(1.0, 0.0, 2.0), glm::vec3(1.0), 1.0, 0.005, true);
    SpotLight *spot = new SpotLight(glm::vec3(-3.33681, 0.0, 3.13254), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 0.0, -1.0), 25.0, 60.0, 1.0, true, 0.08, 0.08, 100.0);
    app->getRenderer()->addLight(spot);
    app->getRenderer()->generateShadowMap(spot);

    /*SunLight *sun = new SunLight(glm::vec3(4.71196, 2.68324, 3.91369), glm::vec3(0.0, 0.0, -1.0), glm::vec3(1.0), 0.08, false);
    app->getRenderer()->addLight(sun);
    app->getRenderer()->generateShadowMap(sun);*/

    app->loop(120); // 120 fps

    return 0;
}
