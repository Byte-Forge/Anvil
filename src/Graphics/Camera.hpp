//
// Created by stephan on 08.12.15.
//

#pragma once
#include "Frustum.hpp"
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace hpse
{
	enum Direction
	{
		FOREWARD,
		BACK,
		LEFT,
		RIGHT,
		ZOOM_IN,
		ZOOM_OUT
	};

    class Camera
    {
    public:
        Camera();
        ~Camera();

        void Update();
		void Move(glm::vec3 dir);
		void Move(Direction dir);
		void Rotate(float angle);
		void Rotate(Direction dir);
		void Zoom(Direction dir);
		void ScreenPosToWorldRay(glm::vec2 mouse_pos, glm::vec3& out_origin, glm::vec3& out_direction);

		inline const glm::vec3 GetLookAt()
		{
			return m_lookat;
		}

		inline const glm::vec3& GetPosition()
		{
			return m_position;
		}

		inline const glm::mat4& GetProjectionMatrix()
		{
			return m_proj;
		}

		inline const glm::mat4& GetViewMatrix()
		{
			return m_view;
		}

        inline const glm::mat4& GetViewProjectionMatrix()
        {
            return m_vp;
        }

        inline void SetFOV(double fov)
        {
            m_fov = fov;
        }

        inline void SetRatio(double ratio)
        {
            m_ratio = ratio;
        }

        inline void SetPosition(glm::vec3 pos)
        {
			m_position = pos;
        }

		inline std::unique_ptr<Frustum>& GetFrustum()
		{
			return m_frustum;
		}

		inline glm::vec3 &GetDirection()
		{
			return m_direction;
		}

    private:
		float speed = 1.0f;
		glm::vec3 m_position;
        glm::vec3 m_currentPos; 
		glm::vec3 m_direction;
        glm::vec3 m_lookat;
        glm::vec3 m_up;
        double m_fov; 
        double m_ratio; 

        glm::mat4 m_proj;
        glm::mat4 m_view;
        glm::mat4 m_vp;

		std::unique_ptr<Frustum> m_frustum;
    };
}


