#include "cnpch.h"
#include "Entity.h"
namespace Crimson {
	Entity::Entity(Scene* scene,const entt::entity& entity)
		:entity(entity),scene(scene)
	{
	}
}
