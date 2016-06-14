#include "ext-params.h"
#include "network-elements.h"
#include "utils.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const Utils::Vec2 FIELD_SIZE(50.0f, 50.0f);
const int NUM_INIT_NODES = 15;
const float WIRELESS_RANGE = 6.0f;
bool showContacts = true;
bool showRanges = true;
bool showWypts = true;
bool showPackets = true;
const float SCALE_FACTOR = 0.03f;
long int globalFrame = 0;

void displayFunc()
{
	globalFrame++;
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
		//glPushMatrix();
		tempNodeVector[i]->updateBuffer();
		//glPopMatrix();
		Utils::drawCircle(0.5f, Utils::Color(0.2f, 0.4f, 0.6f));
		
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

