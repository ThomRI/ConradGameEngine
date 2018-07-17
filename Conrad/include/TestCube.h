#ifndef TESTCUBE_H
#define TESTCUBE_H

#include "StaticMesh.h"
#include <iostream>
#include <algorithm>

class TestCube : public StaticMesh
{
    public:
        TestCube(float size);
        virtual ~TestCube();

    protected:

    private:
};

#endif // TESTCUBE_H
