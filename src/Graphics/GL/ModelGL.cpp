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
#include "../../Util.hpp"
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
	//glm::mat4 mod(1.0);
	for (Entity* e : m_entities)
	{
		if (e->GetInstances().size() > 0)
		{
			for (std::shared_ptr<Entity::Instance> i : e->GetInstances())
			{
				glUniformMatrix4fv(shader.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix()));
				glUniform4fv(shader.GetUniform("position"), 1, glm::value_ptr(glm::vec4(i->position, 1.0)));

				if (m_hierarchy != nullptr)
				{
					glUniform1iv(shader.GetUniform("parentIDs"), m_hierarchy->GetParentIDs().size(), reinterpret_cast<GLint*>(m_hierarchy->GetParentIDs().data()));	
					glUniformMatrix4fv(shader.GetUniform("pivots"), m_hierarchy->GetPivots().size(), GL_FALSE, glm::value_ptr(m_hierarchy->GetPivots().front()));
					//glUniform3fv(shader.GetUniform("centerPos"), 1, glm::value_ptr(m_hierarchy->GetCenterPos()));
				}

				for(const auto& it : m_meshes)
				{								
					glActiveTexture(GL_TEXTURE0); //albedo textures
					e->GetMaterial(it.second->GetName())->GetAlbedoTexture()->Bind();
					glUniform1i(shader.GetUniform("albedoTex"), 0);

					it.second->Render(shader);
				}
			}
		}
	}
}

void GL::ModelGL::Update()
{
	for (Entity* e : m_entities)
	{
		e->Update();
	}
}
