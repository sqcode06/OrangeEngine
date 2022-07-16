#include "OrangeEngineCore/Camera.h"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace OrangeEngine
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, const ProjectionMode projectionMode)
		: m_position(position),
		  m_rotation(rotation),
		  m_projection_mode(projectionMode)
	{
		update_view_matrix();
		update_projection_matrix();
	}

	void Camera::update_view_matrix()
	{
		const glm::mat3 rotation_matrix_x = glm::rotate(glm::mat4(1.0f), -glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		const glm::mat3 rotation_matrix_y = glm::rotate(glm::mat4(1.0f), -glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		const glm::mat3 rotation_matrix_z = glm::rotate(glm::mat4(1.0f), -glm::radians(m_rotation.z), glm::vec3(0, 0, 1));

		const glm::mat3 euler_rotation_matrix = rotation_matrix_x * rotation_matrix_y * rotation_matrix_z;
		m_direction = glm::normalize(euler_rotation_matrix * s_world_forward);
		m_right = glm::normalize(euler_rotation_matrix * s_world_right);
		m_up = glm::cross(m_right, m_direction);

		m_view_matrix = glm::lookAt(m_position, m_position + m_direction, m_up);
	}

	void Camera::update_projection_matrix()
	{
		if (m_projection_mode == ProjectionMode::Perspective)
		{
			m_projection_matrix = glm::perspective<float>(glm::radians(60.f), 16.f/9.f, 0.1f, 30.f);
		}
		else
		{
			m_projection_matrix = glm::ortho<float>(-5.f, 5.f, -5.f, 5.f, 0.1f, 30.f);
		}
	}

	void Camera::set_position(const glm::vec3& position)
	{
		m_position = position;
		update_view_matrix();
	}

	void Camera::set_rotation(const glm::vec3& rotation)
	{
		m_rotation = rotation;
		update_view_matrix();
	}

	void Camera::set_position_rotation(const glm::vec3& position, const glm::vec3& rotation)
	{
		m_position = position;
		m_rotation = rotation;
		update_view_matrix();
	}

	void Camera::set_projection_mode(const ProjectionMode projectionMode)
	{
		m_projection_mode = projectionMode;
		update_projection_matrix();
	}

	void Camera::move_forward(const float offset)
	{
		m_position += m_direction * offset;
		update_view_matrix();
	}

	void Camera::move_right(const float offset)
	{
		m_position += m_right * offset;
		update_view_matrix();
	}

	void Camera::move_up(const float offset)
	{
		m_position += m_up * offset;
		update_view_matrix();
	}

	void Camera::move_and_rotate(const glm::vec3& movementOffset,
		const glm::vec3& rotationOffset)
	{
		m_position += m_direction * movementOffset.x;
		m_position += m_right * movementOffset.y;
		m_position += m_up * movementOffset.z;
		m_rotation += rotationOffset;
		update_view_matrix();
	}
}