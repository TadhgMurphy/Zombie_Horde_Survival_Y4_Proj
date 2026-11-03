#include "Weapon.h"
#include "raymath.h"
#include <cmath>
#include <algorithm>

void Weapon::Update(float dt, Vector2 muzzlePos, float aimAngleDeg, bool triggerHeld, Rectangle levelBounds)
{
	m_cooldown = std::max(0.0f, m_cooldown - dt);

	if (triggerHeld && m_cooldown <= 0.0f)
	{
		float rad = aimAngleDeg * DEG2RAD;
		Vector2 dir{ std::cos(rad), std::sin(rad) };

		m_bullets.push_back({
			muzzlePos,
			Vector2Scale(dir, m_stats.bulletSpeed),
			m_stats.bulletRadius,
			m_stats.damage,
			m_stats.range / m_stats.bulletSpeed
		});
		m_cooldown = 1.0f / m_stats.fireRate;
	}

	for (Bullet& b : m_bullets)
	{
		b.pos = Vector2Add(b.pos, Vector2Scale(b.vel, dt));
		b.life -= dt;
	}

	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [&](const Bullet& b) 
		{ return b.life <= 0.0f || !CheckCollisionPointRec(b.pos, levelBounds);}), m_bullets.end());
}

void Weapon::Draw() const
{
	for (const Bullet& b : m_bullets)
		DrawCircleV(b.pos, b.radius, YELLOW);
}
