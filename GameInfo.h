#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

//-------------------------------------------------------------------------------------------------

class GameInfo
{
public:
	GameInfo();
	void createStage(int);
	void updateTime();
	void updateInfo();
	void updateScore(int);
	void draw(RenderWindow & w) const { w.draw(m_textScore); w.draw(m_textTime); }
	bool checktimer() const { return  (m_timer.x == 0 && m_timer.y == 0) ? true : false;}
	void clean();
	void displayScore(Vector2u);

private: 
	int m_num_of_stick;
	int m_start_num_of_stick;
	int m_score = 0;
	sf::Clock m_clock;				//game clock;
	sf::Vector2i m_timer;
	Font m_font;
	sf::Text m_textScore;
	sf::Text m_textTime;
};

