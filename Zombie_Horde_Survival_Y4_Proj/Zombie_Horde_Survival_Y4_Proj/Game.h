#pragma once
#include "raylib.h"
#include "Level.h"
#include "Player.h"
#include "Zombie.h"
#include <vector>
#include <iostream>

enum class GameState
{
	Playing,
	GameOver
};

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Update(float dt);
	void Render();
	void UpdateCamera();

	void SpawnZombie();
	void SeparateZombies();
	void HandleCollisions();
	void Restart();

	static constexpr int window_w = 1280;
	static constexpr int window_h = 720;

	Camera2D m_camera{};
	GameState m_state = GameState::Playing;

	Level m_level;
	Player m_player;
	std::vector<Zombie> m_zombies;

	float m_spawnTimer = 0.0f;
};