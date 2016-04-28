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
	bool m_keys_pressed[sf::Keyboard::KeyCount];
	sf::Clock m_c_player_move;
	sf::Time m_t_player_move;
	bool m_player_action;

	



private:
	const sf::Time TimePerFrame;
	const int TimePerAnimation;
private:
	void applyTexture();

};

