#include "Game.h"

using namespace std;
using namespace sf;

Game::Game(const char * ini, int map_start):
	TimePerFrame(seconds(1.f / (float)GAME_FPS)),
	m_window(sf::VideoMode(800, 800), "Pokémon")
{
	MapParser parse(ini, map_start);


	m_tile_map.load("tiles\\tiles.png", sf::Vector2u(16, 16), parse.getMap(), 20, 20);
	m_scripts = parse.getParser();
	m_textures.resize(m_scripts.size());
	m_sprites.resize(m_scripts.size());
	applyTexture();
	m_view=View(sf::FloatRect(0, 0, 20 * 16, 20 * 16)); // a gérer
}

Game::~Game()
{
}
void Game::applyTexture()
{
	for (int i = 0; i < m_scripts.size(); ++i)
	{
		RectangleShape rectangle;
		Texture texture;
		rectangle.setSize(Vector2f(16, 32));
		rectangle.setPosition(Vector2f(m_scripts[i].position.x*16, m_scripts[i].position.y*16));
		texture.loadFromFile(m_scripts[i].m_perso_path);
		m_textures[i]=texture;
		rectangle.setTexture(&m_textures[i]);
		m_sprites[i]=rectangle;
	}
}
void Game::run()
{


	Clock clock;

	Time timeSinceLastUpdate;
	timeSinceLastUpdate = Time::Zero;
	// cout << m_scripts[2].instructions[1].offset << endl;  --> fonctionne
	while (m_window.isOpen())
	{


		processEvent();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{

			timeSinceLastUpdate -= TimePerFrame;
			processEvent();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvent()
{
	Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed: m_window.close(); break;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{

		}
	}

}


void Game::update(Time deltaTime)
{

}



void Game::render()
{
	m_window.clear();
	m_window.draw(m_tile_map);
	for (int i = 0; i < m_sprites.size(); ++i)
		m_window.draw(m_sprites[i]);
	
	m_window.setView(m_view);
	m_window.display();
}
