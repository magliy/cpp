#include "header.h"

using namespace std;

Object line = Object(Point(-1, 0), Point(1, 1));
Object speed = Object(Point(0, 0), Point(0, 0));

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Object::StandardBorders() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	Point(-3, -3).Vertex();
	Point(-3, 3).Vertex();
	Point(3, 3).Vertex();
	Point(3, -3).Vertex();
	Point(-3, -3).Vertex();
	glEnd();
}

void Object::DrawLine() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(4);
	glBegin(GL_LINES);
	p1.Vertex();
	p2.Vertex();
	glEnd();
}

void Object::DrawTrace(Object& speed) {
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	p1.Vertex();
	p2.Vertex();
	(p1 - speed.p1 * 10).Vertex();
	(p2 - speed.p2 * 10).Vertex();
	glEnd();
}

void Object::CheckPosition(Object& speed) {
	if (line.p1.CompareX(Point(-3, -3)) || Point(3, 3).CompareX(line.p1) || line.p2.CompareX(Point(-3, -3)) || Point(3, 3).CompareX(line.p2)) {
		speed.ReverseX();
	}
	else if (line.p1.CompareY(Point(-3, -3)) || Point(3, 3).CompareY(line.p1) || line.p2.CompareY(Point(-3, -3)) || Point(3, 3).CompareY(line.p2)) {
		speed.ReverseY();
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	line.StandardBorders();
	line.DrawLine();
	line.DrawTrace(speed);
	line += speed;
	line.CheckPosition(speed);

	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		speed += Vector(Point(-0.001, 0), Point(-0.001, 0));
		break;
	case GLUT_KEY_DOWN:
		speed += Vector(Point(0, -0.001), Point(0, -0.001));
		break;
	case GLUT_KEY_RIGHT:
		speed += Vector(Point(0.001, 0), Point(0.001, 0));
		break;
	case GLUT_KEY_UP:
		speed += Vector(Point(0, 0.001), Point(0, 0.001));
		break;
	}
}