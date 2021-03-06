#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"

using namespace std;

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;

	ColliderComponent(string t)
	{
		tag = t;
	}

	ColliderComponent(string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/CollisionTexture.png");
		srcR = { 0,0,32,32 };
		destR = {collider.x, collider.y, collider.w, collider.h};
	}

	void update() override
	{
		//sets collider box size for players
		if (tag == "player")
		{
			collider.x = static_cast<int>(transform->position.x + 32);
			collider.y = static_cast<int>(transform->position.y + 20);
			collider.w = ((transform->width * transform->scale) / 3);
			collider.h = ((transform->height * transform->scale) * 0.8);
		}

		//sets collider box size for projectiles
		if (tag == "projectile")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		//to draw the collision boxes for projectiles and player via green box 
		SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &collider);
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	}
};