// 2DGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "2DGame.h"

float rndx, rndy;
int counta, countb, countc, countd;
int hits;

int main(int argc, char* args[])
{
	bool quit = false;
	SDL_Event event;
	stringstream ss;
	int mouseX, mouseY;
	float objectx, objecty;
	float dx, dy, dist;
	Point2D* p2dp = new Point2D(300, 300);

	Circle* cp = new Circle(p2dp, 0, 0, 0, 255, 10);

	hits = 0;

	objectx = 300;
	objecty = 300;

	srand(time(NULL));

	dx = rand() % 2;
	if (dx == 1)
		dx = -1;
	else
		dx = 1;
	
	dy = rand() % 2;
	if (dy == 1)
		dy = -1;
	else
		dy = 1;

	makernd();

	counta = 0;
	countb = 0;
	countc = 0;
	countd = 0;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("2DGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Surface* image = SDL_LoadBMP("Circle.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderClear(renderer);

	drawShape(renderer);

	SDL_RenderPresent(renderer);

	cout << "Hit the circle 20 times with your mouse as quick as you can. Good luck!" << endl;

	auto start = chrono::high_resolution_clock::now();

	while (!quit)
	{
		SDL_Delay(20);
		
		moveObject(renderer, objectx, objecty, dx, dy);
		SDL_Rect dstrect = { objectx, objecty, 32, 32 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		drawShape(renderer);
		cp->render(renderer, objectx, objecty);
		//SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
		
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseX = event.motion.x;
			mouseY = event.motion.y;

			dist = sqrt((mouseX - objectx) * (mouseX - objectx) + (mouseY - objecty) * (mouseY - objecty));
			if (dist < 10)
			{
				hits++;
				cout << "Hits :" << hits << endl;
				if (hits >= 20)
					quit = true;
			}
			break;
		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;

			mouseY = event.motion.y;

			ss.str("");

			ss << "X: " << mouseX << " Y: " << mouseY;

			SDL_SetWindowTitle(window, ss.str().c_str());

			//hitTest(renderer, mouseX, mouseY);

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

	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;
	if (hits == 20)
	{
		cout << "You finished 20 hits in : " << elapsed.count() << " sec" << endl;;
		SDL_Delay(3000);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	

	return 0;
}

void moveObject(SDL_Renderer* render, float& objectx, float& objecty, float &dx, float &dy)
{
	

	objectx += (dx * rndx);
	objecty += (dy * rndy);
	counta++;
	countb++;
	countc++;
	countd++;
	//objectx += dx;
	//objecty += dy;

	if (hitTest(render, objectx, objecty, 100, 100, 100, 500) == true)
	{
		if (counta > 5)
		{
			dx *= -1;
			makernd();
			counta = 0;
		}
	}
	if (hitTest(render, objectx, objecty, 100, 100, 500, 100) == true)
	{
		if (countb > 5)
		{
			dy *= -1;
			makernd();
			countb = 0;
		}
	}
	if (hitTest(render, objectx, objecty, 100, 500, 500, 500) == true)
	{
		if (countc > 5)
		{
			dy *= -1;
			makernd();
			countc = 0;
		}
	}
	if (hitTest(render, objectx, objecty, 500, 100, 500, 500) == true)
	{
		
		if (countd > 5)
		{
			dx *= -1;
			makernd();
			countd = 0;
		}
	}
}

void makernd()
{
	srand(time(NULL));

	rndx = rand() % 60 + 70;
	rndx = rndx / 100;
	cout << "Rndx :" << rndx << endl;
	rndy = rand() % 60 + 70;
	rndy = rndy / 100;
	cout << "Rndy :" << rndy << endl;
}
//https://www.xarg.org/book/computer-graphics/2d-hittest/

bool hitTest(SDL_Renderer *render, int x, int y, int point1x, int point1y, int point2x, int point2y)
{
	float r, dc,db,bxc,bprodx, bprody ,axb, bxb, dp3p,dp3p1,dp3p2, ax, ay, bx, by, cx, cy, p1x, p1y, p2x, p2y, p3x, p3y, px, py;

/*
	p1x = 100;
	p1y = 100;
	p2x = 100;
	p2y = 200;
*/
	p1x = point1x;
	p1y = point1y;
	p2x = point2x;
	p2y = point2y;

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
		//cout << "Hit!" << endl;
		return true;
	}
	else
	{
		//cout << "Not hit" << endl;
		return false;
	}

}

void drawShape(SDL_Renderer *render)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderDrawLine(render, 100, 100, 100, 500);
	SDL_RenderDrawLine(render, 100, 100, 500, 100);
	SDL_RenderDrawLine(render, 100, 500, 500, 500);
	SDL_RenderDrawLine(render, 500, 100, 500, 500);
}

Shape::Shape()
{

}

Shape::Shape(Point2D* position, char red, char green, char blue, char alpha) :
	position(position), red(red), green(green), blue(blue), alpha(alpha)
{

}

Circle::Circle()
{

}
Circle::Circle(Point2D* position, char red, char green, char blue, char alpha, int radius) :
	Shape(position, red, green, blue, alpha), radius(radius)
{

}

void Circle::render(SDL_Renderer* render, int x, int y)
{
	float theta = 0.0;
	int circlecenterX = x;
	int circlecenterY = y;
	float step = 2.0 * M_PI / 32;
	int xpos, ypos, yposold, xposold;
	int radius = 10;

	//cout << "Position : " << position->toString() << endl;
	//cout << "Radius : " << radius << endl;

	xpos = circlecenterX + radius * cos(theta);
	ypos = circlecenterY + radius * sin(theta);

	yposold = ypos;
	xposold = xpos;

	theta += step;

	while (theta <= (2.0 * M_PI + step))
	{
		xpos = circlecenterX + radius * cos(theta);
		ypos = circlecenterY + radius * sin(theta);

		SDL_RenderDrawLine(render, xpos, ypos, xposold, yposold);

		yposold = ypos;
		xposold = xpos;

		theta += step;
	}
}

Point2D::Point2D(int x, int y) : x(x), y(y)
{

}

Point2D::Point2D()
{
	x = 0;
	y = 0;
}

float Point2D::getX()
{
	return x;
}

float Point2D::getY()
{
	return y;
}

void Point2D::setX(float x)
{
	x = x;
}

void Point2D::setY(float y)
{
	y = y;
}

Point2D::Point2D(const Point2D& p2d) // copy constructor
{
	x = p2d.x;
	y = p2d.y;
}
float Point2D::Distance(Point2D p2d)
{
	return (sqrt(pow(p2d.x, 2) + pow(p2d.y, 2)));
}
string Point2D::toString()
{
	string ret;

	ret = "[" + to_string(x) + "," + to_string(y) + "]";

	return ret;
}

Point2D Point2D::operator+(const Point2D& p2d)
{
	Point2D temp;

	temp.x = x + p2d.x;
	temp.y = y + p2d.y;

	return temp;
}
bool Point2D::operator== (const Point2D& p2d)
{
	if (x == p2d.x && y == p2d.y)
		return true;
	else
		return false;
}
Point2D& Point2D::operator=(const Point2D& p2d)
{
	x = p2d.x;
	y = p2d.y;
	return *this;
}
