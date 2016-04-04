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
		if (e->GetInstances().size() > 0)
		{
			for (Entity::Instance i : e->GetInstances())
			{
				glUniformMatrix4fv(shader.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix()));
				glUniform4fv(shader.GetUniform("position"), 1, glm::value_ptr(i.position));

				for (std::map<std::string, std::shared_ptr<IMesh>>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
				{
					glActiveTexture(GL_TEXTURE0); //albedo textures
					e->GetMaterial(it->second->GetName())->GetAlbedoTexture()->Bind();
					glUniform1i(shader.GetUniform("albedoTex"), 0);

					it->second->Render(shader);
				}
			}
		}
	}
}

void GL::ModelGL::Update()
{
	for (std::map<std::string, std::shared_ptr<IMesh>>::iterator mesh = m_meshes.begin(); mesh != m_meshes.end(); ++mesh)
	{
		mesh->second->Update();
	}
}