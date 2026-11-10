#pragma once
#include "raylib.h"

struct ZombieStats
{
	float maxHealth = 30.0f;
	float speed = 100.0f;
	float damage = 10.0f;
	float radius = 18.0f;
	Color colour{ 90, 160, 80, 255 };
};

class Zombie
{
public:
	Zombie(Vector2 pos, const ZombieStats& stats = ZombieStats{});

	void Update(float dt, Vector2 playerPos);
	void Draw() const;
	void TakeDamage(float amount);

	bool IsAlive() const { return m_health > 0.0f; }
	Vector2 GetPosition() const { return m_pos; }
	void SetPosition(Vector2 p) { m_pos = p; }
	float GetRadius() const { return m_stats.radius; }
	float GetDamage() const { return m_stats.damage; }
private:
	Vector2 m_pos;
	ZombieStats m_stats;
	float m_health;

	float m_spawnTimer = 0.0f;
};