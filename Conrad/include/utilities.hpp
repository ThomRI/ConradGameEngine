#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

#include "StaticMesh.h"

using namespace std;

/*!
 *  \file utilities.hpp
 *  \brief This file is used to define useful static functions for (for now) the rendering engine
 */

/*!
 *  \brief Loads a .obj file treated as a static mesh (environment, terrain, ...)
 *  \return (StaticMesh) The mesh, loaded or not depending on the load parameter value.
 */
static StaticMesh loadOBJ_static(string filepath, bool load = true)
{

}

#endif // UTILITIES_HPP_INCLUDED
