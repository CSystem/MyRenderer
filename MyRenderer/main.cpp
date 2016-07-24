#include "MyRender.h"

MyRender *myrClass;

using namespace std;

void Display()
{
 	glClear(GL_COLOR_BUFFER_BIT);
 	gluOrtho2D(0,960,0,640);
 	//myrClass->DrawLine(1,500,1000,500);
	//myrClass->DrawLine(500,5,500,1000);
	myrClass->DrawCircle(100,500,500);
	//myrClass->DrawCircleAndFill(100, 500, 500);
	myrClass->DrawPolygon(0, 0);
	//myrClass->FloodFillAlgorithm(500,500, Color(1,0,0), Color(1,1,1));
	myrClass->ScanLineFillAlgorithm(450,450, Color(1,1,1),Color(1,0,0));
	glutSwapBuffers();

// 	glBegin(GL_TRIANGLES);
// 	glVertex2f(1,2);
// 	glVertex2f(1,3);
// 	glVertex2f(3,4);
// 	glEnd();
// 	glutSwapBuffers();
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	gluOrtho2D(0,960,0,640);
// 	glBegin(GL_POINTS);
// 	glVertex2f(100,100);
// 	glEnd();
// 
// 	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(500,20);
	glutInitWindowSize(960,640);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(&Display);

	myrClass = new MyRender();
	glutMainLoop();
	return 0;
}