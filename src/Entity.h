#pragma once

#include "Components.h"
#include <memory>
#include <string>

class Entity
{
	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "default";

	// constructor
	Entity(const size_t id, const std::string &tag)
		: m_id(id), m_tag(tag), m_active(true) {}
	friend class EntityManager;

public:
	// component ptrs
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;

	// private member access funcs
	bool isActive() const;
	const std::string &tag() const;
	const size_t id() const;
	void destroy();
};
