//
// Created by stephan on 08.12.15.
//
#include "Camera.hpp"
#include <iostream>

using namespace hpse;

Camera::Camera()
{
    m_up = glm::vec3(0.0,1.0,0.0);
    m_fov = 45.0;
    m_rotation = glm::quat(1.0,0.0,0.0,0.0);
    m_ratio = 800.0/600.0;
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 direction)
{
	m_pos += direction * speed; //* delta_time
	std::cout << m_pos.x << ", " << m_pos.y << ", " << m_pos.z << std::endl;
}

void Camera::Rotate()
{
	std::cout << "rotate" << std::endl;
	//TODO: rotate the camera around the point its pointing to (go hight down and hight in direction of camera)
}

void Camera::Zoom(int direction)
{
	std::cout << direction << std::endl;
	if (direction == 1)
		m_pos += m_lookat;
	else if ( direction == -1)
		m_pos -= m_lookat;
	std::cout << m_pos.x << ", " << m_pos.y << ", " << m_pos.z << std::endl;
}

void Camera::Update()
{
    m_proj = glm::perspective(m_fov, m_ratio, 0.1, 100.0);
    m_view = glm::lookAt(m_pos, m_lookat, m_up);
    m_vp = m_view * m_proj;
}