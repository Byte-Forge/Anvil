/*
************************************
* Copyright (C) 2016 ByteForge
* IModel.hpp
************************************
*/

#pragma once
#include "IRenderable.hpp"
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <glm/glm.hpp>
#include "../Core/IResource.hpp"
#include "../Graphics/IRenderable.hpp"


namespace anvil
{
	class Instance;
	class Hierarchy;
	class IMesh;

	/**
	 * @class	IModel
	 *
	 * @brief	A model. Consists of one or more meshes.
	 */
	class IModel : public IResource, public IRenderable
	{
	public:

		/**
		 * @struct	BoundingVolume
		 *
		 * @brief	A bounding volume.
		 */
		struct BoundingVolume
		{
			glm::vec4 center;
		};

		/**
		 * @struct	Box
		 *
		 * @brief	A bounding box.
		 */
		struct BoundingBox : BoundingVolume
		{
			glm::f32vec3 extend;
		};

		/**
		 * @struct	Sphere
		 *
		 * @brief	A bounding sphere.
		 */
		struct BoundingSphere : BoundingVolume
		{
			glm::float32 radius;
		};

		/**
		 * @fn	virtual void IModel::Update() = 0;
		 *
		 * @brief	Updates this object.
		 */
		virtual void Update() = 0;

		/**
		 * @fn	virtual int IModel::Render(IShader& shader, bool minimal) = 0;
		 *
		 * @brief	Renders the given shader.
		 *
		 * @param [in,out]	shader	The shader.
		 * @param	minimal if it should render with minimal settings
		 *
		 * @return  returns the number of drawn polygons
		 */
		virtual int Render(IShader& shader, bool minimal) = 0;

		inline void SetHierarchy(std::shared_ptr<Hierarchy> hierarchy) { m_hierarchy = hierarchy; }
		inline std::shared_ptr<Hierarchy> GetHierarchy() { return m_hierarchy; }
		inline void AddMesh(std::string name, std::shared_ptr<IMesh> mesh) { m_meshes.insert({ name, mesh }); }
		inline void SetBoundingBox(BoundingBox box) { m_box = box; }
		inline void SetBoundingSphere(BoundingSphere sphere) { m_sphere = sphere; }
		inline void AddInstance(std::shared_ptr<Instance> i) { m_instances.insert(i); }
		inline void RemoveInstance(std::shared_ptr<Instance> i) { m_instances.erase(i); }
		inline float GetSphereRadius() { return m_sphere.radius; }
		inline glm::vec4 GetSphereCenter() { return m_sphere.center; }
 
	protected:
		std::shared_ptr<Hierarchy> m_hierarchy; //nullpointer if no hierarchy is needed
		std::map<std::string, std::shared_ptr<IMesh>> m_meshes;
		BoundingBox m_box;
		BoundingSphere m_sphere;
		std::set<std::shared_ptr<Instance>> m_instances;
	};
}