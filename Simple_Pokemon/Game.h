#pragma once
#include "TileMap.hpp"
#include "ScriptHandle.h"
#include "Collision.h"
#include "FlagParser.h"

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
	Collision m_col;
	ScriptParser m_scripts;
	std::vector<sf::RectangleShape> m_sprites;
	std::vector<sf::Texture> m_textures;
	bool m_keys_pressed[sf::Keyboard::KeyCount];
	sf::Clock m_c_player_move;
	sf::Time m_t_player_move;
	bool m_player_action;
	MsgBox m_msg_box;
	bool m_must_wait;
	ScriptHandle m_current;
	FlagParser m_flags;

	



private:
	const sf::Time TimePerFrame;
	const int TimePerAnimation;
private:
	void applyTexture();
	void handleScripts(sf::Keyboard::Key);

};

