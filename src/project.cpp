#include "ext-params.h"
#include "network-elements.h"
#include "utils.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const Utils::Vec2 FIELD_SIZE(15.0f, 15.0f);
const int NUM_INIT_NODES = 9;
bool showAnnotations = true;
float scaleFactor = 0.1f;

void displayFunc()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glScalef(scaleFactor * 1000 / SCREEN_WIDTH, scaleFactor * 1000 / SCREEN_HEIGHT, 1.0f);
	
	//Nodes
	for (int i = 0; i < nodeVector.size(); i++)
		nodeVector[i].updateMovement();
	glPushAttrib(GL_LINE_BIT);
	glLineWidth(3);
	glEnable(GL_LINE_SMOOTH);
	for (int i = 0; i < nodeVector.size(); i++)
	{
		nodeVector[i].updateContacts();
		glPushMatrix();
		glTranslatef(nodeVector[i].getPosn().x, nodeVector[i].getPosn().y, 0.0f);
		Utils::drawCircle(0.3f, Utils::Color(0.2f, 0.3f, 0.5f));
		
		//Wireless range circles
		if (showAnnotations)
			Utils::drawCircle(WIRELESS_RANGE, Utils::Color(1.0f, 0.0f, 0.0f), false, true);
		
		glPopMatrix();
	}
	glPopAttrib();
	
	if (showAnnotations)
	{
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
		
		//Contacts
		for (int i = 0; i < nodeVector.size(); i++)
		{
			nodeVector[i].renderContacts();
		}
	}
	glutSwapBuffers();
}

void init()
{
	srand(time(NULL));
	Utils::Vec2 tempVec2;
	Node tempNode;
	for (int i = 0; i < NUM_INIT_NODES; i++)
	{
		tempVec2 = Utils::Vec2(rand() % (int)(int)FIELD_SIZE.x - (int)FIELD_SIZE.x / 2.0f, rand() % (int)(int)FIELD_SIZE.y - (int)FIELD_SIZE.y / 2.0f);
		tempNode = Node(tempVec2, 2.0f);
		nodeVector.push_back(tempNode);
	}
}
 
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutDisplayFunc(displayFunc);
	glutIdleFunc(displayFunc);
	
	init();
	
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("manet sim");
	
	glutMainLoop();
	std::cout << "fin.\n";
	return 0;
}

