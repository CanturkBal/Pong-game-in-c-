#include <iostream>

#include "raylib.h"



int player_score; 
int cpu_score;



class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void draw() {
		DrawCircle(x, y, radius, WHITE);
	}

	void update() {
		x += speed_x;
		y += speed_y;

		if (y + radius > GetScreenHeight() || y - radius < 0) {
			speed_y *= -1;
		}
		if (x + radius > GetScreenWidth() || x - radius < 0) {
			speed_x *= -1;
		}
		if (x + radius >= GetScreenWidth()) {
			player_score++;
		}
		if (x - radius <= 0) {
			cpu_score++;
		}

	}
};

Ball ball;


class Paddle {
public:
	float x, y;
	int width, height;
	int speed;


	void draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}
	void update() {

		

		
		if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		
		}
		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}
};

Paddle paddle;





class CPU {
public:
	float x, y;
	int width, height;
	int speed;


	void draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}

	void update(int bally) {
		if (y + height/2  > ball.y) {
			y = y - speed;
		}
		if (y + height/2 < ball.y) {
			y = y  + speed;
		}
	}
};





CPU cpu;

using namespace std;
int main() {
	
	std::cout << "Starting the game." << std::endl;
	const int screen_width = 1280;
	const int screen_height = 800;
	InitWindow(screen_width, screen_height, "Pong game");
	SetTargetFPS(60);


	ball.x = screen_height / 2;
	ball.y = screen_height / 2;
	ball.radius = 20;
	ball.speed_x = 12;
	ball.speed_y = 12; 


	paddle.x = 10;
	paddle.y = screen_height / 2;
	paddle.width = 25;
	paddle.height = 125; 
	paddle.speed = 10; 


	cpu.x = screen_width - 35;
	cpu.y = screen_height / 2;
	cpu.width = 25; 
	cpu.height = 125;
	cpu.speed = 10; 




	while (WindowShouldClose() == false) {
		BeginDrawing();
		ball.update();
		paddle.update();
		cpu.update(ball.y);
		ClearBackground(BLACK);



		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ paddle.x,paddle.y,float(paddle.width),float(paddle.height) })) {
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpu.x,cpu.y,float(cpu.width),float(cpu.height) })) {
			ball.speed_x *= -1;
		}



		DrawLine(screen_width / 2,0, screen_width / 2, screen_height, WHITE);
		ball.draw();
		paddle.draw();
		cpu.draw();



		DrawText(TextFormat("%i", player_score), (screen_width / 4) - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", cpu_score), 3* (screen_width / 4) - 20, 20, 80, WHITE);


		EndDrawing();
	}

	CloseWindow();
	

	
	return 0;

}
