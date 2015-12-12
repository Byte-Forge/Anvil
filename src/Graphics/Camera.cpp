//
// Created by stephan on 08.12.15.
//
#include "Camera.hpp"
#include <iostream>

using namespace hpse;

Camera::Camera()
{
    m_up = glm::vec3(0.0, 1.0, 0.0);
	m_pos = glm::vec3(-80.0, 80.0, -80.0);
	m_lookat = glm::vec3(0.0, 0.0, 0.0);

    m_fov = 45.0;
    m_ratio = 800.0/600.0;
}

Camera::~Camera()
{

}

void Camera::Move(Direction dir)
{
	glm::vec3 direction = glm::normalize(m_lookat - m_pos);
	switch (dir)
	{
	case FOREWARD:
		m_pos += glm::vec3({ direction.x, 0.0, direction.z }) * speed * m_pos.y/10.0f;
		m_lookat += glm::vec3({direction.x, 0.0, direction.z}) * speed * m_pos.y / 10.0f;
		break;
	case BACK:
		m_pos -= glm::vec3({ direction.x, 0.0, direction.z }) * speed * m_pos.y / 10.0f;
		m_lookat -= glm::vec3({ direction.x, 0.0, direction.z }) * speed * m_pos.y / 10.0f;
		break;
	case LEFT:
		m_pos -= glm::vec3({ -direction.z, 0.0, direction.x }) * speed * m_pos.y / 10.0f;
		m_lookat -= glm::vec3({ -direction.z, 0.0, direction.x }) * speed * m_pos.y / 10.0f;
		break;
	case RIGHT:
		m_pos -= glm::vec3({ direction.z, 0.0, -direction.x }) * speed * m_pos.y / 10.0f;
		m_lookat -= glm::vec3({ direction.z, 0.0, -direction.x }) * speed * m_pos.y / 10.0f;
		break;
	}
}

void Camera::Rotate(Direction dir)
{
	float angle = 0.05f;
	glm::vec3 delta = m_pos - m_lookat;
	m_pos = m_lookat + glm::rotateY(delta, angle);
	switch (dir)
	{
	case (LEFT) :
		m_pos = m_lookat + glm::rotateY(delta, angle);
		break;
	case (RIGHT) :
		m_pos = m_lookat + glm::rotateY(delta, -angle);
		break;
	}
}

void Camera::Zoom(Direction dir)
{
	glm::vec3 direction = glm::normalize(m_pos - m_lookat);
	switch (dir)
	{
	case ZOOM_OUT:
		m_pos += direction  * speed;
		break;
	case ZOOM_IN:
		if (m_pos.y > 5.0)
			m_pos -= direction * speed;
		break;
	}
}

void Camera::Update()
{
    m_proj = glm::perspective(m_fov, m_ratio, 0.1, 10000.0);
    m_view = glm::lookAt(m_pos, m_lookat, m_up);
    m_vp = m_proj * m_view;
}