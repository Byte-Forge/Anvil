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
#include "../../Graphics.hpp"
#include "../../Graphics/IRenderer.hpp"
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

int GL::ModelGL::Render(IShader& shader, bool minimal)
{
	int polygons = 0;
	for (const auto i : m_instances)
	{
		if (i->IsVisible())
		{
			bool useSkeleton = false;
			glUniformMatrix4fv(shader.GetUniform("m"), 1, GL_FALSE, glm::value_ptr(i->GetMatrix()));

			if (m_hierarchy != nullptr)
			{
				useSkeleton = true;
				if (i->IsAnimated())
					glUniformMatrix4fv(shader.GetUniform("pivots"), m_hierarchy->GetPivots().size(), GL_FALSE, glm::value_ptr(m_hierarchy->GetPivots(i->GetAnimation(), i->GetAnimationTime()).front()));
				else 
					glUniformMatrix4fv(shader.GetUniform("pivots"), m_hierarchy->GetPivots().size(), GL_FALSE, glm::value_ptr(m_hierarchy->GetPivots().front()));
			}
			glUniform1i(shader.GetUniform("useSkeleton"), useSkeleton);

			for (const auto& it : m_meshes)
			{
				const auto& m = i->GetMaterial(it.second->GetName());
				if (m != nullptr)
				{
					glActiveTexture(GL_TEXTURE0); //albedo textures
					m->GetAlbedoTexture()->Bind();
					glUniform1i(shader.GetUniform("albedoTex"), 0);

					if (!minimal)
					{
						glActiveTexture(GL_TEXTURE1); //normal textures
						m->GetNormalTexture()->Bind();
						glUniform1i(shader.GetUniform("normalTex"), 1);

						glActiveTexture(GL_TEXTURE2); //spec textures
						m->GetSpecularTexture()->Bind();
						glUniform1i(shader.GetUniform("specularTex"), 2);

						glActiveTexture(GL_TEXTURE3); //disp textures
						m->GetDisplacementTexture()->Bind();
						glUniform1i(shader.GetUniform("displacementTex"), 3);

						glActiveTexture(GL_TEXTURE4); //ambi textures
						m->GetAmbientOcclusionTexture()->Bind();
						glUniform1i(shader.GetUniform("ambientTex"), 4);

						glm::vec2 offset = i->GetTexOffset(m->GetUPerSecond(), m->GetVPerSecond());
						glUniform2f(shader.GetUniform("texOffset"), offset.x, offset.y);
					}

					polygons += it.second->Render(shader, minimal);
				}
			}
		}
	}
	return polygons;
}

void GL::ModelGL::Update()
{
	
}
