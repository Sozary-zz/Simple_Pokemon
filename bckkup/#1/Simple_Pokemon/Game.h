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
	TileMap m_tile_map;
	ScriptParser m_scripts;
	std::vector<sf::RectangleShape> m_sprites;
	std::vector<sf::Texture> m_textures;

private:
	const sf::Time TimePerFrame;
private:
	void applyTexture();
};

