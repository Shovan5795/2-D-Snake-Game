#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include <bits/stdc++.h>
#include "RGBpixmap.cpp"

#define COLUMNS 40
#define ROWS 40

using namespace std;

bool gameOver = false;
extern short sDirection;
extern int fps;

RGBpixmap pix[6];

void timer_callback(int);
void display_callback();
void reshape_callback(int, int);
void keyboard_callback(int, int, int);

int score = 0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    initGrid(COLUMNS, ROWS);
    glEnable(GL_TEXTURE_2D);

    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("D:\\4-2 works\\CG Lab\\CG project\\jack.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("D:\\4-2 works\\CG Lab\\CG project\\snake.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("D:\\4-2 works\\CG Lab\\CG project\\apple.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("D:\\4-2 works\\CG Lab\\CG project\\meta.bmp");
	pix[4].setTexture(5);

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snake Game");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;


}

void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D,5);
	glEnable(GL_TEXTURE_2D);
    drawGrid();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
    drawSnake();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,4);
	glEnable(GL_TEXTURE_2D);
    drawFood();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
    if(score==MAX){
        gameOver = true;
        cout<<"Congratulations! You have completed your level."<<endl;
        cout<<"Your Score: "<<score;
        exit(0);

    }
    if(gameOver)
    {
        cout<<"WOOPS!! Game Over!! :("<<endl;
        cout<<"Your Score: "<<score;
        exit(0);
    }
}

void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/fps, timer_callback, 0);

}

void keyboard_callback(int key, int, int)
{

    switch(key)
    {

    case GLUT_KEY_UP:
        if(sDirection!= DOWN)
            sDirection = UP;
        break;

    case GLUT_KEY_DOWN:
        if(sDirection!= UP)
            sDirection = DOWN;
        break;

    case GLUT_KEY_RIGHT:
        if(sDirection!= LEFT)
            sDirection = RIGHT;
        break;

    case GLUT_KEY_LEFT:
        if(sDirection!= RIGHT)
            sDirection = LEFT;
        break;

    }

}

