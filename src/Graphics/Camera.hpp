/*
************************************
* Copyright (C) 2016 ByteForge
* Camera.hpp
************************************
*/

#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Frustum.hpp"

namespace anvil
{
	/**
	 * @enum	Direction
	 *
	 * @brief	Values that represent directions.
	 */
	enum Direction
	{
		FOREWARD,
		BACK,
		LEFT,
		RIGHT,
		ZOOM_IN,
		ZOOM_OUT
	};

    /**
     * @class	Camera
     *
     * @brief	A camera class to navigate in 3D space
     */
    class Camera
    {
    public:
		/**
		* @fn	Camera::Camera();
		*
		* @brief	Default constructor.
		*/
        Camera();

		/**
		* @fn	Camera::Camera();
		*
		* @brief	Destructor.
		*/
        ~Camera();

        /**
         * @fn	void Camera::Update();
         *
         * @brief	Updates the camera, which will recalculate internal matrices etc.
         */
        void Update();

		/**
		 * @fn	void Camera::Move(glm::vec3 dir);
		 *
		 * @brief	Moves the camera to the given directory
		 *
		 * @param	dir	The directory where we move as a 3-dimensional vector.
		 */
		void Move(glm::vec3 dir);

		/**
		 * @fn	void Camera::Move(Direction dir);
		 *
		 * @brief	Moves the camera to the given directory
		 *
		 * @param	dir	The directory where we move as Direction enum 
		 */
		void Move(Direction dir);

		/**
		 * @fn	void Camera::Rotate(float angle);
		 *
		 * @brief	Rotates the camera by the given angle
		 *
		 * @param	angle	The angle we will rotate.
		 */
		void Rotate(float angle);

		/**
		 * @fn	void Camera::Rotate(Direction dir);
		 *
		 * @brief	Rotates the given dir.
		 *
		 * @param	dir	The directory around we will rotate by a fixed angle.
		 */
		void Rotate(Direction dir);

		/**
		 * @fn	void Camera::Zoom(Direction dir);
		 *
		 * @brief	Zooms the camera in or out
		 *
		 * @param	dir	The dir.
		 */
		void Zoom(Direction dir);

		/**
		 * @fn	void Camera::Zoom(int value);
		 *
		 * @brief	Zooms the camera in or out
		 *
		 * @param	value	The value we will zoom in or out.
		 */
		void Zoom(int value);

		/**
		 * @fn	void Camera::ScreenPosToWorldRay(glm::vec2 mouse_pos, glm::vec3& out_origin, glm::vec3& out_direction);
		 *
		 * @brief	This will calculate a world ray from a given screen position
		 *
		 * @param	mouse_pos			 	The mouse position.
		 * @param [in,out]	out_origin   	The out origin.
		 * @param [in,out]	out_direction	The out direction.
		 */
		void ScreenPosToWorldRay(glm::vec2 mouse_pos, glm::vec3& out_origin, glm::vec3& out_direction);

		inline const glm::vec3 GetLookAt() { return m_lookat; }
		inline const glm::vec3& GetPosition() { return m_position; }
		inline const glm::mat4& GetProjectionMatrix() { return m_proj; }
		inline const glm::mat4& GetViewMatrix() { return m_view; }
		inline const glm::mat4& GetViewProjectionMatrix() { return m_vp; }
		inline void SetFOV(double fov) { m_fov = fov; }
        inline void SetRatio(double ratio) { m_ratio = ratio; }
        inline void SetPosition(glm::vec3 pos) { m_position = pos; }
		inline std::unique_ptr<Frustum>& GetFrustum() { return m_frustum; }
		inline glm::vec3 &GetDirection() { return m_direction; }

    private:
		float m_speed = 50.0f; //Movement per second
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