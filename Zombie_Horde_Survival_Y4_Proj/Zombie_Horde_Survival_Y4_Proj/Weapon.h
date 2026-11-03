#pragma once
#include "raylib.h"
#include <vector>

struct Bullet
{
	Vector2 pos;
	Vector2 vel;
	float radius;
	float damage;
	float life;
};

struct WeaponStats
{
	float damage = 10.0f;
	float fireRate = 4.0f;
	float bulletSpeed = 700.0f;
	float bulletRadius = 4.0f;
	float range = 600.0f;
};

class Weapon
{
public:
	void Update(float dt, Vector2 muzzlePos, float aimAngleDeg, bool triggerHeld, Rectangle levelBounds);
	void Draw() const;

	std::vector<Bullet>& GetBullets() { return m_bullets; }
	WeaponStats& Stats() { return m_stats; }
private:
	WeaponStats m_stats;
	std::vector<Bullet> m_bullets;
	float m_cooldown;
};