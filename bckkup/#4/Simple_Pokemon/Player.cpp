#include "Player.h"

using namespace std;

Player::Player()
{

	m_texture_player.loadFromFile("data/personnages/00.png");
	m_sprite_player.setTexture(m_texture_player);

	m_anim_player.init(4);
	m_anim_player.walk[DROITE].setSpriteSheet(m_texture_player);
	m_anim_player.walk[DROITE].addFrame(sf::IntRect(0, 0, 16, 32));
	m_anim_player.walk[DROITE].addFrame(sf::IntRect(16, 0, 16, 32));
	m_anim_player.walk[DROITE].addFrame(sf::IntRect(0, 0, 16, 32));
	m_anim_player.walk[DROITE].addFrame(sf::IntRect(32, 0, 16, 32));


	m_anim_player.walk[BAS].setSpriteSheet(m_texture_player);
	m_anim_player.walk[BAS].addFrame(sf::IntRect(0, 32, 16, 32));
	m_anim_player.walk[BAS].addFrame(sf::IntRect(16, 32, 16, 32));
	m_anim_player.walk[BAS].addFrame(sf::IntRect(0, 32, 16, 32));
	m_anim_player.walk[BAS].addFrame(sf::IntRect(32, 32, 16, 32));


	m_anim_player.walk[GAUCHE].setSpriteSheet(m_texture_player);
	m_anim_player.walk[GAUCHE].addFrame(sf::IntRect(0, 64, 16, 32));
	m_anim_player.walk[GAUCHE].addFrame(sf::IntRect(16, 64, 16, 32));
	m_anim_player.walk[GAUCHE].addFrame(sf::IntRect(0, 64, 16, 32));
	m_anim_player.walk[GAUCHE].addFrame(sf::IntRect(32, 64, 16, 32));


	m_anim_player.walk[HAUT].setSpriteSheet(m_texture_player);
	m_anim_player.walk[HAUT].addFrame(sf::IntRect(0, 96, 16, 32));
	m_anim_player.walk[HAUT].addFrame(sf::IntRect(16, 96, 16, 32));
	m_anim_player.walk[HAUT].addFrame(sf::IntRect(0, 96, 16, 32));
	m_anim_player.walk[HAUT].addFrame(sf::IntRect(32, 96, 16, 32));


	m_anim_player.current = &m_anim_player.walk[BAS];

	m_anim_player.animated_sprite = AnimatedSprite(sf::seconds(TIME_DEPLACEMNT), true, false);

}



sf::Vector2f Player::getPos() const
{
	return m_anim_player.animated_sprite.getPosition();
}


void Player::changeCurrentAnimation(DIRECTION i)
{
	m_anim_player.current = &m_anim_player.walk[i];
	m_direction = i;
}

DIRECTION Player::getDir() const
{
	return m_direction;
}


Player::~Player()
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	
	target.draw(m_sprite_player, states);
}
