#include "Player.h"
#include <cmath>
#include "raymath.h"


Player::Player()
{
}

void Player::Update(float dt, Rectangle levelBounds, Vector2 mouseWorldPos)
{
	Vector2 dir{ 0.0f, 0.0f };
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		dir.y -= 1.0f;
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
		dir.y += 1.0f;
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
		dir.x -= 1.0f;
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		dir.x += 1.0f;

	if (dir.x != 0.0f || dir.y != 0.0f)
		dir = Vector2Normalize(dir);

	m_pos.x += dir.x * m_speed * dt;
	m_pos.y += dir.y * m_speed * dt;

	m_pos.x = Clamp(m_pos.x, levelBounds.x + m_radius, levelBounds.x + levelBounds.width - m_radius);
	m_pos.y = Clamp(m_pos.y, levelBounds.y + m_radius, levelBounds.y + levelBounds.height - m_radius);

	m_aimAngle = std::atan2(mouseWorldPos.y - m_pos.y, mouseWorldPos.x - m_pos.x) * RAD2DEG;

	const float barrelLength = 30.0f;
	float rad = m_aimAngle * DEG2RAD;
	Vector2 muzzle{ m_pos.x + std::cos(rad) * barrelLength, m_pos.y + std::sin(rad) * barrelLength };

	m_weapon.Update(dt, muzzle, m_aimAngle, IsMouseButtonDown(MOUSE_LEFT_BUTTON), levelBounds);
}

void Player::Draw() const
{
	m_weapon.Draw();
	DrawRectanglePro({ m_pos.x, m_pos.y, 30.0f, 8.0f }, { 0.0f, 4.0f }, m_aimAngle, LIGHTGRAY);
	DrawCircleV(m_pos, m_radius, Color{ 70,130,200,255 });
}
