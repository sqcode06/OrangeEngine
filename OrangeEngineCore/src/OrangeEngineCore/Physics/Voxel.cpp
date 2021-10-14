#include "OrangeEngineCore/Voxel.h"

#include "OrangeEngineCore/GameObject.h"
#include "PhysicsManager.h"

namespace OrangeEngine
{
	Voxel::Voxel(const Position position, const Rotation rotation, const Color color, const VoxelBehavior behavior)
	{
		m_position = position;
		m_rotation = rotation;
		m_color = color;
		m_behavior = behavior;
	}

	Voxel::Voxel(const Voxel& voxel)
	{
		m_position = voxel.get_position();
		m_rotation = voxel.get_rotation();
		m_color = voxel.get_color();
		m_behavior = voxel.get_behavior();
	}
	Voxel& Voxel::operator=(const Voxel& voxel)
	{
		m_position = voxel.get_position();
		m_rotation = voxel.get_rotation();
		m_color = voxel.get_color();
		m_behavior = voxel.get_behavior();
		return *this;
	}
	Voxel::Voxel(Voxel&& voxel) noexcept
		: m_position(std::move(voxel.get_position()))
		, m_rotation(std::move(voxel.get_rotation()))
		, m_color(std::move(voxel.get_color()))
		, m_behavior(std::move(voxel.get_behavior()))
	{}

	Voxel& Voxel::operator=(Voxel&& voxel) noexcept
	{
		m_position = voxel.get_position();
		m_rotation = voxel.get_rotation();
		m_color = voxel.get_color();
		m_behavior = voxel.get_behavior();
		return *this;
	}

	void Voxel::add_pos_x(float x) { m_position.x += 1; }
	void Voxel::add_pos_y(float y) { m_position.y += 1; }
	void Voxel::add_pos_z(float z) { m_position.z += 1; }
	void Voxel::add_rot_x(float x) { m_rotation.x += 1; }
	void Voxel::add_rot_y(float y) { m_rotation.y += 1; }
	void Voxel::add_rot_z(float z) { m_rotation.z += 1; }

	void Voxel::set_pos_x(float x) { m_position.x = x; }
	void Voxel::set_pos_y(float y) { m_position.y = y; }
	void Voxel::set_pos_z(float z) { m_position.z = z; }
	void Voxel::set_rot_x(float x) { m_rotation.x = x; }
	void Voxel::set_rot_y(float y) { m_rotation.y = y; }
	void Voxel::set_rot_z(float z) { m_rotation.z = z; }

	void Voxel::set_position(Position position) { m_position = position; }
	void Voxel::set_rotation(Rotation rotation) { m_rotation = rotation; }
	void Voxel::set_color(Color color) { m_color = color; }

	bool Voxel::apply_physics()
	{
		return true;
	}
}