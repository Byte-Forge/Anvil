/*
************************************
* Copyright (C) 2016 ByteForge
* Skybox.cpp
************************************
*/

#include "Skybox.hpp"
#include "../../Core.hpp"
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

	//normals
	m_normals.resize(36);
	std::fill(m_normals.begin(),	m_normals.begin() + 6,	n_front);
	std::fill(m_normals.begin()+6,	m_normals.begin() + 12, n_back);
	std::fill(m_normals.begin()+12, m_normals.begin() + 18, n_left);
	std::fill(m_normals.begin()+18, m_normals.begin() + 24, n_right);
	std::fill(m_normals.begin()+24, m_normals.begin() + 30, n_top);
	std::fill(m_normals.begin()+30, m_normals.end(),		n_bottom);
	

	std::vector<glm::vec2> uvs = {	{ 0.5,  0.66},{ 0.75, 0.66},{ 0.75, 0.33},//front
									{ 0.5,  0.66},{ 0.75, 0.33},{ 0.5,  0.33},
									{ 0.0,  0.66},{ 0.25, 0.66},{ 0.25, 0.33},//back
									{ 0.0,  0.66},{ 0.25, 0.33},{ 0.0,  0.33},
									{ 0.25, 0.66},{ 0.5,  0.66},{ 0.5,  0.33},//left
									{ 0.25, 0.66},{ 0.5,  0.33},{ 0.25, 0.33},
									{ 0.75, 0.66},{ 1.0,  0.66},{ 1.0,  0.33},//right
									{ 0.75, 0.66},{ 1.0,  0.33},{ 0.75, 0.33},
									{ 0.25, 0.33},{ 0.5,  0.33},{ 0.5,  0.0 },//top
									{ 0.25, 0.33},{ 0.5,  0.0 },{ 0.25, 0.0 },
									{ 0.25, 0.99},{ 0.5,  0.99},{ 0.5,  0.66},//bottom
									{ 0.25, 0.99},{ 0.5,  0.66},{ 0.25, 0.66} };

	m_uvs = uvs;

	m_diff = Core::GetCore()->GetResources()->GetTexture("skybox/skybox.dds");
	m_diffID = Core::GetCore()->GetGraphics()->GetRenderer()->GetSkyboxUniformLocation("DiffuseTextureSampler");

	m_matrixID = Core::GetCore()->GetGraphics()->GetRenderer()->GetSkyboxUniformLocation("MVP");
	m_CameraPos = Core::GetCore()->GetGraphics()->GetRenderer()->GetSkyboxUniformLocation("CameraPosition");


	m_vbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_vbo->Bind();
	m_vbo->Update(static_cast<unsigned int>(m_vertices.size() * sizeof(glm::vec3)), &m_vertices[0]);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_uvbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_uvbo->Bind();
	m_uvbo->Update(static_cast<unsigned int>(m_uvs.size() * sizeof(glm::vec2)), glm::value_ptr(m_uvs.front()));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_nbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_nbo->Bind();
	m_nbo->Update(static_cast<unsigned int>(m_normals.size() * sizeof(glm::vec3)), glm::value_ptr(m_normals.front()));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

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

void GL::Skybox::Render(int mode)
{
	glBindVertexArray(m_vao);
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix()));
	glm::vec3 pos = Core::GetCore()->GetCamera()->GetPosition();
	glUniform3f(m_CameraPos, pos.x, pos.y, pos.z);

	glActiveTexture(GL_TEXTURE0); //diffuse texture
	m_diff->Bind();
	glUniform1i(m_diffID, 0);

	m_fbo->Bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_faces.size()), GL_UNSIGNED_INT,nullptr);
}