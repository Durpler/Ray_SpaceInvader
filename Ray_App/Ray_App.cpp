// SpaceInvader clone

#include <raylib.h>
#include <cstdlib>
#include <iostream>

static void InitGame(void);  // Initialize the game / setup
static void UpdateGame(void); // update game loop
static void DrawGame();  // Draw game (draw frame)

// Player definition: 
typedef struct stPlayer
{
	Rectangle rect;
	Vector2 speed; 
	Color color;
} Player;

// Bullet definition:
typedef struct stBullet
{
	Rectangle rect; 
	Vector2 speed; 
	bool bActive; 
	Color color;
}Bullet;

// Enemy definition: 
typedef struct stEnemy
{
	Rectangle rect; 
	Vector2 speed; 
	bool bActive; 
	Color color; 
}Enemy;


// globals
static Player player;
static int screenWidth = 1920;
static int screenHeight = 1080;

static int shotRate = 0; 
const int NUM_SHOTS = 50;
static Bullet bullets[NUM_SHOTS];

const int NUM_MAX_ENEMIES = 50; 
static Enemy enemies[NUM_MAX_ENEMIES]; 
static int activeEnemies = 0; 

void InitGame(void)
{

	// init player
	player.rect.x = screenWidth /2.0f;
	player.rect.y = screenHeight - 20.0f; 
	player.rect.width = 20; 
	player.rect.height = 20; 
	player.speed.x = 5; 
	player.speed.y = 5; 
	player.color = RED; 

	// Initialize shots
	for (auto &it : bullets)
	{
		it.rect.x = player.rect.x;
		it.rect.y = player.rect.y + player.rect.height / 4; 
		
		it.rect.width = 5; 
		it.rect.height = 10; 
		it.speed.x = 0.0f; 
		it.speed.y = -10.0f;
		it.bActive = false; 
		it.color = YELLOW; 
	}

	// initialize Enemies
	activeEnemies = 10; 
	
	for (auto &it : enemies)
	{
		it.rect.width = 20.0f; 
		it.rect.height = 20.0f;
		it.rect.x = (float) GetRandomValue(0, screenWidth); 
		it.rect.y = (float)GetRandomValue(-screenHeight, -20); 
		it.speed.x = 5.0f; 
		it.speed.y = 5.0f; 
		it.bActive = true; 
		it.color = BLUE;
	}
}

void UpdateGame(void)
{
	if (IsKeyDown(KEY_F11))
	{
		ToggleFullscreen();
	}
	// check for input and move character
	if (IsKeyDown(KEY_RIGHT))
		player.rect.x += player.speed.x;
	if (IsKeyDown(KEY_LEFT))
		player.rect.x -= player.speed.x;

	// wall behaviour
	if (player.rect.x <= 0)
		player.rect.x = 0; 
	if (player.rect.x + player.rect.width >= screenWidth)
		player.rect.x = screenWidth - player.rect.width; 

	// check for fire being pressed
	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		shotRate += 5; 
		for (auto &it : bullets)
		{
			// limit the activation of every bullet
			if (!it.bActive && shotRate % 40 == 0)
			{
				it.rect.x = player.rect.x; 
				it.rect.y = player.rect.y + player.rect.height / 4; 
				it.bActive = true; 
				break;
			}
		}
	}

	// update bullet movement and hide over boundary
	for (auto &it : bullets)
	{
		if (it.bActive)
		{
			it.rect.y += it.speed.y; 
			
			// if bullet goes above the screen
			if (it.rect.y <= 0)
			{
				it.bActive = false; 
				shotRate = 0; 
			}

			// Check for collision with enemy
			for (auto& itEnemy : enemies)
			{
				if (itEnemy.bActive)
				{
					// collision check
					if (CheckCollisionRecs(it.rect, itEnemy.rect))
					{
						it.bActive = false; 
						itEnemy.rect.x = (float)GetRandomValue(screenWidth, screenWidth + 1000);
						itEnemy.rect.y = (float)GetRandomValue(0, screenHeight - itEnemy.rect.height);
						shotRate = 0; 
					}
				}
			}
		}
	}

	// update enemy movement
	for (auto& it : enemies)
	{
		if (it.bActive)
		{
			it.rect.y += it.speed.y; // add speed for movement

			// reset enemy on crossing the boundary
			if (it.rect.y > screenHeight)
			{
				it.rect.x = (float)GetRandomValue(0, screenWidth); 
				it.rect.y = (float)GetRandomValue(-screenHeight, -20);
			}
		}
	}


}

void DrawGame()
{
	BeginDrawing(); 
	ClearBackground(BLACK);

	// draw player
	DrawRectangleRec(player.rect, player.color);

	// draw bullets
	for (auto &it : bullets)
	{
		if (it.bActive)
		{ 
			DrawRectangleRec(it.rect, it.color); 
		}
	}

	// draw enemies
	for (auto& it : enemies)
	{
		if (it.bActive)
		{
			DrawRectangleRec(it.rect, it.color);
		}
	}
	EndDrawing();
}


int main()
{

	InitWindow(screenWidth, screenHeight, "SpaceInvaders - raylib-clone");
	SetTargetFPS(60); 
	InitGame(); 

	//mai8n loop
	while (!WindowShouldClose())
	{
		UpdateGame(); 
		DrawGame();
	}
	CloseWindow();

	return EXIT_SUCCESS;
}
