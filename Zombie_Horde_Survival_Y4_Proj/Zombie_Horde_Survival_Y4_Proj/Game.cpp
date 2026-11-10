#include "Game.h"
#include "raymath.h"

Game::Game()
{
	InitWindow(window_w, window_h, "Zombie Horde Survival");
	SetTargetFPS(60);

	m_camera.target = m_player.GetPosition();

	m_camera.offset = { window_w / 2.0f, window_h / 2.0f };
	m_camera.rotation = 0.0f;
	m_camera.zoom = 0.45f;
	UpdateCamera();

	/*m_zombies.emplace_back(Vector2{ 100.0f, 100.0f });
	m_zombies.emplace_back(Vector2{ 1900.0f, 100.0f });
	m_zombies.emplace_back(Vector2{ 1000.0f, 1400.0f });*/

	for (int i = 0; i < 5; i++)
	{
		SpawnZombie();
	}
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
	//(void)dt;
	switch (m_state)
	{
	case GameState::Playing:
	{
		Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), m_camera);
		m_player.Update(dt, m_level.GetBounds(), mouseWorld);

		for (Zombie& z : m_zombies)
			z.Update(dt, m_player.GetPosition());

		SeparateZombies();
		HandleCollisions();

		m_zombies.erase(
			std::remove_if(m_zombies.begin(), m_zombies.end(), [](const Zombie& z) { return !z.IsAlive(); }),
			m_zombies.end()
		);

		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0.0f && m_zombies.size() < 10)
		{
			SpawnZombie();
			m_spawnTimer = 1.5f;
		}

		UpdateCamera();

		if (m_player.IsDead())
		{
			m_state = GameState::GameOver;
		}

		//m_camera.target = m_player.GetPosition();
		break;
	}
	case GameState::GameOver:
		if (IsKeyPressed(KEY_R))
			Restart();
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
	{
		z.Draw();
		std::cout << "Enemy Spawned\n";
	}

	m_player.Draw();
	EndMode2D();

	DrawHUD();
	DrawFPS(10, 10);
	EndDrawing();
}

void Game::UpdateCamera()
{
	Rectangle bounds = m_level.GetBounds();

	Vector2 playerPos = m_player.GetPosition();

	float halfW = window_w / (2.0f * m_camera.zoom);
	float halfH = window_h / (2.0f * m_camera.zoom);

	float minX = bounds.x + halfW;
	float maxX = bounds.x + bounds.width - halfW;

	float minY = bounds.y + halfH;
	float maxY = bounds.y + bounds.height - halfH;

	if (minX > maxX)
		playerPos.x = bounds.x + bounds.width / 2.0f;
	else
		playerPos.x = Clamp(playerPos.x, minX, maxX);

	if (minY > maxY)
		playerPos.y = bounds.y + bounds.height / 2.0f;
	else
		playerPos.y = Clamp(playerPos.y, minY, maxY);

	m_camera.target = playerPos;
}

void Game::SpawnZombie()
{
	Rectangle b = m_level.GetBounds();
	const float margin = 30.0f;
	Vector2 pos{};

	switch (GetRandomValue(0, 3))
	{
	case 0: pos = { (float)GetRandomValue((int)b.x, (int)(b.x + b.width)), b.y + margin }; break;
	case 1: pos = { (float)GetRandomValue((int)b.x, (int)(b.x + b.width)), b.y + b.height - margin }; break;
	case 2: pos = { b.x + margin, (float)GetRandomValue((int)b.y, (int)(b.y + b.height)) }; break;
	default: pos = { b.x + b.width - margin, (float)GetRandomValue((int)b.y, (int)(b.y + b.height)) }; break;
	}

	m_zombies.emplace_back(pos);
}

void Game::SeparateZombies()
{
	for (size_t i = 0; i < m_zombies.size(); i++)
	{
		for (size_t j = i + 1; j < m_zombies.size(); j++)
		{
			Vector2 a = m_zombies[i].GetPosition();
			Vector2 b = m_zombies[j].GetPosition();

			float minDist = m_zombies[i].GetRadius() + m_zombies[j].GetRadius();

			Vector2 diff = Vector2Subtract(a, b);
			float dist = Vector2Length(diff);
			if (dist < minDist && dist > 0.001f)
			{
				Vector2 push = Vector2Scale(Vector2Normalize(diff), (minDist - dist) * 0.5f);
				m_zombies[i].SetPosition(Vector2Add(a, push));
				m_zombies[j].SetPosition(Vector2Subtract(b, push));
			}
		}
	}
}

void Game::HandleCollisions()
{
	for (Bullet& bullet : m_player.GetWeapon().GetBullets())
	{
		for (Zombie& z : m_zombies)
		{
			if (!z.IsAlive())
				continue;
			if (CheckCollisionCircles(bullet.pos, bullet.radius, z.GetPosition(), z.GetRadius()))
			{
				z.TakeDamage(bullet.damage);
				bullet.life = 0.0f;
				break;
			}
		}
	}

	for (const Zombie& z : m_zombies)
	{
		if (CheckCollisionCircles(m_player.GetPosition(), m_player.GetRadius(), z.GetPosition(), z.GetRadius()))
			m_player.TakeDamage(z.GetDamage());
	}
}

void Game::DrawHUD() const
{
	const int x = 10, y = 40, w = 250, h = 25;
	float pct = m_player.GetHealth() / m_player.GetMaxHealth();

	DrawRectangle(x, y, w, h, Color{ 60, 0, 0, 255 });
	DrawRectangle(x, y, (int)(w * pct), h, RED);
	DrawRectangleLines(x, y, w, h, WHITE);
	DrawText(TextFormat("%d / %d", (int)m_player.GetHealth(), (int)m_player.GetMaxHealth()), x + 8, y + 3, 18, WHITE);

	if (m_state == GameState::GameOver)
	{
		DrawRectangle(0, 0, window_w, window_h, Color{ 0, 0, 0, 160 });
		const char* title = "GAME OVER";
		const char* hint = "Press R to restart";
		DrawText(title, (window_w - MeasureText(title, 60)) / 2, window_h / 2 - 50, 60, RED);
		DrawText(hint, (window_w - MeasureText(hint, 24)) / 2, window_h / 2 + 20, 24, WHITE);
	}
}

void Game::Restart()
{
	m_player = Player();
	m_zombies.clear();
	m_spawnTimer = 0.0f;
	for (int i = 0; i < 5; i++)
		SpawnZombie();
	m_state = GameState::Playing;
}
