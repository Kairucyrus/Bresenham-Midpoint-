#include <iostream>
#include <GL/glut.h>

const int lx = 500; //defining the dimensions of the window sizes
const int ly = 500;
void midpoint(int x1, int y1, int r, GLfloat color[3]) { //function for the drawing of the circle
    void circle(int, int, int, int); // method that takes three parameters: the starting points (x,y) and the radius

    int x = 0, y = r, p = 1 - r; //decision parameters p is calculated using the formula 1-r, where r is the radius

    while (x <= y) { //increment the value of x until the point where the x-value exceeds the y-value(the interchange point)
        x++;
        if (p < 0) //
            p = p + 2 * x + 1; 
        else {
            y--;
            p = p + 2 * x + 1 - 2 * y;
        }
        circle(x1, y1, x, y);
    }
}

void circle(int x1, int y1, int x, int y) {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(x1 + x, y1 + y); //vertices for the eight octants of the circle obtained through mirroring.
    glVertex2i(x1 + y, y1 + x);
    glVertex2i(x1 - y, y1 + x);
    glVertex2i(x1 - x, y1 + y);
    glVertex2i(x1 - x, y1 - y);
    glVertex2i(x1 - y, y1 - x);
    glVertex2i(x1 + y, y1 - x);
    glVertex2i(x1 + x, y1 - y);
    glEnd();
}

void drawDiameter(int kx1, int ky1, int kx2, int ky2, GLfloat color_d[3]) {

    //midpoint line drawing algorithm for the diameter
    //GLfloat color_d[3] = {0.0f, 0.0f, 0.0f};//color for the diameter(black)
    int dx = kx2 - kx1;
    int dy = ky2 - ky1;
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = kx1, y = ky1;

    glBegin(GL_LINES);
    

    glVertex2i(x, y);
    while (x < kx2) {
        if (d <= 0) {
            d += incrE;
            x++;
        } else {
            d += incrNE;
            x++;
            y++;
        }
        glVertex2i(x, y);
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat color_d[3] = {0.0f, 0.0f, 0.0f};
    GLfloat color[3] = {1.0f, 0.0f, 0.0f};
    drawDiameter(-10, 30, 70,30, color_d);
    glColor3f(1.0, 0.0, 0.0); // Setting color to red
    
    midpoint(30, 30, 40, color); //1cm:10 units. Use of actual dimensions leads to 
    //drawing of a small circle even after altering the gluOrtho2D()
    glFlush(); //flush the pipeline after the drawing
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(lx, ly);
    glutCreateWindow("Midpoint Circle Qn 1");
    glClearColor(1.0, 1.0, 1.0, 1.0); // black is the background color of the window
    gluOrtho2D(-lx/4, ly/4, -ly/4, lx/4);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
