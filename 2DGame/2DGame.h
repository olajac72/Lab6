#pragma once
#include <iostream>
#include <SSTREAM>
#include <SDL.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <string>
#include <math.h>
#include <vector>
#include <chrono>

using namespace std;

class Obstacle;

void drawShape(SDL_Renderer* render, vector<Obstacle*> obstacle, int boardx);
bool hitTest(SDL_Renderer* render, int x, int y, int point1x, int point1y, int point2x, int point2y);
void moveObject(SDL_Renderer* render, float& objectx, float& objecty, float& dx, float& dy, vector<Obstacle*> obstacle, int boardx);
void makernd();
void initboard(SDL_Renderer* render, vector<Obstacle*> &obstacle);

class Point2D;

class Obstacle
{
public:
	int beginx, beginy, endx, endy;
	bool hit;
	void draw();
	SDL_Renderer* render;
	Obstacle(SDL_Renderer * rend, int bx, int by, int ex, int ey);
};

class Shape
{
protected:
	Point2D* position;
	char red, green, blue, alpha;
public:
	Shape();
	Shape(Point2D* position, char red, char green, char blue, char alpha);
	virtual void render(SDL_Renderer* render, int x, int y) = 0;
};

class Circle : public Shape
{
private:
	int radius;
public:
	Circle();
	Circle(Point2D* position, char red, char green, char blue, char alpha, int radius);
	void render(SDL_Renderer* render, int x, int y);
};

class Point2D
{
private:
	float x, y;

public:

	Point2D(int x, int y);
	Point2D();
	Point2D(const Point2D& p2d);
	float Distance(Point2D p2d);
	string toString();

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	Point2D operator+(const Point2D& p2d);
	bool operator==(const Point2D& p2d);
	Point2D& operator=(const Point2D& p2d);
};