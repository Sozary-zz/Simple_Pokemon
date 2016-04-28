#pragma once
#include <SFML\Graphics.hpp>
#include "MapParser.hpp"

class Player
{
public:
	Player();
	~Player();
private:
	sf::Sprite m_sprite_player;
	sf::Texture m_texture_player;

};

