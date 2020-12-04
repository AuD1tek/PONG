#include <iostream>
#include <windowsx.h> 
#include <glut.h>
#include <time.h>
#include "settings.h"

#pragma comment (lib, "OpenGL32.lib") 
#pragma comment (lib, "Glu32.lib") 
#pragma comment (lib, "Glut32.lib")

using namespace Settings;


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        left.Up = true;
        break;
    case 'a':
        left.Down = true;
        break;
    case 'z':
        if (left.hold) {
            left.hold = false;
            ball.vx = settings.BallSpeedX;
        }
        break;
    case 'p':
        right.Up = true;
        break;
    case 'l':
        right.Down = true;
        break;
    case 'm':
        if (right.hold) {
            right.hold = false;
            ball.vx = settings.BallSpeedX;
        }
        break;
    }
}
void keyboardUp(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        left.Up = false;
        break;
    case 'a':
        left.Down = false;
        break;
    case 'p':
        right.Up = false;
        break;
    case 'l':
        right.Down = false;
        break;
    }
}
void Timer(int value)
{
    settings.win();
    settings.KeyControl();
    left.move();
    right.move();
    ball.move();
    ball.reflection();
    left.care();
    right.care();
    settings.KeyReset();
    glutPostRedisplay();
    glutTimerFunc(settings.delay, Timer, 0);
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    right.draw();
    left.draw();
    ball.draw();
    settings.DrawField();
    glEnd();
    settings.DrawScore();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    settings.start_settings();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(settings.WinWid, settings.WinHei);
    glutInitWindowPosition(settings.winXPos, settings.winYPos);
    glutCreateWindow("PONG");
    glutDisplayFunc(draw);
    glutTimerFunc(settings.delay, Timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-settings.OrthoWid, settings.OrthoWid, -settings.OrthoHei, settings.OrthoHei);
    glutMainLoop();
    return 0;
}
