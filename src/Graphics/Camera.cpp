//
// Created by stephan on 08.12.15.
//
#include "Camera.hpp"
#include <iostream>

using namespace hpse;

Camera::Camera()
{
    m_up = glm::vec3(0.0, 1.0, 0.0);
	m_pos = glm::vec3(-30.0, 30.0, -30.0);
	m_lookat = glm::vec3(0.0, 0.0, 0.0);

    m_fov = 45.0;
    m_ratio = 800.0/600.0;
	m_proj = glm::perspective(m_fov, m_ratio, 0.1, 1000.0);

	m_frustum = std::make_unique<Frustum>();
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 dir)
{
	//add also the up direction
	glm::vec3 foreward = glm::vec3({ m_direction.x, 0.0, m_direction.z });
	glm::vec3 right = glm::vec3({ m_direction.z, 0.0, -m_direction.x });
	//glm::vec3 up = glm::vec3({  });
	glm::vec3 offset = (dir.x * right + dir.z * foreward) * speed * m_pos.y / 10.0f;
	m_pos += offset;
	m_lookat += offset;
}

void Camera::Move(Direction dir)
{
	glm::vec3 offset;
	switch (dir)
	{
	case FOREWARD:
		offset = glm::vec3({ m_direction.x, 0.0, m_direction.z }) * speed * m_pos.y / 10.0f;
		m_pos += offset;
		m_lookat += offset;
		break;
	case BACK:
		offset = glm::vec3({ m_direction.x, 0.0, m_direction.z }) * speed * m_pos.y / 10.0f;
		m_pos -= offset;
		m_lookat -= offset;
		break;
	case LEFT:
		offset = glm::vec3({ -m_direction.z, 0.0, m_direction.x }) * speed * m_pos.y / 10.0f;
		m_pos -= offset;
		m_lookat -= offset;
		break;
	case RIGHT:
		offset = glm::vec3({ m_direction.z, 0.0, -m_direction.x }) * speed * m_pos.y / 10.0f;
		m_pos -= offset;
		m_lookat -= offset;
		break;
	}
}

void Camera::Rotate(float angle)
{
	glm::vec3 delta = m_pos - m_lookat;
	m_pos = m_lookat + glm::rotateY(delta, angle);
}

void Camera::Rotate(Direction dir)
{
	float angle = 0.05f;
	switch (dir)
	{
	case (LEFT) :
		Rotate(angle);
		break;
	case (RIGHT) :
		Rotate(-angle);
		break;
	}
}

void Camera::Zoom(Direction dir)
{
	switch (dir)
	{
	case ZOOM_OUT:
		m_pos -= m_direction + m_direction;
		break;
	case ZOOM_IN:
		if (m_pos.y > 3)
			m_pos += m_direction + m_direction;
		break;
	}
}

void Camera::Update()
{
	m_direction = glm::normalize(m_lookat - m_pos);
    m_view = glm::lookAt(m_pos, m_lookat, m_up);
    m_vp = m_proj * m_view;

	m_frustum->Recalculate(m_view, m_proj);
}

//out_origin starts at the near plane NOT the camera position
void Camera::ScreenPosToWorldRay(glm::vec2 mouse_pos, glm::vec3& out_origin, glm::vec3& out_direction)
{
	/*
	glm::vec2 resolution = Core::GetCore()->GetResolution();

	glm::vec4 ray_start(
	((float)mouse_pos.x / (float)resolution.x - 0.5f) * 2.0f,
	((float)mouse_pos.y / (float)resolution.y - 0.5f) * 2.0f,
	-1.0, 1.0f);

	glm::vec4 ray_end(
	((float)mouse_pos.x / (float)resolution.x - 0.5f) * 2.0f,
	((float)mouse_pos.y / (float)resolution.y - 0.5f) * 2.0f,
	0.0, 1.0f);

	glm::mat4 InverseProjectionMatrix = glm::inverse(Core::GetCore()->GetCamera()->GetProjectionMatrix());
	glm::mat4 InverseViewMatrix = glm::inverse(Core::GetCore()->GetCamera()->GetViewMatrix());

	glm::vec4 ray_start_camera = InverseProjectionMatrix * ray_start;
	ray_start_camera /= ray_start_camera.w;
	glm::vec4 ray_start_world = InverseViewMatrix       * ray_start_camera;
	ray_start_world /= ray_start_world.w;
	glm::vec4 ray_end_camera = InverseProjectionMatrix * ray_end;
	ray_end_camera /= ray_end_camera.w;
	glm::vec4 ray_end_world = InverseViewMatrix       * ray_end_camera;
	ray_end_world /= ray_end_world.w;

	glm::vec3 ray_dir_world(ray_end_world - ray_start_world);

	out_origin = glm::vec3(ray_start_world);
	out_direction = glm::normalize(ray_dir_world);
	*/
	//std::cout << mouse_pos.x << ", " << mouse_pos.y << std::endl;

	out_origin = m_pos + m_direction;
	out_direction = m_direction;
}