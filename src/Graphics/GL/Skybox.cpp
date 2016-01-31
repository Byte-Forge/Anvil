#include "Skybox.hpp"
#include "../../Core.hpp"

using namespace hpse;

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

	int index = 0;

	//front
	m_vertices.push_back(v1);
	m_vertices.push_back(v4);
	m_vertices.push_back(v8);

	m_vertices.push_back(v1);
	m_vertices.push_back(v8);
	m_vertices.push_back(v5);

	m_normals.push_back(n_front);
	m_normals.push_back(n_front);
	m_normals.push_back(n_front);

	m_normals.push_back(n_front);
	m_normals.push_back(n_front);
	m_normals.push_back(n_front);

	m_uvs.push_back({ 0.5, 0.66 });
	m_uvs.push_back({ 0.75, 0.66 });
	m_uvs.push_back({ 0.75, 0.33 });

	m_uvs.push_back({ 0.5, 0.66 });
	m_uvs.push_back({ 0.75, 0.33 });
	m_uvs.push_back({ 0.5, 0.33 });
	/*
	m_uvs.push_back({ v1.x, v1.y, v1.z, 5 });
	m_uvs.push_back({ v4.x, v4.y, v4.z, 5 });
	m_uvs.push_back({ v8.x, v8.y, v8.z, 5 });

	m_uvs.push_back({ v1.x, v1.y, v1.z, 5 });
	m_uvs.push_back({ v8.x, v8.y, v8.z, 5 });
	m_uvs.push_back({ v5.x, v5.y, v5.z, 5 });
	*/

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	//back
	m_vertices.push_back(v3);
	m_vertices.push_back(v2);
	m_vertices.push_back(v6);

	m_vertices.push_back(v3);
	m_vertices.push_back(v6);
	m_vertices.push_back(v7);

	m_normals.push_back(n_back);
	m_normals.push_back(n_back);
	m_normals.push_back(n_back);

	m_normals.push_back(n_back);
	m_normals.push_back(n_back);
	m_normals.push_back(n_back);

	m_uvs.push_back({ 0.0, 0.66 });
	m_uvs.push_back({ 0.25, 0.66 });
	m_uvs.push_back({ 0.25, 0.33 });

	m_uvs.push_back({ 0.0, 0.66 });
	m_uvs.push_back({ 0.25, 0.33 });
	m_uvs.push_back({ 0.0, 0.33 });

	/*
	m_uvs.push_back({ v3.x, v3.y, v3.z, 4 });
	m_uvs.push_back({ v2.x, v2.y, v2.z, 4 });
	m_uvs.push_back({ v6.x, v6.y, v6.z, 4 });

	m_uvs.push_back({ v3.x, v3.y, v3.z, 4 });
	m_uvs.push_back({ v6.x, v6.y, v6.z, 4 });
	m_uvs.push_back({ v7.x, v7.y, v7.z, 4 });
	*/

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	//left
	m_vertices.push_back(v2);
	m_vertices.push_back(v1);
	m_vertices.push_back(v5);

	m_vertices.push_back(v2);
	m_vertices.push_back(v5);
	m_vertices.push_back(v6);

	m_normals.push_back(n_left);
	m_normals.push_back(n_left);
	m_normals.push_back(n_left);

	m_normals.push_back(n_left);
	m_normals.push_back(n_left);
	m_normals.push_back(n_left);

	m_uvs.push_back({ 0.25, 0.66 });
	m_uvs.push_back({ 0.5, 0.66 });
	m_uvs.push_back({ 0.5, 0.33 });

	m_uvs.push_back({ 0.25, 0.66 });
	m_uvs.push_back({ 0.5, 0.33 });
	m_uvs.push_back({ 0.25, 0.33 });

	/*
	m_uvs.push_back({ v2.x, v2.y, v2.z, 1 });
	m_uvs.push_back({ v1.x, v1.y, v1.z, 1 });
	m_uvs.push_back({ v5.x, v5.y, v5.z, 1 });

	m_uvs.push_back({ v2.x, v2.y, v2.z, 1 });
	m_uvs.push_back({ v5.x, v5.y, v5.z, 1 });
	m_uvs.push_back({ v6.x, v6.y, v6.z, 1 });
	*/

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	//right
	m_vertices.push_back(v4);
	m_vertices.push_back(v3);
	m_vertices.push_back(v7);

	m_vertices.push_back(v4);
	m_vertices.push_back(v7);
	m_vertices.push_back(v8);

	m_normals.push_back(n_right);
	m_normals.push_back(n_right);
	m_normals.push_back(n_right);

	m_normals.push_back(n_right);
	m_normals.push_back(n_right);
	m_normals.push_back(n_right);

	m_uvs.push_back({ 0.75, 0.66 });
	m_uvs.push_back({ 1.0, 0.66 });
	m_uvs.push_back({ 1.0, 0.33 });

	m_uvs.push_back({ 0.75, 0.66 });
	m_uvs.push_back({ 1.0, 0.33 });
	m_uvs.push_back({ 0.75, 0.33 });

	/*
	m_uvs.push_back({ v4.x, v4.y, v4.z, 0 });
	m_uvs.push_back({ v3.x, v3.y, v3.z, 0 });
	m_uvs.push_back({ v7.x, v7.y, v7.z, 0 });

	m_uvs.push_back({ v4.x, v4.y, v4.z, 0 });
	m_uvs.push_back({ v7.x, v7.y, v7.z, 0 });
	m_uvs.push_back({ v8.x, v8.y, v8.z, 0 });
	*/

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	//top
	m_vertices.push_back(v5);
	m_vertices.push_back(v8);
	m_vertices.push_back(v7);

	m_vertices.push_back(v5);
	m_vertices.push_back(v7);
	m_vertices.push_back(v6);

	m_normals.push_back(n_top);
	m_normals.push_back(n_top); 
	m_normals.push_back(n_top);

	m_normals.push_back(n_top);
	m_normals.push_back(n_top);
	m_normals.push_back(n_top);

	m_uvs.push_back({ 0.25, 0.33 });
	m_uvs.push_back({ 0.5, 0.33 });
	m_uvs.push_back({ 0.5, 0.0 });

	m_uvs.push_back({ 0.25, 0.33 });
	m_uvs.push_back({ 0.5, 0.0 });
	m_uvs.push_back({ 0.25, 0.0 });

	/*
	m_uvs.push_back({ v5.x, v5.y, v5.z, 2 });
	m_uvs.push_back({ v8.x, v8.y, v8.z, 2 });
	m_uvs.push_back({ v7.x, v7.y, v7.z, 2 });

	m_uvs.push_back({ v5.x, v5.y, v5.z, 2 });
	m_uvs.push_back({ v7.x, v7.y, v7.z, 2 });
	m_uvs.push_back({ v6.x, v6.y, v6.z, 2 });
	*/

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	//bottom
	m_vertices.push_back(v2);
	m_vertices.push_back(v3);
	m_vertices.push_back(v4);

	m_vertices.push_back(v2);
	m_vertices.push_back(v4);
	m_vertices.push_back(v1);

	m_normals.push_back(n_bottom);
	m_normals.push_back(n_bottom);
	m_normals.push_back(n_bottom);

	m_normals.push_back(n_bottom);
	m_normals.push_back(n_bottom);
	m_normals.push_back(n_bottom);

	m_uvs.push_back({ 0.25, 0.99 });
	m_uvs.push_back({ 0.5, 0.99 });
	m_uvs.push_back({ 0.5, 0.66 });

	m_uvs.push_back({ 0.25, 0.99 });
	m_uvs.push_back({ 0.5, 0.66 });
	m_uvs.push_back({ 0.25, 0.66 });

	/*
	m_uvs.push_back({ v2.x, v2.y, v2.z, 3 });
	m_uvs.push_back({ v3.x, v3.y, v3.z, 3 });
	m_uvs.push_back({ v4.x, v4.y, v4.z, 3 });

	m_uvs.push_back({ v2.x, v2.y, v2.z, 3 });
	m_uvs.push_back({ v4.x, v4.y, v4.z, 3 });
	m_uvs.push_back({ v1.x, v1.y, v1.z, 3 });
	*/

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_faces.push_back(index++);
	m_faces.push_back(index++);
	m_faces.push_back(index++);

	m_diff = Core::GetCore()->GetResources()->GetTexture("skybox/skybox.dds");
	m_diffID = Core::GetCore()->GetGraphics()->GetRenderer()->GetSkyboxUniformLocation("DiffuseTextureSampler");

	m_matrixID = Core::GetCore()->GetGraphics()->GetRenderer()->GetSkyboxUniformLocation("MVP");
	m_CameraPos = Core::GetCore()->GetGraphics()->GetRenderer()->GetSkyboxUniformLocation("CameraPosition");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vbo = GL::Buffer(ARRAY_BUFFER);
	m_vbo.Bind();
	m_vbo.Update(m_vertices.size() * sizeof(glm::vec3), &m_vertices[0]);

	m_uvbo = GL::Buffer(ARRAY_BUFFER);
	m_uvbo.Bind();
	m_uvbo.Update(m_uvs.size() * sizeof(glm::vec2), &m_uvs[0]);

	m_nbo = GL::Buffer(ARRAY_BUFFER);
	m_nbo.Bind();
	m_nbo.Update(m_normals.size() * sizeof(glm::vec3), &m_normals[0]);

	m_fbo = GL::Buffer(ELEMENT_ARRAY_BUFFER);
	m_fbo.Bind();
	m_fbo.Update(m_faces.size() * sizeof(std::uint32_t), &m_faces[0]);

	glEnableVertexAttribArray(0);
	m_vbo.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	m_uvbo.Bind();
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	m_nbo.Bind();
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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

	glDrawElements(GL_TRIANGLES, (GLsizei)m_faces.size(), GL_UNSIGNED_INT, (void*)0);
}