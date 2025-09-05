#pragma once

#include "Entity.h"
#include "EntityManager.h"


#include <SFML/Graphics.hpp>

// shape rad, collision rad, fill r, g, b, outer r, g, b, out thic, vertices, speed
struct PlayerConfig {int SR, CR, FR, FG,FB, OR, OG, OB, OT, V; float S;};
// shape rad, collision rad, fill r, g, b, outer r, g, b, out thic, VMIN -> vertices min, max, L -> small lifespan, spawn interval, Smin -> speed min max
struct EnemyConfig {int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;};
// shape rad, collision rad, fill r, g, b, outer r, g, b, out thic, vertices, lifespan, speed
struct BulletConfig {int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;};

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;

	std::shared_ptr<Entity> m_player;

	void init(const std::string& config); // reads from config file
	void setPaused(bool paused);

	// system funcs
	void sMovement();
	void sUserInput();
	void sLifespan();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	// helpers
	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

	Game(const std::string& config);

	void run();
};
