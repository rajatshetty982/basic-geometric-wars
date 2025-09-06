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
	// do something else?
}

void Entity::setAlpha(int alphaValue)
{
	sf::Color color = cShape->circle.getFillColor();
	color.a = alphaValue;
	cShape->circle.setFillColor(sf::Color(color));
}

