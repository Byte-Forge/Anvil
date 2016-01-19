#include "RendererGui.hpp"
#include <glm/glm.hpp>
#include "../../Core.hpp"
#include "../../Util/stb_image.h"
using namespace hpse;

class GLGeometry
{
public:
	GLuint m_vbo, m_ibo, m_texture;
	int m_numVerts;

	GLGeometry() : m_vbo(0), m_ibo(0)
	{
	};

	~GLGeometry()
	{
		if (m_vbo)
			glDeleteBuffers(1, &m_vbo);

		if (m_ibo)
			glDeleteBuffers(1, &m_ibo);

		m_vbo = m_ibo = 0;
	};
};

struct Vertex
{
	glm::vec2 Position, TexCoord;
	glm::vec4 Color;
};


GL::RendererGui::RendererGui(sf::Window * window) : m_window(window), m_translID(0), m_orthoID(0)
{
	
}

void GL::RendererGui::RenderGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices,
	int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f & translation)
{
	Rocket::Core::CompiledGeometryHandle gh = CompileGeometry(vertices,
		num_vertices, indices, num_indices, texture);
	RenderCompiledGeometry(gh, translation);
	ReleaseCompiledGeometry(gh);
}

Rocket::Core::CompiledGeometryHandle GL::RendererGui::CompileGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	std::vector<Vertex> data(num_vertices);

	for (unsigned long i = 0; i < data.size(); i++)
	{
		data[i].Position = *(glm::vec2*)&vertices[i].position;
		data[i].TexCoord = *(glm::vec2*)&vertices[i].tex_coord;
		data[i].Color = glm::vec4((float)vertices[i].colour.red / 255.f,
			(float)vertices[i].colour.green / 255.f,
			(float)vertices[i].colour.blue / 255.f,
			(float)vertices[i].colour.alpha / 255.f);
	};

	GLGeometry* geometry = new GLGeometry();
	geometry->m_numVerts = num_indices;
	
	glGenBuffers(1, &geometry->m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertices, &data[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	geometry->m_texture = texture;

	return Rocket::Core::CompiledGeometryHandle(geometry);
}

void GL::RendererGui::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle handle, const Rocket::Core::Vector2f & translation)
{
	m_translID = static_cast<GLuint>(Core::GetCore()->GetGraphics()->GetRenderer()->GetGuiUniformLocation("translation"));
	m_orthoID = static_cast<GLuint>(Core::GetCore()->GetGraphics()->GetRenderer()->GetGuiUniformLocation("ortho"));
	m_samplerID = static_cast<GLuint>(Core::GetCore()->GetGraphics()->GetRenderer()->GetGuiUniformLocation("tex"));

	GLGeometry* geometry = reinterpret_cast<GLGeometry*>(handle);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vbo);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

	// Colors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_ibo);
	glBindTexture(GL_TEXTURE_2D, geometry->m_texture);

	glUniform1i(m_samplerID, 0);
	glUniform2f(m_translID, translation.x, translation.y);
	auto* mat = glm::value_ptr(Core::GetCore()->GetGraphics()->GetOrtho());
	glUniformMatrix4fv(m_orthoID, 1, GL_FALSE,mat);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, geometry->m_numVerts, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void GL::RendererGui::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	delete (GLGeometry*)geometry;
}

void GL::RendererGui::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

void GL::RendererGui::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, m_window->getSize().y - (y + height), width, height);
}

bool GL::RendererGui::LoadTexture(Rocket::Core::TextureHandle & texture_handle, Rocket::Core::Vector2i & texture_dimensions, const Rocket::Core::String & source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (file_handle == NULL)
		return false;

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	unsigned char* buffer = new unsigned char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	
	unsigned char *data = stbi_load_from_memory(buffer, buffer_size,&texture_dimensions.x, &texture_dimensions.y, NULL, 0);
	if (data == NULL)
		return false;
	
	GLuint handle = 0;
	glGenTextures(1, &handle);
	texture_handle = handle;
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_dimensions.x, texture_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

	return true;
}

bool GL::RendererGui::GenerateTexture(Rocket::Core::TextureHandle & texture_handle, const Rocket::Core::byte * source, const Rocket::Core::Vector2i & source_dimensions)
{
	GLuint handle = 0;
	glGenTextures(1, &handle);
	texture_handle = handle;
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);

	return true;
}

void GL::RendererGui::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	glDeleteTextures(1, &texture_handle);
	texture_handle = 0;
}
