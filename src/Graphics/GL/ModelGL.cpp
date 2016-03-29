/*
************************************
* Copyright (C) 2016 ByteForge
* ModelGL.cpp
************************************
*/

#include "ModelGL.hpp"
#include "MeshGL.hpp"
#include "../../Objects/Entity.hpp"
#include <iostream>
#include "../../Core.hpp"
#include "../Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace anvil;

GL::ModelGL::ModelGL()
{

}

GL::ModelGL::~ModelGL()
{

}

void GL::ModelGL::Render(IShader& shader)
{
	glm::mat4 mod(1.0);
	for (Entity* e : m_entities)
	{
		glUniformMatrix4fv(shader.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix()));
		for (std::shared_ptr<IMesh> mesh : m_meshes)
		{
			mesh->Render(shader);
		}
		/*
		for (Entity::Instance i : e->GetInstances())
		{
			glUniformMatrix4fv(shader.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix() * i.position));
			for (std::shared_ptr<IMesh> mesh : m_meshes)
			{
				mesh->Render(shader);
			}
		}
		*/
	}
}

void GL::ModelGL::Update()
{
	/*
	for (Entity* e : m_entities)
	{
		e->Update();
	}
	*/

	for (std::shared_ptr<IMesh> mesh : m_meshes)
	{
		mesh->Update(); 
	}
}