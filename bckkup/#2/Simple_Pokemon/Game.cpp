#include "Game.h"

using namespace std;
using namespace sf;

Game::Game(const char * ini, int map_start):
	TimePerFrame(seconds(1.f / (float)GAME_FPS)),
	TimePerAnimation(200),
	m_can_move(false),
	m_window(VideoMode(800, 800), "Pokémon"),
	m_keys_pressed{ false }
{
	MapParser parse(ini, map_start);


	m_tile_map.load("tiles\\tiles.png", Vector2u(16, 16), parse.getMap(), 20, 20);
	m_scripts = parse.getParser();
	m_textures.resize(m_scripts.size());
	m_sprites.resize(m_scripts.size());
	applyTexture();
	m_joueur.m_anim_player.animated_sprite.move(Vector2f(32,32));
	m_view=View(FloatRect(0, 0, 20 * 16, 20 * 16)); // a gérer
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
	int animationCounter = 0;
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
			case Event::KeyPressed:
				m_joueur.m_anim_player.frame_clock.restart();
				m_joueur.m_anim_player.updateFPS = true;
			
				switch (event.key.code)
				{
				case Keyboard::Up:
					m_keys_pressed[Keyboard::Up] = true; 
					break;

				case Keyboard::A:
					m_keys_pressed[Keyboard::A] = true;
					break;
				case Keyboard::Left:
					m_keys_pressed[Keyboard::Left] = true; 
					break;

				case Keyboard::Down:
					m_keys_pressed[Keyboard::Down] = true;
					break;

				case Keyboard::Right:
					m_keys_pressed[Keyboard::Right] = true;
					break;


				}
				break;
			case Event::KeyReleased:	
				m_joueur.m_anim_player.updateFPS = false;
				switch (event.key.code)
				{
				case Keyboard::Up:
					m_keys_pressed[Keyboard::Up] = false;
					break;
				case Keyboard::A:
					m_keys_pressed[Keyboard::A] = false;
					break;
				case Keyboard::Left:
					m_keys_pressed[Keyboard::Left] = false;
					break;

				case Keyboard::Down:
					m_keys_pressed[Keyboard::Down] = false;
					break;

				case Keyboard::Right:
					m_keys_pressed[Keyboard::Right] = false;
					break;


				}
				break;

		}

		
	
	}

}


void Game::update(Time deltaTime)
{
	
	if (m_joueur.m_anim_player.frame_clock.getElapsedTime().asMilliseconds() >= 100)
	{
		Vector2f movement(0.f, 0.f);
		m_joueur.m_anim_player.frame_clock.restart();
		switch (m_next_player)
		{
		case HAUT:
			m_joueur.changeCurrentAnimation(HAUT);
			movement.y -= SPEED;
			break;
		case BAS:
			m_joueur.changeCurrentAnimation(BAS);
			movement.y += SPEED;
			break;
		case GAUCHE:
			m_joueur.changeCurrentAnimation(GAUCHE);
			movement.x -= SPEED;
			break;
		case DROITE:
			m_joueur.changeCurrentAnimation(DROITE);
			movement.x += SPEED;
			break;
		case NONE:
			break;
		}
		m_joueur.m_anim_player.animated_sprite.play(*m_joueur.m_anim_player.current);
		m_joueur.m_anim_player.animated_sprite.move(movement);
		//m_joueur.fixPos();
		if (!m_joueur.m_anim_player.updateFPS)
			m_joueur.m_anim_player.animated_sprite.stop();

		m_joueur.m_anim_player.animated_sprite.update(TimePerFrame);
	}

	else
	{
		m_next_player = NONE;
		if (m_keys_pressed[Keyboard::Up])
		m_next_player = HAUT;

		else if (m_keys_pressed[Keyboard::Down])
			m_next_player = BAS;

		else if (m_keys_pressed[Keyboard::Left])
			m_next_player = GAUCHE;

		else if (m_keys_pressed[Keyboard::Right])
			m_next_player = DROITE;
		else if (m_keys_pressed[Keyboard::A])
		{
			
			Script nearest = m_scripts.nearScript(int(m_joueur.getPos().x), int(m_joueur.getPos().y),m_joueur.getDir());
			cout << nearest.m_perso_path << endl;
		}
			
	}
	
	
	

}



void Game::render()
{
	m_window.clear();
	m_window.draw(m_tile_map);
	for (int i = 0; i < m_sprites.size(); ++i)
		m_window.draw(m_sprites[i]);

	m_window.draw(m_joueur.m_anim_player.animated_sprite);
	m_window.setView(m_view);
	m_window.display();
}
