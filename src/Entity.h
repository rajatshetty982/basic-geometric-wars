#pragma once

#include "Components.h"
#include <memory>
#include <string>

class Entity
{
	friend class EntityManager;
	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "default";
	bool m_collidedAtX = false;
	bool m_collidedAtY = false;
	size_t m_points = 1;
	bool m_isSmallEnemy = false;

	// constructor
	Entity(const size_t id, const std::string &tag)
		: m_id(id), m_tag(tag), m_active(true) {}

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
	void setAlpha(int alphaValue);
	bool hasCollidedAtX();
	bool hasCollidedAtY();
	void setCollidedAtY(bool);
	void setCollidedAtX(bool);
	void setPointForSmallEnemies();
	size_t getPoints();
	void setIsSmallEnemy();
	bool isSmallEmeny();
};
