//creating main class 
//include header files
#include "objects.h"  

//declaring init method
void init()
{
    //set background color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //set fill color
    glColor3f(1.0, 1.0, 1.0);
    //set the color of the pixel
    glPointSize(4.0);
    //set the width of lines
    glLineWidth(2.0);
    //set the viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);
    
}

//declaring drawAxes method
void drawAxes()
{
    glBegin(GL_LINES);
    {
        //draw x in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);

        //draw y in green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);

        //draw z in blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    }
    glEnd();
}


//declaring display method
void display()
{
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //load the identity matrix
    glLoadIdentity();

    //initialize the matrix
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    //do the drawing
    drawAxes();
    for(Object *object: objects) {
        object->draw();
    }
    for(Light light: lights) {
        light.draw();
    }
    //glutSwapBuffers();
}


//main method
int main(int argc, char **argv)
{
    //create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ray Tracing");

    //initialize
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}