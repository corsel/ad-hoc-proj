#include "ext-params.h"
#include "network-elements.h"
#include "utils.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
//#include <stdlib.h>
#include <time.h>
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const Utils::Vec2 FIELD_SIZE(50.0f, 50.0f);
const int NUM_INIT_NODES = 10;
const float WIRELESS_RANGE = 4.0f;
bool showContacts = true;
bool showRanges = false;
bool showWypts = false;
const float SCALE_FACTOR = 0.03f;

void displayFunc()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glScalef(SCALE_FACTOR * 1000 / SCREEN_WIDTH, SCALE_FACTOR * 1000 / SCREEN_HEIGHT, 1.0f);
	
	//Nodes
	NodeContainer::getInstance()->update();
	
	glPushAttrib(GL_LINE_BIT);
	glLineWidth(3);
	glEnable(GL_LINE_SMOOTH);
	
	std::vector<Node*> tempNodeVector = NodeContainer::getInstance()->getNodeVector();
	for (int i = 0; i < tempNodeVector.size(); i++)
	{
		glPushMatrix();
		glTranslatef(tempNodeVector[i]->getPosn().x, tempNodeVector[i]->getPosn().y, 0.0f);
		Utils::drawCircle(0.3f, Utils::Color(0.2f, 0.3f, 0.5f));
		
		//Wireless range circles
		if (showRanges)
			Utils::drawCircle(WIRELESS_RANGE, Utils::Color(1.0f, 0.2f, 0.2f), false, true);
		
		glPopMatrix();
	}
	glPopAttrib();
	
	//Field limits
	glPushAttrib(GL_LINE_BIT);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.1f, 0.1f);
	glVertex2f(-(int)FIELD_SIZE.x / 2.0f, -(int)FIELD_SIZE.y / 2.0f);
	glVertex2f((int)FIELD_SIZE.x / 2.0f, -(int)FIELD_SIZE.y / 2.0f);
	glVertex2f((int)FIELD_SIZE.x / 2.0f, (int)FIELD_SIZE.y / 2.0f);
	glVertex2f(-(int)FIELD_SIZE.x / 2.0f, (int)FIELD_SIZE.y / 2.0f);
	glVertex2f(-(int)FIELD_SIZE.x / 2.0f, -(int)FIELD_SIZE.y / 2.0f);
	glEnd();
	glPopAttrib();
	glPopMatrix();
	
	NodeContainer::getInstance()->update();
	
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutDisplayFunc(displayFunc);
	glutIdleFunc(displayFunc);
	
	NodeContainer::getInstance()->init(NUM_INIT_NODES);
	
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("manet sim");
	
	glutMainLoop();
	std::cout << "fin.\n";
	return 0;
}

