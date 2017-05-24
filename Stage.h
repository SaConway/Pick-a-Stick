#pragma once

#include "Graph.h"
#include "GameInfo.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//-------------------------------------------------------------------------------------------------

class Stage
{
public:
	Stage();
	void clean();
	void setLevel(int );
	bool runStage(RenderWindow &);
	void draw(RenderWindow &);
	void playerEvent(RenderWindow &);
	void displayScore(RenderWindow &);

private:
	Texture m_back_ground;
	Sprite m_back_ground_sprite;
	Graph m_graph;
	GameInfo m_info;
	SoundBuffer m_sound_buf;
	Sound m_click;
	bool m_game_over;
};