#include <iostream>
#include "Application.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;

    Application *app = new Application("Sexer", 640, 480);
    cout << app->init() << endl;


    return 0;
}
