#include "Zombie.h"
#include "raymath.h"

Zombie::Zombie(Vector2 pos, const ZombieStats& stats) : m_pos(pos), m_stats(stats), m_health(stats.maxHealth)
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

	if (m_health < m_stats.maxHealth)
	{
		const float barW = m_stats.radius * 2.0f;
		const float barH = 5.0f;
		float x = m_pos.x - m_stats.radius;
		float y = m_pos.y - m_stats.radius - 10.0f;
		float pct = m_health / m_stats.maxHealth;

		DrawRectangle((int)x, (int)y, (int)barW, (int)barH, Color{ 60, 0, 0, 255 });
		DrawRectangle((int)x, (int)y, (int)(barW * pct), (int)barH, RED);
	}
}

void Zombie::TakeDamage(float amount)
{
	m_health -= amount;
}
