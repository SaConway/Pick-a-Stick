#include "Stick.h"

//-------------------------------------------------------------------------------------------------

/* c-tor of stick */

Stick::Stick(Texture & texture, int index) : m_index(index)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect({ 0, 0,(int)STICK_SIZE.x ,(int)STICK_SIZE.y });
	m_sprite.setOrigin({ STICK_SIZE.x / 2, STICK_SIZE.y / 2 });
	Vector2f vec(rand() % 700 + 50, rand() % 700 + 100);
	m_sprite.setPosition(vec);
	m_sprite.setRotation((rand() % 359) + 1);

	m_pTop = m_sprite.getTransform().transformPoint(9.5, 255);
	m_pBottom = m_sprite.getTransform().transformPoint(9.5, 0);
}

//-------------------------------------------------------------------------------------------------

/* Check if stick contain mouse pressed coordinets*/

bool Stick::isContain(const Vector2f & mouse_location)
{
	Vector2f trans_position = m_sprite.getInverseTransform().transformPoint(mouse_location);
	return m_sprite.getLocalBounds().contains(trans_position);
}