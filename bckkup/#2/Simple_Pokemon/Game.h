#pragma once
#include "TileMap.hpp"
#include "Player.h"

#define GAME_FPS 50

class Game // LE jeu est ici!
{
public:
	Game(const char*,int);
	void run();
	void processEvent();
	void update(sf::Time);
	void render();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::View m_view;
	Player m_joueur;
	TileMap m_tile_map;
	ScriptParser m_scripts;
	std::vector<sf::RectangleShape> m_sprites;
	std::vector<sf::Texture> m_textures;
	bool m_can_move;
	bool m_keys_pressed[sf::Keyboard::KeyCount];

	DIRECTION m_next_player;



private:
	const sf::Time TimePerFrame;
	const int TimePerAnimation;
private:
	void applyTexture();
};

