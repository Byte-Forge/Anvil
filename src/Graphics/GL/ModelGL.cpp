/*
************************************
* Copyright (C) 2016 ByteForge
* ModelGL.cpp
************************************
*/

#include "ModelGL.hpp"
#include "MeshGL.hpp"
#include "../../Objects/Entity.hpp"
#include "../../Core.hpp"
#include "../Camera.hpp"
#include "../../Util.hpp"
#include "../../Objects/Instance.hpp"
#include "../../Graphics/Hierarchy.hpp"
#include "../../Graphics/IMesh.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>


using namespace anvil;

GL::ModelGL::ModelGL()
{

}

GL::ModelGL::~ModelGL()
{

}

int GL::ModelGL::Render(IShader& shader)
{
	int polygons = 0;
	for (std::shared_ptr<Instance> i : m_instances)
	{
		if (i->IsVisible())
		{
			bool useSkeleton = false;
			glUniformMatrix4fv(shader.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix()));
			glUniformMatrix4fv(shader.GetUniform("m"), 1, GL_FALSE, glm::value_ptr(i->GetMatrix()));

			if (m_hierarchy != nullptr)
			{
				useSkeleton = true;
				if (i->IsAnimated())
					glUniformMatrix4fv(shader.GetUniform("pivots"), m_hierarchy->GetPivots().size(), GL_FALSE, glm::value_ptr(m_hierarchy->GetPivots(i->GetAnimation(), i->GetAnimationTime()).front()));
				else 
					glUniformMatrix4fv(shader.GetUniform("pivots"), m_hierarchy->GetPivots().size(), GL_FALSE, glm::value_ptr(m_hierarchy->GetPivots().front()));
				//glUniform3fv(shader.GetUniform("centerPos"), 1, glm::value_ptr(m_hierarchy->GetCenterPos()));
			}
			glUniform1i(shader.GetUniform("useSkeleton"), useSkeleton);

			for (const auto& it : m_meshes)
			{
				const auto& m = i->GetMaterial(it.second->GetName());
				if (m != nullptr)
				{
					glm::vec2 offset = i->GetTexOffset(m->GetUPerSecond(), m->GetVPerSecond());
					glUniform2f(shader.GetUniform("texOffset"), offset.x, offset.y);
					glActiveTexture(GL_TEXTURE0); //albedo textures
					m->GetAlbedoTexture()->Bind();

					//glActiveTexture(GL_TEXTURE1); //normal textures
					//i->GetMaterial(it.second->GetName())->GetNormalTexture()->Bind();

					polygons += it.second->Render(shader);
				}
			}
		}
	}
	return polygons;
}

void GL::ModelGL::Update()
{
	
}
