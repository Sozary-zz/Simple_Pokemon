#pragma once
#include <SFML\Graphics.hpp>
#include "MapParser.hpp"
#include "AnimatedSprite.hpp"
#define SPEED 16
#define TIME_DEPLACEMNT .15

struct SAnimation
{
	Animation* walk;
	Animation* current;
	AnimatedSprite animated_sprite;
	sf::Clock frame_clock;
	bool updateFPS;
	float speed;
	SAnimation(){}
	void init(int n)
	{
		walk = new Animation[n];
		updateFPS = false;
	}

	void destroy()
	{
		delete []walk;
	}
};

class Player:public sf::Drawable
{
public:
	Player();
	void fixPos();
	sf::Vector2f getPos() const;
	void move(sf::Vector2f);
	void changeCurrentAnimation(DIRECTION);
	DIRECTION getDir() const;
	SAnimation m_anim_player;
	~Player();
private:
	sf::Sprite m_sprite_player;
	sf::Texture m_texture_player;
	DIRECTION m_direction;


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

