#include "Game.h"

using namespace std;
using namespace sf;

Game::Game(const char * ini, int map_start) :
	TimePerFrame(seconds(1.f / (float)GAME_FPS)),
	TimePerAnimation(200),
	m_t_player_move(sf::Time()),
	m_player_action(false) ,
	m_window(VideoMode(800, 800), "Pokémon"),
	m_keys_pressed{ false },
	m_must_wait(false)
{
	MapParser parse(ini, map_start);


	
	m_tile_map.load("tiles\\tiles.png", Vector2u(16, 16), parse.getMap(), 20, 20);
	m_scripts = parse.getParser();

	m_col = Collision(ini, map_start, m_scripts);
	m_textures.resize(m_scripts.size());
	m_sprites.resize(m_scripts.size());
	applyTexture();
	m_joueur.m_anim_player.animated_sprite.setPosition(Vector2f(160,160));
	m_joueur.m_anim_player.animated_sprite.stop();
	m_joueur.changeCurrentAnimation(BAS);
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

void Game::handleScripts(Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::A:

		
				if (!m_must_wait)
				{
					auto dir = m_joueur.getDir();
					auto pos = m_joueur.getPos();

					pos.x = round(pos.x) / 16;
					pos.y = round(pos.y) / 16;

					switch (dir)
					{
					case DROITE:
						pos.x++;
						break;
					case BAS:
						pos.y++;
						break;
					case GAUCHE:
						pos.x--;
						break;
					case HAUT:
						pos.y--;
						break;
					}
					// on recherche un événement proche de player

					for (int i = 0; i < m_scripts.size(); ++i)
					{
						if (distanceE(pos.x, pos.y, m_scripts[i].position.x, m_scripts[i].position.y) == 0)
						{

						string path = "data/personnages/" + m_scripts.getID(i);
						switch (dir)
						{
						case DROITE:
							path += "_02.png";
							break;
						case BAS:
							path += "_03.png";
							break;
						case GAUCHE:
							path += "_00.png";
							break;
						case HAUT:
							path += "_01.png";
							break;
						}


						m_scripts[i].m_perso_path = path; // on change d'image
						applyTexture();
						
						m_current.loadScript(m_scripts[i]); // on gère CE script
		
						m_current.executeHeap(&m_msg_box, &m_must_wait); // on démarre son execution
						
				}
				else
				
					m_current.next_action(&m_must_wait);
				
				

			}
		}

	}
	
}



void Game::run()
{


	Clock clock;
	Time timeSinceLastUpdate;
	timeSinceLastUpdate = Time::Zero;
	int animationCounter = 0;
	// cout << m_scripts[2].instructions[1].offset << endl; // --> fonctionne
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
				
				switch (event.key.code)
				{
				case Keyboard::Up:
					if (!m_must_wait)
					{
						m_keys_pressed[Keyboard::Up] = true;
					}
					break;

				case Keyboard::A:
					m_keys_pressed[Keyboard::A] = true;
					break;
				case Keyboard::Left:
					if (!m_must_wait)
					{
						m_keys_pressed[Keyboard::Left] = true;
					}
					break;

				case Keyboard::Down:
					if (!m_must_wait)
					{
						m_keys_pressed[Keyboard::Down] = true;
					}
					break;

				case Keyboard::Right:
					if (!m_must_wait)
					{
						m_keys_pressed[Keyboard::Right] = true;
					}
					break;


				}
				
				break;

				case Event::KeyReleased:	
					
					switch (event.key.code)
					{
					case Keyboard::Up:
						if (!m_must_wait)
						{
							m_keys_pressed[Keyboard::Up] = false;
						}
						break;
					case Keyboard::A:
						m_keys_pressed[Keyboard::A] = false;
						break;
					case Keyboard::Left:
						if (!m_must_wait)
						{
							m_keys_pressed[Keyboard::Left] = false;
						}
						break;

					case Keyboard::Down:
						if (!m_must_wait)
						{
							m_keys_pressed[Keyboard::Down] = false;
						}
						break;

					case Keyboard::Right:
						if (!m_must_wait)
						{
							m_keys_pressed[Keyboard::Right] = false;
						}
						break;
					}
			}
			break;
		
	
	}

}


void Game::update(Time deltaTime)
{
	
	m_joueur.m_anim_player.animated_sprite.play(*m_joueur.m_anim_player.current);
	if (!m_player_action)
		m_joueur.m_anim_player.animated_sprite.stop();
	if (m_player_action)
	{
		m_t_player_move = m_c_player_move.getElapsedTime();
		if (m_t_player_move.asMilliseconds() > 850)
			m_player_action = false;
	}

	if (!m_player_action)
	{
		int iAction = -1;
		for (int i = 0; i < Keyboard::KeyCount; ++i)
			if (m_keys_pressed[i])
				iAction = i;
		auto pos = m_joueur.getPos();
		pos.x = round(pos.x);
		pos.y = round(pos.y)+16;
		switch (iAction)
		{
		case -1:
			break;
		case Keyboard::Right:
			m_joueur.changeCurrentAnimation(DROITE);
			if (!m_col.collision((pos.x / 16)+1, (pos.y / 16) ))
			{
				
				m_player_action = true;
				m_c_player_move.restart();
			}
			
		
			break;
		case Keyboard::Left:
			m_joueur.changeCurrentAnimation(GAUCHE);
			if (!m_col.collision((pos.x / 16)-1, (pos.y / 16)))
			{
			
				
				m_player_action = true;
				m_c_player_move.restart();
			}

			break;
		case Keyboard::Up:
			m_joueur.changeCurrentAnimation(HAUT);
			if (!m_col.collision(pos.x / 16,(pos.y / 16)-1))
			{
				
				m_player_action = true;
				m_c_player_move.restart();
			}
			
			break;
		case Keyboard::Down:
			m_joueur.changeCurrentAnimation(BAS);
			if (!m_col.collision(pos.x / 16, (pos.y / 16)+1))
			{
				m_player_action = true;
				m_c_player_move.restart();
			}
			break;
		case Keyboard::A:
			handleScripts(Keyboard::A);
			
			break;
		
		}
	}
	else
	{
		sf::Vector2f toMove(0, 0);
		double step = (8.f / 21.f);
		switch (m_joueur.getDir())
		{
			case HAUT:   toMove.x =   0; toMove.y = -step; break;
			case BAS:    toMove.x = 0  ; toMove.y = step; break;
			case GAUCHE: toMove.x = -step; toMove.y = 0  ; break;
			case DROITE: toMove.x = step; toMove.y = 0  ; break;
		}
	
		if (m_t_player_move.asMilliseconds() > 0 && m_t_player_move.asMilliseconds() < 850/2)
		{
			
			m_joueur.m_anim_player.animated_sprite.move(toMove);
		}
		else if (m_t_player_move.asMilliseconds() >= 850 /2 && m_t_player_move.asMilliseconds() < 850)
		{
			m_joueur.m_anim_player.animated_sprite.move(toMove);
		}
	}

	

		
	m_joueur.m_anim_player.animated_sprite.update(TimePerFrame);
}



void Game::render()
{
	m_window.clear();
	m_window.draw(m_tile_map);
	for (int i = 0; i < m_sprites.size(); ++i)
		m_window.draw(m_sprites[i]);

	m_window.draw(m_joueur.m_anim_player.animated_sprite);
	if(m_msg_box.canBeDrawn())
		m_window.draw(m_msg_box);
	m_window.setView(m_view);
	m_window.display();
}
