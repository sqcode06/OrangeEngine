#pragma once

#include "Voxel.h"

#include <vector>

namespace OrangeEngine
{
	class GameObject
	{
	public:
		GameObject(Position position, Rotation rotation);
		~GameObject();

		GameObject(const GameObject& game_object);
		GameObject& operator=(const GameObject& game_object);
		GameObject(GameObject&& game_object) noexcept;
		GameObject& operator=(GameObject&& game_object) noexcept;

		void add_voxel(Voxel& voxel);
		void merge(GameObject& game_object);

		void add_pos_x(float x);
		void add_pos_y(float y);
		void add_pos_z(float z);
		void add_rot_x(float x);
		void add_rot_y(float y);
		void add_rot_z(float z);

		void set_pos_x(float x);
		void set_pos_y(float y);
		void set_pos_z(float z);
		void set_rot_x(float x);
		void set_rot_y(float y);
		void set_rot_z(float z);

		void set_position(Position position);
		void set_rotation(Rotation rotation);

		Position get_position() const { return m_position; }
		Rotation get_rotation() const { return m_rotation; }
		std::vector<Voxel> get_voxels() const { return m_voxels; }

	private:
		std::vector<Voxel> m_voxels;
		Position m_position;
		Rotation m_rotation;
	};
}
