#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "TestCube.h"
#include "TestTriangle.h"
#include "SceneFormatParser.h"
#include "scope.h"
#include "FreeCamera.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "SunLight.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;


    Application *app = new Application("Conrad Engine", 1280, 720);
    if(!app->init()) {
        cout << "Error setting up SDL or context" << endl;
    }

    FreeCamera *camera = new FreeCamera(app->getInputManager());
    app->getRenderer()->setCamera(camera);

    Shader shader("shaders/advanced/materials.vert", "shaders/advanced/materials.frag");
    Shader depthShader("shaders/advanced/depth.vert", "shaders/advanced/depth.frag");

    app->getRenderer()->setShader(shader); // loads the shader
    app->getRenderer()->setDepthShader(depthShader);


    Uint32 start = SDL_GetTicks();

    SceneFormatParser parser("D:/GitHub/ConradGameEngine/Conrad/blender/testfile.scene");

    cout << "Loaded in " << SDL_GetTicks() - start << " ms" << endl;

    vector<StaticMesh *> *meshes = parser.getMeshes();
    for(int i = 0;i < meshes->size();i++) {
        app->getRenderer()->addMesh(meshes->at(i));
    }


    vector <AbstractLight *> *lights = parser.getLights();
    for(int i = 0;i < lights->size();i++) {
        app->getRenderer()->addLight(lights->at(i));
    }

    //PointLight *light = new PointLight(glm::vec3(5.0, 0.0, 3.0), glm::vec3(1.0), 1.0, false);
    //app->getRenderer()->addLight(light);
    //SpotLight *spot = new SpotLight(glm::vec3(-2.0, 0.0, 4.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 0.0, -0.5), 50.0, 60.0, 10.0, false, 0.08, 0.08, 100.0);
    //app->getRenderer()->addLight(spot);
    //app->getRenderer()->generateShadowMap(spot);


    /*SunLight *sun = new SunLight(glm::vec3(4.71196, 2.68324, 3.91369), glm::vec3(-1.0, 0.0, -1.0), glm::vec3(1.0, 0.8, 0.4), 1.0, true);
    app->getRenderer()->addLight(sun);
    app->getRenderer()->generateShadowMap(sun);*/


    app->loop(120); // 120 fps

    return 0;
}
