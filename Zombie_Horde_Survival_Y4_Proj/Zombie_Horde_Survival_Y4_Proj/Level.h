#pragma once
#include "raylib.h"

class Level
{
public:
	Level(float width = 2000.0f, float height = 1500.0f, float tileSize = 100.0f);

	void Draw() const;
	Rectangle GetBounds() const { return m_bounds; }
private:
	Rectangle m_bounds;
	float m_tileSize;
};