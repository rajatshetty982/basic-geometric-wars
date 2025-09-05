#include "Game.h"

#include <iostream>
#include <math.h>
#include <fstream>
// #include <cstdlib> // For rand() and srand()

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string &path)
{
	std::string font_path;
	int font_size, f_r, f_g, f_b;
	int win_w, win_h, fps;
	bool fullscreen;

	std::cout << "\n";
	std::cout << "Current working directory: ";
	system("pwd"); // prints working directory
	std::cout << "\n";

	// read config file start
	std::ifstream fin(path);
	if (!fin.is_open())
	{
		std::cerr << "Error opening file\n";
		exit(1);
	}

	std::string type;
	while (fin >> type)

	{
		if (type == "window")
		{
			fin >> win_w >> win_h >> fps >> fullscreen;
		}
		else if (type == "Font")
		{
			fin >> font_path >> font_size >> f_r >> f_g >> f_b;
		}
		else if (type == "Player")
		{

			fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S
				>> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB 
				>> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB
				>> m_playerConfig.OT >> m_playerConfig.V;
		}
		else if (type == "Enemy")
		{
			fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN 
				>> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG 
				>> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN
				>> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
		}
		else if (type == "Bullet")
		{
			fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S
				>> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB
				>> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
				>> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L ;
		}
	}
	// read config file end

	
	// set default window params
	if (fullscreen)
	{
		auto mode = sf::VideoMode::getDesktopMode();
		m_window.create(sf::VideoMode(mode), "AAA Game", sf::Style::Fullscreen);
	}
	else 
	{
		m_window.create(sf::VideoMode(win_w, win_h), "AAA Game");
	}
	m_window.setFramerateLimit(fps);

	spawnPlayer();
}

void Game::run(){
	// TODO: add pause functionality
	// 		 some systems should be running while paused (rendering)
	//		 movements and inputs should halt

	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		}
		sRender();

		// increment the current frame;
		// may need to be moved when pause is implemented
		m_currentFrame++;
	}
}


void Game::setPaused(bool paused) // TODO Unused. Use when the p button is pressed
{
	m_paused = paused;
}

void Game::spawnPlayer()
{
	// NOTE: this is done
	// finish adding all properties of the player 
	// with the correct values from the config

	// returns a shared ptr of Entiry type
	auto entity = m_entities.addEntity("player");

	// get cent of the window
	// to get in the center of the window we get window size(width, height)  and devide it by 2 
	sf::Vector2 window_size = m_window.getSize();
	Vec2 center_of_window(window_size.x / 2.0f, window_size.y / 2.0f); // vec2 with x, y of center of the window

	entity->cTransform  = std::make_shared<CTransform>(center_of_window, Vec2(10.0f,0.0f),0); // * NOTE: assumed that we start at 0 vel and angle

	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, 
		sf::Color(m_playerConfig.FR, m_playerConfig.FG ,m_playerConfig.FB),
		sf::Color(m_playerConfig.OR , m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity;

}

void Game::spawnEnemy()
{
	// // TODO make sure the enemy us spawned with the m_enemyConfig vars
	// // the enemy must be spawned completely within the bounds of the window
	// auto entity = m_entities.addEntity("enemy");

	// srand(static_cast<unsigned int>(time(0))); // seed the rand generator

	// // configure the enemy
	// //  get rand pos x
	// int x_start = m_enemyConfig.SR;
	// int x_end = m_window.getSize().x -  m_enemyConfig.SR;
	// float x_rand = x_start + (rand() % (x_end - x_start));

	// // get rand pos y
	// int y_start = m_enemyConfig.SR;
	// int y_end =  m_window.getSize().y - m_enemyConfig.SR;
	// float y_rand = y_start + (rand() % (y_end - y_start));

	// // get the velocity
	// float speed_min = m_enemyConfig.SMIN;
	// float speed_max = m_enemyConfig.SMAX;
    // float random_speed = speed_min + (static_cast<float>(rand()) / RAND_MAX) * (speed_max - speed_min);

	// // rand angle for shapes movement inside the window
	// float random_angle = rand() % 360;

	// float v_x = cos(random_angle) * random_speed; // * Note check the angle
	// float v_y = sin(random_angle) * random_speed; // * Note check the angle
	// Vec2 velocity(v_x, v_y);

	// entity->cTransform = std::make_shared<CTransform>(Vec2(x_rand, y_rand), Vec2(v_x, v_y), random_angle); // * Check Change angle here? think 

	// // record the most recernt enemy was spawned
	// m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	// spanw smaller enemies at location of the enemy e

	// read the e to get the details
		// spawn n spawn enemies for n sides of e
		// set same colour and half the size
		// these are worth double of original enemy

}

void Game::spawnBullet(std::shared_ptr<Entity> e, const Vec2& target)
{
	// TODO 
	// bullet travels to the target
	// bullet speed is given as S
	// set velocity accoring to MATH!!

	auto bullet = m_entities.addEntity("bullet");
	// MATHH!!
	// get x and y by minusing
	float x_player = m_player->cTransform->pos.x;
	float y_player = m_player->cTransform->pos.y;
	float x_length = target.x - x_player;
	float y_length = target.y - y_player;

	// get the angle of click to current player pos
	float result_radians = std::atan2(y_length, x_length);
	float angle_q = (result_radians * 180) / M_PI;

	// use the angle to get the velocity x and y
	Vec2 velocity;
	velocity.x = cos(angle_q) * m_bulletConfig.S;
	velocity.y = sin(angle_q) * m_bulletConfig.S;
	// MATH END!!

	bullet->cTransform = std::make_shared<CTransform>(target, velocity, 0);

	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V,
											  sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
											  sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
											  m_bulletConfig.OT);

		// TODO bullet should have lifespan depending on movement
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> e)
{
	// TODO THINK YO!
}

void Game::sMovement()
{
	// // TODO
	// // All entity movement here
	// 	// read the m_player->cInput comp to determine if the player is moving
	// 	///added now
	// // get the x and y movement for the velocity
	// float hypotenus = m_playerConfig.S;
	// // FIXME: this is for temp purpose. angle should be gotten by the input and class of the player. idk how rn
	
	// // TODO the angle  will be 0, 45 90 etc, according to the input key
	// float v_x = cos(10) * hypotenus; // TODO change the angle
	// float v_y = cos(10) * hypotenus; // TODO change the angle
	// Vec2 velocity(v_x, v_y);

	// 	//

	// // set vel to 0 at every frame
	// m_player->cTransform->velocity =  {0,0};

	// // implement movement
	// if (m_player->cInput->up)
	// {
	// 	m_player->cTransform->velocity.y = -5; // TODO this should be according to the S
	// }

	// // sample
	// m_player->cTransform->pos.x = m_player->cTransform->velocity.x;
	// m_player->cTransform->pos.y = m_player->cTransform->velocity.y;
}

void Game::sLifespan()
{
	// TODO 
	// for all entities
	// if entity has no lifespan comp skip
	// if it has > than 0 subtract 1
	// if has lifespan and alive
		// scale alpha properly (it should have alpha of percentage of it life left)
	// if has lifespan and is 0
		// destroy!!
}

void Game::sCollision()
{
// 	// TODO
// 	// implement the collisions
// 	// use coll rad not the Shape rad

// 	for (auto b : m_entities.getEntities("bullet"))
// 	{
// 		for (auto e : m_entities.getEntities("enemy"))
// 		{
// 			// TODO if collision radius is colliding the collision radius of the enemy
// 		// if collided
// 		//{
// 			b->destroy();
// 			e->destroy();

// //		}
// 		// update the isActive to false
// 		}
// 	}
}

void Game::sEnemySpawner()
{
	// TODO enemy spawning will go here

	// use m_currentFrame - m_lastEnemySpawnTime to determine
	// to get how long it has ben since last enemy spawned
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI){
		spawnEnemy();
	}
}

void Game::sRender()
{
	m_window.clear();

	for (auto e: m_entities.getEntities())
	{
		if (e->cShape && e->cTransform)
		{

		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		e->cTransform->angle += 4.0f;
		e->cShape->circle.setRotation(e->cTransform->angle); // older one circleRotation(m_player->cTransform->angle);
		
		m_window.draw(e->cShape->circle);
		}
	}
	m_window.display();
}

void Game::sUserInput()
{
	// TODO handle user input
	//	set the players input component vars here
	// no movement logic here
	// movement system does the loigc by reading the vars set here

	m_player->cInput->down = false;
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		// when key press event
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::W:
				{
					std::cout << "W pressed\n";
					m_player->cInput->up = true;
					// TODO set the vars here
					break;
				}

				case sf::Keyboard::S:
				{
					std::cout << "S pressed\n";
					m_player->cInput->down = true;
					break;
				}

				case sf::Keyboard::A:
				{
					std::cout << "A pressed\n";
					m_player->cInput->left = true;
					break;
				}

				case sf::Keyboard::D:
				{
					std::cout << "D pressed\n";
					m_player->cInput->right = true;
					break;
				}

			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::W:
				{
					std::cout << "W released\n";
					m_player->cInput->up = false;
					// TODO set the vars here
					break;
				}

				case sf::Keyboard::S:
				{
					std::cout << "S released\n";
					m_player->cInput->down = false;
					break;
				}

				case sf::Keyboard::A:
				{
					std::cout << "A released\n";
					m_player->cInput->left = false;
					break;
				}

				case sf::Keyboard::D:
				{
					std::cout << "D released\n";
					m_player->cInput->right = false;
					break;
				}
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left mouse Button at (" << event.mouseButton.x << ","
				<< event.mouseButton.y << ")\n";
				// TODO call spawn the bullets
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y)); // TODO check
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Left mouse Button at (" << event.mouseButton.x << ","
				<< event.mouseButton.y << ")\n";
				// call special weapon
				spawnSpecialWeapon(m_player); // TODO check
		}
	}
}

}


	//! print all
    // std::cout << "=== Window Config ===\n";
    // std::cout << "Width       : " << win_w << "\n";
    // std::cout << "Height      : " << win_h << "\n";
    // std::cout << "FPS         : " << fps << "\n";
    // std::cout << "Fullscreen  : " << (fullscreen ? "Yes" : "No") << "\n\n";

    // std::cout << "=== Font Config ===\n";
    // std::cout << "Font path   : " << font_path << "\n";
    // std::cout << "Font size   : " << font_size << "\n";
    // std::cout << "Color (RGB) : (" << f_r << ", " << f_g << ", " << f_b << ")\n\n";

    // std::cout << "=== Player Config ===\n";
    // std::cout << "SR : " << m_playerConfig.SR << "\n";
    // std::cout << "CR : " << m_playerConfig.CR << "\n";
    // std::cout << "S  : " << m_playerConfig.S << "\n";
    // std::cout << "FR : " << m_playerConfig.FR << "\n";
    // std::cout << "FG : " << m_playerConfig.FG << "\n";
    // std::cout << "FB : " << m_playerConfig.FB << "\n";
    // std::cout << "OR : " << m_playerConfig.OR << "\n";
    // std::cout << "OG : " << m_playerConfig.OG << "\n";
    // std::cout << "OB : " << m_playerConfig.OB << "\n";
    // std::cout << "OT : " << m_playerConfig.OT << "\n";
    // std::cout << "V  : " << m_playerConfig.V << "\n\n";

    // std::cout << "=== Enemy Config ===\n";
    // std::cout << "SR    : " << m_enemyConfig.SR << "\n";
    // std::cout << "CR    : " << m_enemyConfig.CR << "\n";
    // std::cout << "SMIN  : " << m_enemyConfig.SMIN << "\n";
    // std::cout << "SMAX  : " << m_enemyConfig.SMAX << "\n";
    // std::cout << "OR    : " << m_enemyConfig.OR << "\n";
    // std::cout << "OG    : " << m_enemyConfig.OG << "\n";
    // std::cout << "OB    : " << m_enemyConfig.OB << "\n";
    // std::cout << "OT    : " << m_enemyConfig.OT << "\n";
    // std::cout << "VMIN  : " << m_enemyConfig.VMIN << "\n";
    // std::cout << "VMAX  : " << m_enemyConfig.VMAX << "\n";
    // std::cout << "L     : " << m_enemyConfig.L << "\n";
    // std::cout << "SI    : " << m_enemyConfig.SI << "\n\n";

    // std::cout << "=== Bullet Config ===\n";
    // std::cout << "SR : " << m_bulletConfig.SR << "\n";
    // std::cout << "CR : " << m_bulletConfig.CR << "\n";
    // std::cout << "S  : " << m_bulletConfig.S << "\n";
    // std::cout << "FR : " << m_bulletConfig.FR << "\n";
    // std::cout << "FG : " << m_bulletConfig.FG << "\n";
    // std::cout << "FB : " << m_bulletConfig.FB << "\n";
    // std::cout << "OR : " << m_bulletConfig.OR << "\n";
    // std::cout << "OG : " << m_bulletConfig.OG << "\n";
    // std::cout << "OB : " << m_bulletConfig.OB << "\n";
    // std::cout << "OT : " << m_bulletConfig.OT << "\n";
    // std::cout << "V  : " << m_bulletConfig.V << "\n";
    // std::cout << "L  : " << m_bulletConfig.L << "\n";
	//////////////////////////////// !