/*
************************************
* Copyright (C) 2016 ByteForge
* IParticleSystem.hpp
************************************
*/
#pragma once
#include "IRenderable.hpp"
#include "../Core/IResource.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace anvil
{
	class IParticleSystem : public IRenderable, public IResource
	{
	protected:
		struct Particle
		{
			glm::vec3 pos,directory;
			glm::vec4 color;
			float speed,size;
			int lifetime; //in ms
			float cameradistance;

			bool operator<(Particle& that) 
			{
			// Sort in reverse order : far particles drawn first.
			return this->cameradistance > that.cameradistance;
			}
		};
	public:
		IParticleSystem();
		void Start();
		virtual void Render(int mode) = 0;
		virtual void Update();
		inline void SetLifetime(int lifetime)
		{
			m_lifetime = lifetime;
		}
		inline void SetSpawnRate(int rate)
		{
			m_spawnRate = rate;
		}
		inline void SetSpawnInterval(int interval)
		{
			m_spawnInterval = interval;
		}
	protected:
		int m_maxParticles;
		int m_spawnRate;
		int m_spawnInterval; //in ms
		int m_currentTime; //in ms
		int m_spawnTime;//in ms
		int m_lifetime;
		glm::vec3 m_center;
		std::vector<Particle> m_particles;
	};
}