// Pong v2.0.0

#include "Game.h"

void game()
{	
	int screen_width = 800;
	int screen_height = 600;

	InitWindow(screen_width, screen_height, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	// ----------
	// Variables
	// ----------

	// Texts
	const char* txt_winner = nullptr;
	const char* txt_playagain = "Play again - Press space.";

	// Prevents wins from being counted more than once in a cycle until the game starts again
	bool winner_is = false;

	// Default colors
	Color background_color = BLACK;
	Color score_color = YELLOW;
	Color wins_color = BLUE;

	// Counters
	Counter lp_score;
	Counter rp_score;
	Counter lp_wins;
	Counter rp_wins;

	// --------
	// Objects Variables
	// --------
	Ball ball;

	ball.defX = GetScreenWidth() / 2;
	ball.defY = GetScreenHeight() / 2;
	ball.defSpeedX = 200.0f;
	ball.defSpeedY = 200.0f;

	ball.x = ball.defX;
	ball.y = ball.defY;
	ball.radius = 7;
	ball.speedX = ball.defSpeedX;
	ball.speedY = ball.defSpeedY;
	ball.color = WHITE;

	Paddle left_paddle;

	left_paddle.defX = 25;
	left_paddle.defY = GetScreenHeight() / 2;
	left_paddle.defSpeed = 500;

	left_paddle.x = left_paddle.defX;
	left_paddle.y = left_paddle.defY;
	left_paddle.width = 10;
	left_paddle.height = 100;
	left_paddle.speed = left_paddle.defSpeed;
	left_paddle.color = WHITE;

	Paddle right_paddle;

	right_paddle.defX = GetScreenWidth() - left_paddle.x;
	right_paddle.defY = GetScreenHeight() / 2;

	right_paddle.x = right_paddle.defX;
	right_paddle.y = right_paddle.defY;
	right_paddle.width = 10;
	right_paddle.height = 100;
	right_paddle.speed = left_paddle.defSpeed;
	right_paddle.color = WHITE;

	// ----------
	// Game loop
	// ----------

	while (!WindowShouldClose())
	{	
		// -----------------------------
		// Non-game proccess conditions
		// -----------------------------

		// -------------------
		// Change game colors
		if (IsKeyDown(KEY_ONE))
		{
			left_paddle.color = WHITE;
			right_paddle.color = WHITE;
			ball.color = WHITE;
			background_color = BLACK;
			score_color = YELLOW;
			wins_color = BLUE;
		}

		if (IsKeyDown(KEY_TWO))
		{
			left_paddle.color = BLACK;
			right_paddle.color = BLACK;
			ball.color = BLACK;
			background_color = WHITE;
			wins_color = RED;
			score_color = GREEN;
		}

		if (IsKeyDown(KEY_THREE))
		{
			left_paddle.color = YELLOW;
			right_paddle.color = YELLOW;
			ball.color = YELLOW;
			background_color = BLUE;
			wins_color = WHITE;
			score_color = GREEN;
		}

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
		if (ball.x < 0 && !winner_is)
		{
			txt_winner = "Right player win";
			rp_wins.add_count();
			winner_is = true;
		}
		if (ball.x > GetScreenWidth() && !winner_is)
		{
			txt_winner = "Left player win";
			lp_wins.add_count();
			winner_is = true;
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
			lp_score.add_count();
		}
		if (CheckCollisionCircleRec(Vector2{ (float)ball.x,(float)ball.y }, ball.radius, right_paddle.GetPos()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY += -1.1f;
			}
			rp_score.add_count();
		}

		// ----------------
		// Game conditions
		if (txt_winner && IsKeyPressed(KEY_SPACE))
		{
			// reset ball cords and speed
			ball.x = ball.defX;
			ball.y = ball.defY;
			ball.speedX = ball.defSpeedX;
			ball.speedY = ball.defSpeedY;

			// reset paddle cords
			left_paddle.x = left_paddle.defX;
			left_paddle.y = left_paddle.defY;
			right_paddle.x = right_paddle.defX;
			right_paddle.y = right_paddle.defY;

			// reset current winner
			txt_winner = nullptr;

			// reset score
			lp_score.clear_count();
			rp_score.clear_count();

			// set false winner_is
			winner_is = false;
		}

		BeginDrawing();	
		ClearBackground(background_color);

		// ------------------
		// Draw game objects
		// ------------------
		ball.Draw();
		left_paddle.Draw();
		right_paddle.Draw();

		// ------
		// Score
		// ------
		
		// Score

		DrawText("Score", GetScreenWidth() / 2 - (90 / 2), GetScreenHeight() - 60, 30, score_color);
		DrawText(static_cast<const char*>(std::to_string(lp_score.get_count()).c_str()),
			20, GetScreenHeight() - 60, 60, score_color);
		DrawText(static_cast<const char*>(std::to_string(rp_score.get_count()).c_str()),
			GetScreenWidth() - 50, GetScreenHeight() - 60, 60, score_color);

		// Wins
		DrawText("Wins", GetScreenWidth() / 2 - (63 / 2), 20, 30, wins_color);
		DrawText(static_cast<const char*>(std::to_string(lp_wins.get_count()).c_str()),
			20, 20, 60, wins_color);
		DrawText(static_cast<const char*>(std::to_string(rp_wins.get_count()).c_str()),
			GetScreenWidth() - 50, 20, 60, wins_color);

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