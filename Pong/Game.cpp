#include "Game.h"

void Init::game()
{	
	int screen_width = 800;
	int screen_height = 600;

	InitWindow(screen_width, screen_height, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	// ----------
	// Variables
	// ----------
	const char* txt_winner = nullptr;
	const char* txt_playagain = "Play again - Press space.";

	// --------
	// Objects Variables
	// --------

	Ball ball;
	ball.x = GetScreenWidth() / 2;
	ball.y = GetScreenHeight() / 2;
	ball.radius = 7;
	ball.speedX = 200.0f;
	ball.speedY = 200.0f;
	ball.color = WHITE;

	Paddle left_paddle;
	left_paddle.x = 25;
	left_paddle.y = GetScreenHeight() / 2;
	left_paddle.width = 10;
	left_paddle.height = 100;
	left_paddle.speed = 500;
	left_paddle.color = WHITE;

	Paddle right_paddle;
	right_paddle.x = GetScreenWidth() - left_paddle.x;
	right_paddle.y = GetScreenHeight() / 2;
	right_paddle.width = 10;
	right_paddle.height = 100;
	right_paddle.speed = 500;
	right_paddle.color = WHITE;

	// ----------
	// Game loop
	// ----------

	while (!WindowShouldClose())
	{	
		// -------------------
		// Game objects logic
		// -------------------

		// -----
		// Ball
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		// Ball out of screen
		if (ball.x < 0)
		{
			txt_winner = "Right player win";
		}
		if (ball.x > GetScreenWidth())
		{
			txt_winner = "Left player win";
		}

		// --------
		// Paddles

		// Move paddles
		if (IsKeyDown(KEY_W))
		{
			left_paddle.y -= left_paddle.speed * GetFrameTime();
			if (left_paddle.y < 50)
			{
				left_paddle.y = 50;
			}
		}
		if (IsKeyDown(KEY_S))
		{
			left_paddle.y += left_paddle.speed * GetFrameTime();
			if (left_paddle.y > GetScreenHeight() - 50)
			{
				left_paddle.y = GetScreenHeight() - 50;
			}
		}

		if (IsKeyDown(KEY_UP))
		{
			right_paddle.y -= right_paddle.speed * GetFrameTime();
			if (right_paddle.y < 50)
			{
				right_paddle.y = 50;
			}
		}
		if (IsKeyDown(KEY_DOWN))
		{
			right_paddle.y += right_paddle.speed * GetFrameTime();
			if (right_paddle.y > GetScreenHeight() - 50)
			{
				right_paddle.y = GetScreenHeight() - 50;
			}
		}
		
		// Paddle and ball collision
		if (CheckCollisionCircleRec(Vector2{ (float)ball.x, (float)ball.y }, ball.radius, left_paddle.GetPos()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY += -1.1f;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ (float)ball.x,(float)ball.y }, ball.radius, right_paddle.GetPos()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY += -1.1f;
			}
		}

		// ----------------
		// Game conditions
		if (txt_winner && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 200.0f;
			ball.speedY = 200.0f;

			left_paddle.x = 25;
			left_paddle.y = GetScreenHeight() / 2;
			right_paddle.x = GetScreenWidth() - left_paddle.x;
			right_paddle.y = GetScreenHeight() / 2;

			txt_winner = nullptr;
		}

		BeginDrawing();	
		ClearBackground(BLACK);

		// ------------------
		// Draw game objects
		// ------------------
		ball.Draw();
		left_paddle.Draw();
		right_paddle.Draw();

		// ----------------
		// Game conditions
		// ----------------
		if (txt_winner)
		{
			int winner_text_size = MeasureText(txt_winner, 60);
			int playagain_text_size = MeasureText(txt_playagain, 30);
			DrawText(txt_winner, GetScreenWidth() / 2 - winner_text_size / 2, GetScreenHeight() / 2 - 30, 60, GREEN);
			DrawText(txt_playagain, GetScreenWidth() / 2 - playagain_text_size / 2, GetScreenHeight() / 2 + 60, 30, SKYBLUE);
		}

		// ------------------
		// Debug Information
		// ------------------
		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			DrawFPS(10, 10);
			DrawText("BALL X: ", 100, 10, 20, RED);
			DrawText(static_cast<const char*>(std::to_string(ball.x).c_str()), 180, 10, 20, RED);
			DrawText("Y: ", 230, 10, 20, GREEN);
			DrawText(static_cast<const char*>(std::to_string(ball.y).c_str()), 250, 10, 20, GREEN);
		}	

		EndDrawing();
	}
	CloseWindow();
}
