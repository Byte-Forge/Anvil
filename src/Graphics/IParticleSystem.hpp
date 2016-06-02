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
	/**
	 * @class	IParticleSystem
	 *
	 * @brief	A particle system.
	 */
	class IParticleSystem : public IRenderable, public IResource
	{
	protected:

		/**
		 * @struct	Particle
		 *
		 * @brief	A particle.
		 */
		struct Particle
		{
			glm::vec3 pos,directory;
			glm::vec4 color;
			float speed,size;
			int lifetime; //in ms
			float cameradistance;

			/**
			 * @fn	bool operator<(Particle& that)
			 *
			 * @brief	Sort in reverse order : far particles drawn first.
			 * 			
			 * @param [in,out]	that	The that.
			 *
			 * @return	true if the first parameter is less than the second.
			 */
			bool operator<(Particle& that) 
			{
				return this->cameradistance > that.cameradistance;
			}
		};
		 
	public:

		/**
		 * @fn	IParticleSystem::IParticleSystem();
		 *
		 * @brief	Default constructor.
		 */
		IParticleSystem();

		/**
		 * @fn	void IParticleSystem::Start();
		 *
		 * @brief	Starts this object.
		 */
		void Start();

		/**
		 * @fn	virtual void IParticleSystem::Render(IShader& shader) = 0;
		 *
		 * @brief	Renders the given shader.
		 *
		 * @param [in,out]	shader	The shader.
		 *
		 * @return  returns the number of drawn polygons
		 */
		virtual int Render(IShader& shader) = 0;

		/**
		 * @fn	virtual void IParticleSystem::Update();
		 *
		 * @brief	Updates this object.
		 */
		virtual void Update();

		inline void SetLifetime(int lifetime) { m_lifetime = lifetime; }
		inline void SetSpawnRate(int rate) { m_spawnRate = rate; }
		inline void SetSpawnInterval(int interval) { m_spawnInterval = interval; }

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