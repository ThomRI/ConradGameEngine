#include "AbstractCamera.h"

using namespace glm;

AbstractCamera::AbstractCamera()
{
    //ctor
}

AbstractCamera::AbstractCamera(vec3 position, vec3 shiftSpeed) :
    m_position(position), m_shiftSpeed(shiftSpeed)
{

}

/* #### MOVEMENTS #### */
void AbstractCamera::forward()
{
    m_position += m_orientation * m_shiftSpeed[FORWARD];
    update();
}

void AbstractCamera::back()
{
    m_position -= m_orientation * m_shiftSpeed[FORWARD];
    update();
}

void AbstractCamera::up()
{
    m_position += m_up * m_shiftSpeed[UP];
    update();
}

void AbstractCamera::down()
{
    m_position -= m_up * m_shiftSpeed[UP];
    update();
}

void AbstractCamera::left()
{
    m_position += m_transversal * m_shiftSpeed[TRANSVERAL];
    update();
}

void AbstractCamera::right()
{
    m_position -= m_transversal * m_shiftSpeed[TRANSVERAL];
    update();
}

void AbstractCamera::rotate(float dtheta, float dphi)
{
    /* Updating angles */
    m_theta += dtheta * (M_PI / 180) * m_y_sensitivity;
    m_phi   += dphi * (M_PI / 180) * m_x_sensitivity;

    /* Boundaries of theta (0; pi) */
    if(m_theta < ONE_DEGREE_RAD)             m_theta = ONE_DEGREE_RAD; // One degree before the limit so that the angle never becomes the boundary
    else if(m_theta > M_PI - ONE_DEGREE_RAD) m_theta = M_PI - ONE_DEGREE_RAD;

    if(m_up.x == 1.0) { // X up
        m_orientation.x = cos(m_theta);
        m_orientation.y = sin(m_theta) * sin(m_phi);
        m_orientation.z = sin(m_theta) * cos(m_phi);
    } else if(m_up.y == 1.0) { // Y up
        m_orientation.x = sin(m_theta) * cos(m_phi);
        m_orientation.y = cos(m_theta);
        m_orientation.z = sin(m_theta) * sin(m_phi);
    } else if(m_up.z == 1.0) { // Z up
        m_orientation.x = sin(m_theta) * sin(m_phi);
        m_orientation.y = sin(m_theta) * cos(m_phi);
        m_orientation.z = cos(m_theta);
    }

    update();
}

/* #### UPDATE #### */
void AbstractCamera::update()
{
    m_transversal = glm::normalize(glm::cross(m_up, m_orientation));
    m_lookAt = lookAt(m_position, m_position + m_orientation, m_up);
}

void AbstractCamera::move()
{
    // Virtual pure
}

/* #### SETTERS #### */

void AbstractCamera::setSpeed(vec3 speed)
{
    m_shiftSpeed = speed;
}

void AbstractCamera::setSpeed(float forwardSpeed, float transversalSpeed, float upSpeed)
{
    setSpeed(vec3(forwardSpeed, transversalSpeed, upSpeed));
}

void AbstractCamera::setPosition(vec3 position)
{
    m_position = position;
}

void AbstractCamera::setPosition(float x, float y, float z)
{
    setPosition(vec3(x, y, z));
}

/* #### GETTERS */
vec3 AbstractCamera::getUpVector()
{
    return m_up;
}

mat4 &AbstractCamera::get_lookat()
{
    return m_lookAt;
}

vec3 AbstractCamera::getPos()
{
    return m_position;
}

AbstractCamera::~AbstractCamera()
{
    //dtor
}
