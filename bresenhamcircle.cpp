//**using glut**
#include <GL/glut.h>
#include <iostream>

int xl1=-10, yk=30, xl2=70, yl2=30;

const int height = 750;
const int width = 600;

void init(){
	glClearColor(1.0, 1.0, 1.0, 0.3);
	glMatrixMode(GL_PROJECTION);

	glColor3f(1.0, 0.0, 0.0);
    
}

void myLine() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 50, 0, 50);
}

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_diameter(int xl1, int xl2, int yk, int yl2, GLfloat color_d[3]) {
	//function for the drawing of the diameter of the circle using bresenham's line drawing algorithm

	int dx, dy, i, e;
	int incx, cny, cn1, cn2;
	int x,y;
	glBegin(GL_LINES);
	//glLineWidth(2.0); // Start drawing points
    glColor3fv(color_d);

	dx = xl2-xl1;
	dy = yl2-yk;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (xl2 < xl1) incx = -1;
	cny = 1;
	if (yl2 < yk) cny = -1;
	x = xl1; y = yk;
	if (dx > dy) {
		draw_pixel(x, y);
		e = 2 * dy-dx;
		cn1 = 2*(dy-dx);
		cn2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += cny;
				e += cn1;
			}
			else
				e += cn2;
			x += incx;
			draw_pixel(x, y);
		}

	} else {
		draw_pixel(x, y);
		e = 2*dx-dy;
		cn1 = 2*(dx-dy);
		cn2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += cn1;
			}
			else
				e += cn2;
			y += cny;
			draw_pixel(x, y);
		}
	}
}

// function for circle generation using Bresenham's algorithm
void bresenhamCircle(int xc, int yc, int r, GLfloat color[3]) { /**center coordinates, radius and an color array of 
    3-floating-point values representing each of the three primary colors(RGB)    **/
    int x = 0, y = r; //starting points. x initialized to zero and y to r, the radius
    int d = 3 - 2 * r; //initial decision parameter 
    glBegin(GL_TRIANGLE_STRIP); // Start drawing points
    glColor3fv(color); // Set color

    while (x <= y) {
        glVertex2i(xc + x, yc + y); //the eight octants of the cicle found from the reflection of the coordinates of first ctant
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - y, yc - x);

        if (d <= 0) { //iteration of our case when decision param is less than zero
            d = d + 4 * x + 6;
        } else { //when decision param is greater than zero
            d = d + 4 * (x - y) + 10;
            y--; 
        }
        x++;
    }

    glEnd(); // End drawing points
    glFlush(); // Flush the pipeline
}

/**
void drawAxii(){
	//GLfloat color_a[3] = {0.0f, 0.0f, 0.0f}; not used 
	//glColor3fv(color_a); not used 
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, -height/2);
	glVertex2i(0, height/2);
	
	//glEnd();

	//glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_LINES);
	glVertex2i(-width/2, 0);
	glVertex2i(width/2, 0);
	
	glEnd();

}
**/
//commented out, really not necessary as it does not work


void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Set the color to white

    glBegin(GL_LINES);
    // Draw x-axis
    glVertex2f(-200, 0);
    glVertex2f(200, 0);

    // Draw y-axis
    glVertex2f(0, -200);
    glVertex2f(0, 200);
    glEnd();
}
// function to handle drawing
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
	GLfloat color_d[3] = {0.0f, 0.0f, 0.0f};
    GLfloat color[3] = {1.0f, 0.0f, 0.0f};
	
	drawAxes();
    bresenhamCircle(30, 30, 40, color); //using  a scale of 1cm:10  
	draw_diameter(xl1, xl2, yk, yl2, color_d); // red color
	gluOrtho2D(-200, 200, -200, 200);
	
	//drawAxii();
    // Draw the circle center (30,30) points and radius 40 points
    
    //glutSwapBuffers(); //used for double buffering- the display and rendering buffers
	
	glFlush();
}

// driver code
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //double buffering enabled for smooth rendering
    glutInitWindowSize(height, width);
    glutCreateWindow("Bresenham Circle Qn1");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    gluOrtho2D(-200, 200, -200, 200); // Set the coordinate system for the display of the circle
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
