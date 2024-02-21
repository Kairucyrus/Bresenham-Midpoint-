#include <GL/glut.h>
#include <cmath>

const int cx = 500;
const int cy = 500;
//Bresenham's ellipse drawing algorithm
void drawEllipse(int a, int b, GLfloat color[3]) {
    glBegin(GL_TRIANGLE_STRIP); //drawing the ellipse in fill color
    int x = 0, y = b;
    float d1 = b * b - a * a * b + 0.25 * a * a;
    float dx = 2 * b * b * x;
    float dy = 2 * a * a * y;
    while (dx < dy) {
        glVertex2f(x, y);
        glVertex2f(-x, y);
        glVertex2f(x, -y);
        glVertex2f(-x, -y);
        if (d1 < 0) {
            x++;
            dx = dx + 2 * b * b;
            d1 = d1 + dx + b * b;
        } else {
            x++;
            y--;
            dx = dx + 2 * b * b;
            dy = dy - 2 * a * a;
            d1 = d1 + dx - dy + b * b;
        }
    }
    float d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y >= 0) {
        glVertex2f(x, y);
        glVertex2f(-x, y);
        glVertex2f(x, -y);
        glVertex2f(-x, -y);
        if (d2 > 0) {
            y--;
            dy = dy - 2 * a * a;
            d2 = d2 + a * a - dy;
        } else {
            y--;
            x++;
            dx = dx + 2 * b * b;
            dy = dy - 2 * a * a;
            d2 = d2 + dx - dy + a * a;
        }
    }
    glEnd();
}
void drawAxes() {
    glColor3f(0.0, 1.0, 0.0); // Set the color to white

    glBegin(GL_LINES);
    // Draw x-axis
    glVertex2f(-500, 0);
    glVertex2f(500, 0);

    // Draw y-axis
    glVertex2f(0, -500);
    glVertex2f(0, 500);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(0.0, 1.0, 0.0); // Set color to red
    drawAxes();
    GLfloat color[3] = {0.0f, 1.0f, 0.0f};

    drawEllipse(80, 60, color); // Major axis of 80 and minor axis of 60
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(cx, cy);
    glutCreateWindow("Bresenham's Ellipse QN 2");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-cx/2, cy/2, -cy/2, cx/2);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
