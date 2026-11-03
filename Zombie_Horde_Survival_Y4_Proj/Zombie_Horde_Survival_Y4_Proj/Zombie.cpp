#include "Zombie.h"
#include "raymath.h"

Zombie::Zombie(Vector2 pos, const ZombieStats& stats) : m_pos(pos), m_stats(stats)
{
}

void Zombie::Update(float dt, Vector2 playerPos)
{
	Vector2 toPlayer = Vector2Subtract(playerPos, m_pos);
	if (Vector2LengthSqr(toPlayer) > 1.0f)
	{
		Vector2 dir = Vector2Normalize(toPlayer);
		m_pos = Vector2Add(m_pos, Vector2Scale(dir, m_stats.speed * dt));
	}
}

void Zombie::Draw() const
{
	DrawCircleV(m_pos, m_stats.radius, m_stats.colour);
}