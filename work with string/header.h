#pragma once

#include "glut-3.7/include/GL/glut.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

class Point {
private:
	float x;
	float y;

public:
	Point() { x = 0, y = 0; };
	Point(float x1, float y1) { x = x1, y = y1; };

	void ReverseX() { 
		x = -x; 
	};
	void ReverseY() { 
		y = -y; 
	};

    int CompareX(Point p) {
		if (x <= p.x)
			return 1;
		else return 0;
	}

	int CompareY(Point p) {
		if (y <= p.y)
			return 1;
		else return 0;
	}

	void Vertex() {
		glVertex2d(x, y);
	}

	Point& operator += (Point& p) {
		x += p.x;
		y += p.y;
		return *this;
	}

	Point operator - (Point p) {
		return (Point(x - p.x, y - p.y));
	}

	Point operator * (int num) {
		return Point(x * num, y * num);
	}

	Point operator - () {
		return (Point(-x, -y));
	}

	Point operator + (Point& p) {
		return (Point(x + p.x, y + p.y));
	}
};


class Vector {
protected:
	Point p1;
	Point p2;

public:
	Vector(Point a, Point b) { p1 = a, p2 = b; };

	void ReverseX() {
		p1.ReverseX();
		p2.ReverseX();
	}

	void ReverseY() {
		p1.ReverseY();
		p2.ReverseY();
	}

	int CheckX(Point& p) {
		if (p1.CompareX(p) || p2.CompareX(p))
			return 1;
		else return 0;
	}

	int CheckY(Point& p) {
		if (p1.CompareY(p) || p2.CompareY(p))
			return 1;
		else return 0;
	}

	Vector& operator += (Vector v) {
		p1 += v.p1;
		p2 += v.p2;
		return *this;
	}

	Vector& operator = (Vector v) {
		p1 = v.p1;
		p2 = v.p2;
		return *this;
	}

	const Vector operator - (Vector v) {
		return(Vector(p1 - v.p1, p2 - v.p2));
	}

	const Vector operator - () {
		return(Vector(-p1, -p2));
	}

	const Vector operator + (Vector v) {
		return(Vector(p1 + v.p1, p2 + v.p2));
	}
};


class Object : public Vector {
public:
	Object(Point a, Point b) : Vector(a, b) {};

	void StandardBorders();
	void DrawLine();
	void DrawTrace(Object& speed);
	void CheckPosition(Object& speed);
};

void renderScene();
void changeSize(int w, int h); 
void processNormalKeys(unsigned char key, int x, int y); 
void processSpecialKeys(int key, int x, int y); 