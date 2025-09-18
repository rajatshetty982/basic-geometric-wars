#include "Entity.h"
#include <iostream>

bool Entity::isActive() const
{
	return m_active;
}

const std::string& Entity::tag() const
{
	return m_tag;
}

const size_t Entity::id() const
{
	return m_id;
}

void Entity::destroy()
{
	m_active = false;
}

void Entity::setAlpha(int alphaValue)
{
	sf::Color color = cShape->circle.getFillColor();
	color.a = alphaValue;
	cShape->circle.setFillColor(sf::Color(color));
}

bool Entity::hasCollidedAtX()
{
	return m_collidedAtX;
}


bool Entity::hasCollidedAtY()
{
	return m_collidedAtY;

}
void Entity::setCollidedAtX(bool boolVal)
{
	m_collidedAtX = boolVal;
}

void Entity::setCollidedAtY(bool boolVal)
{
	m_collidedAtY = boolVal;
}
void Entity::setPointForSmallEnemies()
{
	m_points = 2;
}

size_t Entity::getPoints()
{
	return m_points;
}
void Entity::setIsSmallEnemy()
{
	m_isSmallEnemy = true;
}
bool Entity::isSmallEmeny()
{
	return m_isSmallEnemy;
}