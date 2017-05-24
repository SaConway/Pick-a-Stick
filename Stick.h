#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

//-------------------------------------------------------------------------------------------------

const Vector2f STICK_SIZE = {19,255};

//-------------------------------------------------------------------------------------------------

class Stick
{
public:
	Stick(Texture &,int);
	void draw(RenderWindow & w) const {	w.draw(m_sprite);}
	Vector2f getPosition() { return m_sprite.getPosition(); }
	bool isContain(const Vector2f &);
	const Vector2f & getPTop() { return m_pTop; }
	const Vector2f & getPBottom() { return m_pBottom; }
	int getIndex(){ return m_index; }
	void setIndex(int index) { m_index = index; }

private:
	Sprite m_sprite;
	Vector2f m_pTop,m_pBottom;
	int m_index;
};
