#include "OrangeEngineCore/GameObject.h"

namespace OrangeEngine
{
	GameObject::GameObject(Position position, Rotation rotation)
	{
		m_position = position;
		m_rotation = rotation;
	}

	GameObject::~GameObject()
	{
		for (unsigned int counter = 0; counter < m_voxels.size(); counter++)
		{
			delete &m_voxels.at(counter);
		}
	}

	GameObject::GameObject(const GameObject& game_object)
	{
		m_position = game_object.m_position;
		m_rotation = game_object.m_rotation;
		m_voxels = game_object.get_voxels();
	}

	GameObject& GameObject::operator=(const GameObject& game_object)
	{
		m_position = game_object.m_position;
		m_rotation = game_object.m_rotation;
		m_voxels = game_object.get_voxels();
		return *this;
	}

	GameObject::GameObject(GameObject&& game_object) noexcept
		: m_position(std::move(game_object.get_position()))
		, m_rotation(std::move(game_object.get_rotation()))
		, m_voxels(std::move(game_object.get_voxels()))
	{}

	GameObject& GameObject::operator=(GameObject&& game_object) noexcept
	{
		m_position = game_object.m_position;
		m_rotation = game_object.m_rotation;
		m_voxels = game_object.get_voxels();
		return *this;
	}

	void GameObject::add_pos_x(float x) { m_position.x += 1; }
	void GameObject::add_pos_y(float y) { m_position.y += 1; }
	void GameObject::add_pos_z(float z) { m_position.z += 1; }
	void GameObject::add_rot_x(float x) { m_rotation.x += 1; }
	void GameObject::add_rot_y(float y) { m_rotation.y += 1; }
	void GameObject::add_rot_z(float z) { m_rotation.z += 1; }

	void GameObject::set_pos_x(float x) { m_position.x = x; }
	void GameObject::set_pos_y(float y) { m_position.y = y; }
	void GameObject::set_pos_z(float z) { m_position.z = z; }
	void GameObject::set_rot_x(float x) { m_rotation.x = x; }
	void GameObject::set_rot_y(float y) { m_rotation.y = y; }
	void GameObject::set_rot_z(float z) { m_rotation.z = z; }

	void GameObject::set_position(Position position) { m_position = position; }
	void GameObject::set_rotation(Rotation rotation) { m_rotation = rotation; }

	void GameObject::add_voxel(Voxel& voxel)
	{
		m_voxels.push_back(voxel);
	}

	void GameObject::merge(GameObject& game_object)
	{
		std::vector<Voxel> go_voxels = game_object.get_voxels();
		for (unsigned int counter = 0; counter < go_voxels.size(); counter++)
		{
			m_voxels.push_back(go_voxels.at(counter));
		}
		delete &go_voxels;
		delete &game_object;
	}
}