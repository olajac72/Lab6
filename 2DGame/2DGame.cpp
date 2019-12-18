// 2DGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SSTREAM>
#include <SDL.h>

using namespace std;

void drawShape(SDL_Renderer* render);
void hitTest(SDL_Renderer* render, int x, int y);

int main(int argc, char* args[])
{
	bool quit = false;
	SDL_Event event;
	stringstream ss;
	int mouseX, mouseY;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("2DGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderClear(renderer);

	drawShape(renderer);

	SDL_RenderPresent(renderer);


	while (!quit)
	{


		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;

			mouseY = event.motion.y;

			ss.str("");

			ss << "X: " << mouseX << " Y: " << mouseY;

			SDL_SetWindowTitle(window, ss.str().c_str());

			hitTest(renderer, mouseX, mouseY);

			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_q:
				quit = true;
				break;
			}
		}

		
	}

	//SDL_Delay(3000);

	return 0;
}

//https://www.xarg.org/book/computer-graphics/2d-hittest/

void hitTest(SDL_Renderer *render, int x, int y)
{
	float r, dc,db,bxc,bprodx, bprody ,axb, bxb, dp3p,dp3p1,dp3p2, ax, ay, bx, by, cx, cy, p1x, p1y, p2x, p2y, p3x, p3y, px, py;


	p1x = 100;
	p1y = 100;
	p2x = 100;
	p2y = 200;
	p3x = x;
	p3y = y;
	r = 10.0;

	bx = p2x - p1x;
	by = p2y - p1y;

	ax = p3x - p1x;
	ay = p3y - p1y;

	

	axb = ax * bx + ay * by;
	bxb = bx * bx + by * by;

	bprodx = axb / bxb * bx;
	bprody = axb / bxb * by;

	px = p1x + bprodx;
	py = p1y + bprody;

	cx = px - p1x;
	cy = py - p1y;

	dc = sqrt(cx * cx + cy * cy);
	db = sqrt(bx * bx + by * by);
	bxc = bx * cx + by * cy;

	dp3p = sqrt((p3x - px) * (p3x - px) + (p3y - py) * (p3y - py));
	dp3p1 = sqrt((p3x - p1x) * (p3x - p1x) + (p3y - p1y) * (p3y - p1y));
	dp3p2 = sqrt((p3x - p2x) * (p3x - p2x) + (p3y - p2y) * (p3y - p2y));

	if (((dp3p < r) && (dc < db) && (bxc > 0.0)) || (dp3p1 < r) || (dp3p2 < r))
	{
		cout << "Hit!" << endl;
	}
	else
	{
		cout << "Not hit" << endl;
	}

}

void drawShape(SDL_Renderer *render)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderDrawLine(render, 100, 100, 100, 200);
}