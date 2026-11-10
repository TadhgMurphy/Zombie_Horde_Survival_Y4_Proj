#pragma once
#include "raylib.h"
#include "Weapon.h"

class Player
{
public:
	Player();
	void Update(float dt, Rectangle levelBounds, Vector2 mouseWorldPos);
	void Draw() const;
	void TakeDamage(float amount);

	Vector2 GetPosition() const { return m_pos; }
	float GetRadius() const { return m_radius; }
	float GetHealth() const { return m_health; }
	float GetMaxHealth() const { return m_maxHealth; }
	bool IsDead() const { return m_health <= 0.0f; }
	Weapon& GetWeapon() { return m_weapon; }
private:
	Vector2 m_pos{ 1000.0f, 750.0f };
	float m_radius = 20.0f;
	float m_speed = 250.0f;
	float m_aimAngle = 0.0f;

	float m_maxHealth = 100.0f;
	float m_health = 100.0f;
	float m_invulnTimer = 0.0f;
	static constexpr float invulnDuration = 0.5f;

	Weapon m_weapon;
};