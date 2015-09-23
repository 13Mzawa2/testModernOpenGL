#pragma comment(linker, "/SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("Hellow OpenGL World !!");

	cout << "Vendor :" << glGetString(GL_VENDOR) << '\n';
	cout << "GPU : " << glGetString(GL_RENDERER) << '\n';
	cout << "OpenGL ver. " << glGetString(GL_VERSION) << '\n';
	cout << "yŠg’£‹@”\ˆê——z" << endl;
	cout << glGetString(GL_EXTENSIONS) << endl;

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}