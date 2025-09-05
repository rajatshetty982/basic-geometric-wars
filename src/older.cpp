#include "Game.h"

int main()
{
	Game g("../config.txt");
	g.run();
}

// // lectures classes start - Entity 
// class Entity 
// {
// 	size_t m_id = 0;
// 	std::string m_tag = "Default";
// 	bool is_alive = 1;

// 	// for making add entities only to be able to be done by EM 
// 	Entity(const std::string &tag, size_t id);

// public:
// 	std::shared_ptr<CTransform> cTransform;
// 	std::shared_ptr<CName> cName;
// 	std::shared_ptr<CShape> cShape;
// 	std::shared_ptr<CBBox> cBBox;

// };

// typedef std::vector<std::shared_ptr<Entity>> EntityVec;

// typedef std::map<std::string, EntityVec> EntityMap;

// class EntityManager:
// 	EntityVec m_entities;
// 	EntityVec m_toAdd;
// 	EntityMap m_entitiesMap;
// 	size_t total_entities;
	 

// public:

// 	std::shared_ptr<Entity> add_entity(const std::string &tag)
// 	{
// 		// set incremental id
// 		auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
// 		m_toAdd.push_back(e);
// 		// m_entities.push(e);
// 		// m_entitiesMap[tag].push_puah(e);
// 		return e; 

// 	}

// 	void update()
// 	{
// 		for (auto e : m_toAdd)
// 		{
// 			m_entities.push_back(e);
// 			m_entitiesMap[e->tag()].push_back(e);
// 		}
// 		for (auto e : m_entities)
// 		{
// 			// if e is dead, remove it from m_entities
// 			// if e is dead, remove it from m_entitiesMap[e->tag()]
// 			// hinted to check for iterator invalidation here for m_entities
// 			// there is a good builtin method in cpp call remove_if, check it

// 		}
// 		m_toAdd.clear();
// 	}
// 	EntityVec &getEntites();
// 	EntityVec &getEntities(const std::string &tag);


// };


// /*
// above is for reference
// below is me smashing keys.
// */

// // 0. need to make the config file.

// // 1. impl the vec2 class

