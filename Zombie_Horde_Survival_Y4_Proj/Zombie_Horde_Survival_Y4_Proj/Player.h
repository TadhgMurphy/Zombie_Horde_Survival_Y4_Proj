#pragma once
#include "raylib.h"
#include "Weapon.h"

class Player
{
public:
	Player();
	void Update(float dt, Rectangle levelBounds, Vector2 mouseWorldPos);
	void Draw() const;
	Vector2 GetPosition() const { return m_pos; }
	float GetRadius() const { return m_radius; }
	Weapon& GetWeapon() { return m_weapon; }
private:
	Vector2 m_pos{ 1000.0f, 750.0f };
	float m_radius = 20.0f;
	float m_speed = 250.0f;
	float m_aimAngle = 0.0f;

	Weapon m_weapon;
};