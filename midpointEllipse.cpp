#include <GL/glut.h>
#include <iostream>

const int xl=500;
const int yl = 500;
const int width =500;// window width
const int height = 400; //window height

void ellipseMidpoint(int rx, int ry, int xc, int yc, GLfloat color[3]) {
    
    
    float dx, dy, d1, d2, x, y;
    x=0;
    y = ry;

    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;
    //has two regions 1 and 2 with different gradients in evry quadrant
    while (dx < dy) {
        glVertex2i(x + xc, y + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(x + xc, -y + yc);
        glVertex2i(-x + xc, -y + yc);

        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        } else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    while (y >= 0) {
        glVertex2i(x + xc, y + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(x + xc, -y + yc);
        glVertex2i(-x + xc, -y + yc);

        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        } else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

/**
void drawAxii(){
	//GLfloat color_a[3] = {0.0f, 0.0f, 0.0f}; not used 
	//glColor3fv(color_a); not used 
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, -height/2);
	glVertex2i(0, height/2);
	glVertex2i(-width/2, 0);
	glVertex2i(width/2, 0);
	
	glEnd();

}
**/


void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer bit to use our defined color
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    GLfloat color[3] = {0.0f, 1.0f, 0.0f};
    
    ellipseMidpoint(80, 60, 0, 0, color);
    
    /*** 1 cm represented by 10 units in drawing so 
    //that our ellipse is centered at (0,0) and has major radius of 8cm(80 units and minor radius of 6cm (60units))
    **/
    glEnd(); //here we end the drawing of the ellipse(points)
    glFlush(); //flush the pipeline
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, RGB colorspace
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoin-ellipse Drawing, Question2");

    gluOrtho2D(-xl/2, yl/2, -yl/2, xl/2);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}