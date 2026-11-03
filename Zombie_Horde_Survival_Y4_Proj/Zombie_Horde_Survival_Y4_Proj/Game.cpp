#include "Game.h"
#include "raymath.h"

Game::Game()
{
	InitWindow(window_w, window_h, "Zombie Horde Survival");
	SetTargetFPS(60);

	m_camera.offset = { window_w / 2.0f, window_h / 2.0f };

	UpdateCamera();
	m_camera.rotation = 0.0f;
	m_camera.zoom = 1.0f;

	m_zombies.emplace_back(Vector2{ 100.0f, 100.0f });
	m_zombies.emplace_back(Vector2{ 1900.0f, 100.0f });
	m_zombies.emplace_back(Vector2{ 1000.0f, 1400.0f });
}

Game::~Game()
{
	CloseWindow();
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		if (dt > 0.1f)
			dt = 0.1f;

		Update(dt);
		Render();
	}
}

void Game::Update(float dt)
{
	(void)dt;
	switch (m_state)
	{
	case GameState::Playing:
		Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), m_camera);
		m_player.Update(dt, m_level.GetBounds(), mouseWorld);

		for (Zombie& z : m_zombies)
			z.Update(dt, m_player.GetPosition());

		m_camera.target = m_player.GetPosition();
		break;
	}
}

void Game::Render()
{
	BeginDrawing();
	ClearBackground(Color{ 15,15,15,255 });

	BeginMode2D(m_camera);
	m_level.Draw();

	for (const Zombie& z : m_zombies)
		z.Draw();

	m_player.Draw();
	EndMode2D();

	DrawFPS(10, 10);
	EndDrawing();
}

void Game::UpdateCamera()
{
	Rectangle b = m_level.GetBounds();
	Vector2 p = m_player.GetPosition();

	float halfW = window_w / 2.0f / m_camera.zoom;
	float halfH = window_h / 2.0f / m_camera.zoom;

	p.x = Clamp(p.x, b.x + halfW, b.x + b.width - halfW);
	p.y = Clamp(p.y, b.y + halfH, b.y + b.height - halfH);
	m_camera.target = p;
}