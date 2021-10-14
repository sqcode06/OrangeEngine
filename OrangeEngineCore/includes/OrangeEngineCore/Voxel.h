#pragma once

#include <cstdint>

namespace OrangeEngine
{
	struct Position
	{
		float x;
		float y;
		float z;
	};

	struct Rotation
	{
		float x;
		float y;
		float z;
	};

	struct Color
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};
	
	enum class VoxelBehavior
	{
		BOUND,
		LOOSE,
		LIQUID,
		PARTICLE
	};

	class Voxel
	{
	public:
		Voxel(const Position position, const Rotation rotation, const Color color, const VoxelBehavior behavior);

		Voxel(const Voxel& voxel);
		Voxel& operator=(const Voxel& voxel);
		Voxel(Voxel&& voxel) noexcept;
		Voxel& operator=(Voxel&& voxel) noexcept;

		bool apply_physics();

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

		void set_color(Color color);

		Position get_position() const { return m_position; }
		Rotation get_rotation() const { return m_rotation; }
		Color get_color() const { return m_color; }
		VoxelBehavior get_behavior() const { return m_behavior; }

	private:
		Position m_position;
		Rotation m_rotation;
		Color m_color;
		VoxelBehavior m_behavior;
	};
}