/*
************************************
* Copyright (C) 2016 ByteForge
* Skybox.cpp
************************************
*/

#include "SkyboxGL.hpp"
#include "../../Core.hpp"
#include "../../Core/ResourceHandler.hpp"
#include "../Camera.hpp"
#include <numeric>

using namespace anvil;

GL::Skybox::Skybox()
{
	float size = 1.0f;

	glm::vec3 v1 = { -size, -size, -size };
	glm::vec3 v2 = { -size, -size,  size };
	glm::vec3 v3 = {  size, -size,  size };
	glm::vec3 v4 = {  size, -size, -size };

	glm::vec3 v5 = { -size,  size, -size };
	glm::vec3 v6 = { -size,  size,  size };
	glm::vec3 v7 = {  size,  size,  size };
	glm::vec3 v8 = {  size,  size, -size };

	glm::vec3 n_bottom = {0.0, 1.0, 0.0};
	glm::vec3 n_top = { 0.0, -1.0, 0.0 };
	glm::vec3 n_left = { 1.0, 0.0, 0.0 };
	glm::vec3 n_right = { -1.0, 0.0, 0.0 };
	glm::vec3 n_front = { 0.0, 0.0, 1.0 };
	glm::vec3 n_back = { 0.0, 0.0, -1.0 };

	//vertices
	std::vector<glm::vec3> vertices{v1,v4,v8,v1,v8,v5, //front
									v3,v2,v6,v3,v6,v7, //back
									v2,v1,v5,v2,v5,v6, //left
									v4,v3,v7,v4,v7,v8, //right
									v5,v8,v7,v5,v7,v6, //top
									v2,v3,v4,v2,v4,v1 }; //bottom
	m_vertices = vertices;

	//faces
	m_faces.resize(36);
	std::iota(m_faces.begin(), m_faces.end(), 0);


	m_diff = Core::GetCore()->GetResources()->GetTexture("textures/skybox/skybox.dds");
	
	m_vbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_vbo->Bind();
	m_vbo->Update(static_cast<unsigned int>(m_vertices.size() * sizeof(glm::vec3)), &m_vertices[0]);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_fbo = std::make_unique<GL::Buffer>(ELEMENT_ARRAY_BUFFER);
	m_fbo->Bind();
	m_fbo->Update(static_cast<unsigned int>(m_faces.size() * sizeof(std::uint32_t)),&m_faces.front());
}

GL::Skybox::~Skybox()
{
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
}

void GL::Skybox::Update()
{

}

size_t GL::Skybox::Render(IShader& shader, bool minimal)
{
	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(m_vao);

	glActiveTexture(GL_TEXTURE1); //diffuse texture
	m_diff->Bind();
	glUniform1i(shader.GetUniform("skybox"), 1);

	m_fbo->Bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_faces.size()), GL_UNSIGNED_INT,nullptr);

	glEnable(GL_DEPTH_TEST);

	return m_faces.size()/3;
}