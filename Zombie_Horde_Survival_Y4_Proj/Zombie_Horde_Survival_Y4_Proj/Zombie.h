#pragma once
#include "raylib.h"

struct ZombieStats
{
	float speed = 100.0f;
	float radius = 18.0f;
	Color colour{ 90, 160, 80, 255 };
};

class Zombie
{
public:
	Zombie(Vector2 pos, const ZombieStats& stats = ZombieStats{});

	void Update(float dt, Vector2 playerPos);
	void Draw() const;

	Vector2 GetPosition() const { return m_pos; }
	float GetRadius() const { return m_stats.radius; }
private:
	Vector2 m_pos;
	ZombieStats m_stats;
};