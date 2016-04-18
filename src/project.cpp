#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>

void displayFunc()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Utils::drawCircle(0.2f, Color(1.0f, 0.0f, 0.0f));
	
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutDisplayFunc(displayFunc);
	glutIdleFunc(displayFunc);
	
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("test");
	glutMainLoop();
	std::cout << "fin.\n";
	return 0;
}
