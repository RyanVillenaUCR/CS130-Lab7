// Name:            Ryan Villena
// Quarter, Year:   Winter 2019
// Lab:             7
// Assignment pulled from here:
// https://www.cs.ucr.edu/~shinar/courses/cs130/content/lab-07-bezier-files.zip
// https://www.cs.ucr.edu/~shinar/courses/cs130/content/Lab7-Bezier-Curve.pdf
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>
#include <cassert>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

std::vector<vec2> ctrl_pts;



unsigned int factorial(int n) {

    assert(n >= 0);

    if (n <= 1)
        return 1;

    unsigned int result = 1;

    for (unsigned int i = 1; i <= static_cast<unsigned int>(n); i++)
        result *= i;

    return result;
}

float combination(int n, int k) {

    assert(n >= k);

    return factorial(n) / (factorial(n - k) * factorial(k));
}

float binomial(int n, int k, float t) {

    // float result = 0;

    // for (int i = 0; i <= k; i++)
    //     result += combination(n - 1, i) * pow(t, i) * pow(1 - t, n - 1 - i);

    // return result;

    return combination(n - 1, k) * pow(t, k) * pow(1 - t, n - 1 - k);
}



void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();


    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f,0.0f,0.0f);


    if (ctrl_pts.size() >= 2) {

        for (float i = 0.01; i <= 1.0; i += 0.01) {

            vec2 graphMe;

            for (size_t j = 0; j < ctrl_pts.size(); j++) {

                graphMe += binomial(ctrl_pts.size(), j, i) * ctrl_pts[j];
            }

            glVertex2f(graphMe[0], graphMe[1]);

        }
    }

    // glBegin(GL_LINES);
    // just for example, remove if desired

    // glColor3f(1.0f,0.0f,0.0f);
    // glVertex2f(-.5f,-.5f);
    // glVertex2f(.5f,-.5f);
    // glVertex2f(.5f,.5f);
    // glVertex2f(-.5f,.5f);
    // glEnd();
    // glFlush();





    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);

        vec2 point;
        point[0] = static_cast<float> (px);
        point[1] = static_cast<float> (py);
        ctrl_pts.push_back(point);

        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - RyanVillenaUCR");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
