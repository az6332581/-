#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "glut.h"
#include <time.h>



typedef enum {
    RESERVED, BODY_SIDE, BODY_EDGE, BODY_WHOLE, ARM_SIDE, ARM_EDGE, ARM_WHOLE,
    LEG_SIDE, LEG_EDGE, LEG_WHOLE, EYE_SIDE, EYE_EDGE, EYE_WHOLE
} displayLists;

GLfloat angle = 45;   
GLfloat angle2 = 45;
GLboolean doubleBuffer = GL_TRUE, iconic = GL_FALSE, keepAspect = GL_FALSE;
int moving, startx, starty;
int W = 1280, H = 1280;
int useStencil = 0; 

int peopel_x = 21;
int peopel_y = -3;
GLdouble bodyWidth = 3.0;
float jump = 0.0;

int angle_people = 0;
int pep_agl = -45;

int people_position_x = 0;
int people_position_y = 0;

int weapon_position = -15.0;
int weapon_people_position = -150;
bool weapon_on = false;
int people_on_agl = -45;

int kill_agl = 0;

int Rotated1 = 1;
int Rotated2 = 0;

GLfloat body[][2] = { {0, 3}, {1, 1}, {5, 1}, {8, 4}, {10, 4}, {11, 5},
  {11, 11.5}, {13, 12}, {13, 13}, {10, 13.5}, {13, 14}, {13, 15}, {11, 16},
  {8, 16}, {7, 15}, {7, 13}, {8, 12}, {7, 11}, {6, 6}, {4, 3}, {3, 2},
  {1, 2} };
GLfloat arm[][2] = { {8, 10}, {9, 9}, {10, 9}, {13, 8}, {14, 9}, {16, 9},
  {15, 9.5}, {16, 10}, {15, 10}, {15.5, 11}, {14.5, 10}, {14, 11}, {14, 10},
  {13, 9}, {11, 11}, {9, 11} };
GLfloat leg[][2] = { {8, 6}, {8, 4}, {9, 3}, {9, 2}, {8, 1}, {8, 0.5}, {9, 0},
  {12, 0}, {10, 1}, {10, 2}, {12, 4}, {11, 6}, {10, 7}, {9, 7} };
GLfloat eye[][2] = { {8.75, 15}, {9, 14.7}, {9.6, 14.7}, {10.1, 15},
  {9.6, 15.25}, {9, 15.25} };


GLfloat lightZeroPosition[] = { 10.0, 14.0, 10.0, 1.0 };
//GLfloat lightZeroPosition[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightZeroColor[] = { 0.8, 1.0, 0.8, 1.0 }; /* green */
GLfloat lightOnePosition[] = { -1.0, 1.0, 1.0, 0.0 };
GLfloat lightOneColor[] = { 0.6, 0.3, 0.2, 1.0 }; /* red */

GLfloat skinColor[] = { 0.1, 1.0, 0.1, 1.0 }, eyeColor[] = { 1.0, 0.2, 0.2, 1.0 };

GLfloat weaponColor[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat floorColor[] = { 1.0, 0.0, 0.0, 1.0 };

GLfloat peopleColor[] = { 0.75, 0.75, 0.75, 1.0 };

GLfloat treeColor1[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat treeColor2[] = { 1.0, .87, 0.67, 1.0 };
void tree(void)
{
    glPushMatrix();
    glScalef(0.2, 0.2, 0.15);
    glTranslatef(120, -60, -450);
    glTranslatef(60, 70, 400);
    glutSolidSphere(25.0, 20, 20);
    glTranslatef(20, 0, 0);
    glutSolidSphere(25.0, 20, 20);
    glTranslatef(-10, 0, -10);
    glutSolidSphere(25.0, 20, 20);
    glTranslatef(0, 0, 20);
    glutSolidSphere(25.0, 20, 20);  
    glTranslatef(0, 10, -10);
    glutSolidSphere(25.0, 20, 20);  
    glPopMatrix();
}

void draw_tree() {
    glPushMatrix();
    tree();
    glPopMatrix();
}

void draw_weapon_TRIANGLES() {
    glBegin(GL_TRIANGLES);          
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();
}

void people(void)
{
    glutSolidCube(2);

    //glColor3f(1.0,1.0,1.0);
    glPushMatrix();            
    glTranslatef(0, 1.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    //glColor3f(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(-0.2, 1.75, 0.52);
    glVertex3f(-0.3, 1.75, 0.52);
    glVertex3f(0.2, 1.75, 0.52);
    glVertex3f(0.3, 1.75, 0.52);
    glVertex3f(0.1, 1.25, 0.52);
    glVertex3f(-0.1, 1.25, 0.52);
    glEnd();
    glLineWidth(1);

    //glColor3f(0,0,1.0);
    glPushMatrix();           
    glTranslatef(-0.7, -2.25, 0);
    glScalef(0.5, 2.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7, -2.25, 0);
    glScalef(0.5, 2.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.25, 0);

    glPushMatrix();
    glTranslatef(-1.25, 0, 0);
    glScalef(1, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotated(people_on_agl, 1, 0, 0);
    glTranslatef(-1.75, -0.75, 0);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.25, 0, 0);
    glScalef(1, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotated(-1 * pep_agl, 1, 0, 0);
    glTranslatef(1.75, -0.75, 0);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glRotated(-1 * pep_agl, 1, 0, 0);
    glTranslatef(1.75, -0.75, 0);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    

    glMaterialfv(GL_FRONT, GL_DIFFUSE, weaponColor);
    //劍
    glPushMatrix();
    glTranslatef(weapon_people_position, 0.25, 1.75);
    glRotated(45, 1, 0, 0);
    glScalef(1.0, 1.0, 3.0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(weapon_people_position, -0.5, 1.0);
    glRotated(45, 1, 0, 0);
    glScalef(.5, 1.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(weapon_people_position, 2.25, 3.75);
    glRotated(45, 1, 0, 0);
    glScalef(1.0, 5.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(weapon_people_position, 4.25, 5.75);
    glRotated(45, 1, 0, 0);
    glScalef(0.5, 0.5, 0.5);
    draw_weapon_TRIANGLES();
    glPopMatrix();


    glPopMatrix();
}

void draw_people(void) {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, peopleColor);
    glTranslatef(peopel_x, -3.5, peopel_y);
    glRotated(180, 0, 0, 1);
    glRotated(angle_people, 0, 1, 0);
    people();
    glPopMatrix();
}

void weapon(void) {

    //glColor3f(1.0, 0, 0);
    glPushMatrix();
    glTranslatef(0, 1.5, 2);
    glScalef(3.0, 1.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.5, 2);
    glScalef(.5, 1.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 4.5, 2.0);
    glScalef(1.0, 5.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 7.5, 2.0);
    glScalef(0.5, 0.5, 0.5);
    draw_weapon_TRIANGLES();
    glPopMatrix();
}

void draw_weapon(void) {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, weaponColor);    
    glRotated(180, 0, 0, 1);
    glTranslatef(weapon_position, 0.0, 19.0);
    weapon();
    glPopMatrix();
}

void extrudeSolidFromPolygon(GLfloat data[][2], unsigned int dataSize,
    GLdouble thickness, GLuint side, GLuint edge, GLuint whole)
{
    static GLUtriangulatorObj* tobj = NULL;
    GLdouble vertex[3], dx, dy, len;
    int i;
    int count = dataSize / (int)(2 * sizeof(GLfloat));

    if (tobj == NULL) {
        tobj = gluNewTess();
        gluTessCallback(tobj, GLU_END, glEnd);
    }
    glNewList(side, GL_COMPILE);
    glShadeModel(GL_SMOOTH);
    gluBeginPolygon(tobj);
    for (i = 0; i < count; i++) {
        vertex[0] = data[i][0];
        vertex[1] = data[i][1];
        vertex[2] = 0;
        gluTessVertex(tobj, vertex, data[i]);
    }
    gluEndPolygon(tobj);
    glEndList();
    glNewList(edge, GL_COMPILE);
    glShadeModel(GL_FLAT);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= count; i++) {
        glVertex3f(data[i % count][0], data[i % count][1], 0.0);
        glVertex3f(data[i % count][0], data[i % count][1], thickness);
        dx = data[(i + 1) % count][1] - data[i % count][1];
        dy = data[i % count][0] - data[(i + 1) % count][0];
        len = sqrt(dx * dx + dy * dy);
        glNormal3f(dx / len, dy / len, 0.0);
    }
    glEnd();
    glEndList();
    glNewList(whole, GL_COMPILE);
    glFrontFace(GL_CW);
    glCallList(edge);
    glNormal3f(0.0, 0.0, -1.0); 
    glCallList(side);
    glPushMatrix();
    glTranslatef(0.0, 0.0, thickness);
    glFrontFace(GL_CCW);
    glNormal3f(0.0, 0.0, 1.0); 
    glCallList(side);
    glPopMatrix();
    glEndList();
}

void makeDinosaur(void)
{
    extrudeSolidFromPolygon(body, sizeof(body), bodyWidth,
        BODY_SIDE, BODY_EDGE, BODY_WHOLE);
    extrudeSolidFromPolygon(arm, sizeof(arm), bodyWidth / 4,
        ARM_SIDE, ARM_EDGE, ARM_WHOLE);
    extrudeSolidFromPolygon(leg, sizeof(leg), bodyWidth / 2,
        LEG_SIDE, LEG_EDGE, LEG_WHOLE);
    extrudeSolidFromPolygon(eye, sizeof(eye), bodyWidth + 0.2,
        EYE_SIDE, EYE_EDGE, EYE_WHOLE);
}

void drawDinosaur(void)
{
    glPushMatrix();
    //glTranslatef(0.0, jump, 0.0);
    glRotated(kill_agl, Rotated1, 0, Rotated2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor);
    glCallList(BODY_WHOLE);
    glPushMatrix();
    glTranslatef(0.0, 0.0, bodyWidth);
    glCallList(ARM_WHOLE);
    glCallList(LEG_WHOLE);
    glTranslatef(0.0, 0.0, -bodyWidth - bodyWidth / 4);
    glCallList(ARM_WHOLE);
    glTranslatef(0.0, 0.0, -bodyWidth / 4);
    glCallList(LEG_WHOLE);
    glTranslatef(0.0, 0.0, bodyWidth / 2 - 0.1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeColor);
    glCallList(EYE_WHOLE);
    glPopMatrix();
    glPopMatrix();
}

void drawFloor(void)
{
    glPushMatrix();
    //glDisable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floorColor);
    glBegin(GL_QUADS);
    glVertex3f(-13.0, 0.0, 27.0);
    glVertex3f(32.0, 0.0, 27.0);
    glVertex3f(32.0, 0.0, -18.0);
    glVertex3f(-13.0, 0.0, -18.0);
    glEnd();
    //glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, treeColor1);
    glTranslatef(-10.0, 7, -9.0);
    draw_tree();
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, treeColor2);
    glScalef(1, 3.5, 1);
    glTranslatef(28.0, 1.0, -15.0);
    glutSolidCube(2);
    glPopMatrix();
}


void redraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    glTranslatef(-8, -8, -bodyWidth / 2);

    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);

    if (useStencil) {

        glDisable(GL_DEPTH_TEST);

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

        drawFloor();

        glEnable(GL_DEPTH_TEST);

        glStencilFunc(GL_EQUAL, 1, 0xffffffff);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    }

    glPushMatrix();

    glScalef(1.0, -1.0, 1.0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);

    glEnable(GL_NORMALIZE);
    glCullFace(GL_FRONT);

    drawDinosaur();
    
    draw_people();
    
    draw_weapon();


    glDisable(GL_NORMALIZE);
    glCullFace(GL_BACK);

    glPopMatrix();

    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);


    if (useStencil) {
        glDisable(GL_STENCIL_TEST);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glColor4f(0.7, 0.0, 0.0, 0.3);
    drawFloor();
    glDisable(GL_BLEND);

    glFrontFace(GL_CW);
    //glColor4f(0.1, 0.1, 0.7, 1.0);
    drawFloor();
    glFrontFace(GL_CCW);

    drawDinosaur();

    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        moving = 1;
        startx = x;
        starty = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        moving = 0;
    }
}

void kill_agl_add(int x) {
    
    if (x == 1) {
        Rotated1 = 1;
        Rotated2 = 0;
        if (kill_agl == 90) {
            kill_agl = 90;
        }
        else
        {
            kill_agl += 45;
        }
    }
    if (x == 2) {
        Rotated1 = 0;
        Rotated2 = 1;
        if (kill_agl == 90) {
            kill_agl = 90;
        }
        else
        {
            kill_agl -= 22.5;
        }
    }
}



void keyboard(unsigned char key,int x, int y)
{
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
    if (key == 'w' || key == 'W') {
        if (angle_people == 0) { 
            peopel_y++; 
            people_position_y += 1;
        }
        if (angle_people == 90) { 
            peopel_x--;
            people_position_x -= 1;
        }
        if (angle_people == 180) { 
            peopel_y--;
            people_position_y -= 1;
        }
        if (angle_people == 270) { 
            peopel_x++; 
            people_position_x += 1;
        }
        if (angle_people == -90) { 
            peopel_x++; 
            people_position_x += 1;
        }
        if (angle_people == -180) { 
            peopel_y--; 
            people_position_y -= 1;
        }
        if (angle_people == -270) { 
            peopel_x--; 
            people_position_x -= 1;
        }
        printf("x = %d", people_position_x);
        printf("y = %d", people_position_y);
        if (weapon_on == true) {
            people_on_agl = -45;
        }
        else if (weapon_on == false) {
            people_on_agl = people_on_agl * -1;
        }
        
        pep_agl = pep_agl * -1;
    }
    /*if (key == 's' || key == 'S') {
        if (angle_people == 0) { peopel_y--; }
        if (angle_people == -90) { peopel_x++; }
        if (angle_people == -180) { peopel_y++; }
        if (angle_people == -270) { peopel_x--; }
        if (angle_people == 90) { peopel_x--; }
        if (angle_people == 180) { peopel_y++; }
        if (angle_people == 270) { peopel_x++; }
        pep_agl = pep_agl * -1;
    }*/
    if (key == 'a' || key == 'A') {
        if (angle_people <= -270) {
            angle_people = 0;
        }
        else
        {
            angle_people -= 90;
        }
    }
    if (key == 'd' || key == 'D') {
        if (angle_people >= 270) {
            angle_people = 0;
        }
        else
        {
            angle_people += 90;
        }
    }
    if (key == 'r' || key == 'R') {
        if (people_position_x == -4 && people_position_y == 24) {
            weapon_position = 90;
            weapon_people_position = -2;
            weapon_on = true;
        }
        if (people_position_x == -9 && people_position_y == 24) {
            weapon_position = 90;
            weapon_people_position = -2;
            weapon_on = true;
        }
        if (people_position_x == -6 && people_position_y == 26) {
            weapon_position = 90;
            weapon_people_position = -2;
            weapon_on = true;
        }
        if (people_position_x == -6 && people_position_y == 22) {
            weapon_position = 90;
            weapon_people_position = -2;
            weapon_on = true;
        }
    }
    if (key == 'f' || key == 'F') {
        if (people_position_x == -4 && weapon_on == true) {
            if (people_position_y <= 5 && people_position_y >= 2) {
                if (angle_people == 90 || angle_people == -270) {
                    kill_agl_add(1);
                }              
            }
        }
        if (people_position_y == 13 && weapon_on == true) {
            if (people_position_x >= -11 && people_position_x <= -8) {
                if (angle_people == 180 || angle_people == -180) {
                    kill_agl_add(2);
                }
            }
        }
        if (people_position_y == -4 && weapon_on == true) {
            if (people_position_x >= -15 && people_position_x <= -12) {
                if (angle_people == 0) {
                    kill_agl_add(1);
                }
            }
        }
    }
    printf("angle_people = %d", angle_people);
}


void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

GLboolean lightZeroSwitch = GL_TRUE, lightOneSwitch = GL_TRUE;

void controlLights(int value)
{
    switch (value) {
    case 1:
        lightZeroSwitch = !lightZeroSwitch;
        if (lightZeroSwitch) {
            glEnable(GL_LIGHT0);
        }
        else {
            glDisable(GL_LIGHT0);
        }
        break;
    case 2:
        lightOneSwitch = !lightOneSwitch;
        if (lightOneSwitch) {
            glEnable(GL_LIGHT1);
        }
        else {
            glDisable(GL_LIGHT1);
        }
        break;
    case 3:
        useStencil = 1 - useStencil;
        break;
    }
    glutPostRedisplay();
}

void idle(void)
{
    static float time;

    time = glutGet(GLUT_ELAPSED_TIME) / 500.0;

    jump = 3.0 * fabs(sin(time));
    glutPostRedisplay();
}

void visible(int vis)
{
    if (vis == GLUT_VISIBLE)
        glutIdleFunc(idle);
    else
        glutIdleFunc(NULL);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Leapin' Lizards");
    glutDisplayFunc(redraw);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutVisibilityFunc(visible);

    /*glutCreateMenu(controlLights);
    glutAddMenuEntry("Toggle right light", 1);
    glutAddMenuEntry("Toggle left light", 2);
    glutAddMenuEntry("Toggle stenciling out reflection artifacts", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);*/

    makeDinosaur();
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0,1.0,1.0,80.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, -20.0, 50.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.);


    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);

    /*const GLfloat glfLightAmbient1[4] = { 0.1, 0.1, 0.1, 1.0 };
    const GLfloat glfLightAmbient2[4] = { 0.4, 0.4, 0.4, 1.0 };
    const GLfloat glfLightDiffuse1[4] = { 0, 0.8, 0.8, 1.0 };
    const GLfloat glfLightDiffuse2[4] = { 0.8, 0.8, 0.8, 1.0 };
    const GLfloat glfLightSpecular1[4] = { 0, 0.8, 0.8, 1.0 };
    const GLfloat glfLightSpecular2[4] = { 0.8, 0.8, 0.8, 1.0 };
    const GLfloat glPosition1[4] = { 0,0,1,0 };
    const GLfloat glPosition2[4] = { 0.6,0.6,-0.6,1 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, glfLightAmbient1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glfLightDiffuse1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, glfLightSpecular1);
    glLightfv(GL_LIGHT0, GL_POSITION, glPosition1);*/
    /*glLightfv(GL_LIGHT1, GL_AMBIENT, glfLightAmbient2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, glfLightDiffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, glfLightSpecular2);*/


    glutMainLoop();
    return 0;
}