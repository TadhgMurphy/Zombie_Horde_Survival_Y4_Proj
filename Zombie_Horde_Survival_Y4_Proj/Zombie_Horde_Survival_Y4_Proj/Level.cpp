#include "Level.h"

Level::Level(float width, float height, float tileSize)
	: m_bounds{ 0.0f, 0.0f, width, height}, m_tileSize(tileSize)
{
}

void Level::Draw() const
{
	const Color floorColour{ 40,45,40,255 };
	const Color lineColour{ 80, 90, 80, 255 };
	const Color wallColor{ 90,60,40,255 };

	DrawRectangleRec(m_bounds, floorColour);
	for (float x = m_bounds.x; x <= m_bounds.x + m_bounds.width; x += m_tileSize)
	{
		DrawLineV({ x, m_bounds.y }, { x, m_bounds.y + m_bounds.height }, lineColour);
	}
	for (float y = m_bounds.y; y <= m_bounds.y + m_bounds.height; y += m_tileSize)
	{
		DrawLineV({ m_bounds.x, y }, { m_bounds.x + m_bounds.width, y }, lineColour);
	}


	const float t = 20.0f;
	DrawRectangleLinesEx({ m_bounds.x - t, m_bounds.y - t, m_bounds.width + 2 * t, m_bounds.height + 2 * t }, t, wallColor);
}
