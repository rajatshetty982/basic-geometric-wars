#include "EntityManager.h"
#include <algorithm>

// #include <iostream>

EntityManager::EntityManager() { }

void EntityManager::update()
{
	// TODO
	for (auto e: m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_entitiesToAdd.clear();

	// remove dead souls or bullets or anyythinggg
	// c++17 way of iterating thought map
	for (auto& [tag, entityVec]: m_entityMap)
	{
		removeDeadEntities(entityVec);
	}

}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// this thing takes care of iterator invalidation
	vec.erase(
		std::remove_if(vec.begin(), vec.end(),
					   [](const auto &e)
					   { return !e->isActive(); }),
		vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	// Entity(const size_t id, const std::string& tag);

	m_entitiesToAdd.push_back(entity);

	return entity;
}

EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}

