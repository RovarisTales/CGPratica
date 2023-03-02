#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha = M_PI/4, beta = M_PI/4,raio= sqrt(50);
float radius = 1, height = 2;
int slices = 10;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {
	float ang = 0;

	for(int i = 0; i!= slices; i++){
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f, height/2, 0.0f);
		glVertex3f(sin(ang)*radius, height/2, cos(ang)*radius);
		glVertex3f(sin(ang+(M_PI*2/slices))*radius, height/2, cos(ang+(M_PI*2/slices))*radius);
		glEnd();

		glBegin(GL_TRIANGLES);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(sin(ang)*radius, height/2, cos(ang)*radius);
		glVertex3f(sin(ang)*radius, -height/2, cos(ang)*radius);
		glVertex3f(sin(ang+(M_PI*2/slices))*radius, height/2, cos(ang+(M_PI*2/slices))*radius);
		glEnd();
		
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(sin(ang+(M_PI*2/slices))*radius, height/2, cos(ang+(M_PI*2/slices))*radius);
		glVertex3f(sin(ang)*radius, -height/2, cos(ang)*radius);
		glVertex3f(sin(ang+(M_PI*2/slices))*radius, -height/2, cos(ang+(M_PI*2/slices))*radius);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f, -height/2, 0.0f);
		glVertex3f(sin(ang)*radius, -height/2, cos(ang)*radius);
		glVertex3f(sin(ang+(M_PI*2/slices))*radius, -height/2, cos(ang+(M_PI*2/slices))*radius);
		glEnd();

		ang +=  M_PI*2/(slices);
	}

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	
	gluLookAt(sin(alpha)*cos(beta)*raio,sin(beta)*raio,cos(alpha)*cos(beta)*raio, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	/*
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	*/
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f( 100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	drawCylinder(radius,height,slices);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
	
	switch(key){
		case 'a':
			alpha -= M_PI/16;
			break;
		case 'd':
			alpha += M_PI/16;
			break;
		case 'w':
			if(!(beta+M_PI/16>M_PI/2)){
				beta += M_PI/16;
			}
			break;
		case 's':
			if(!(beta-M_PI/16<-M_PI/2)){
				beta -= M_PI/16;
			}
			break;
		case 'z':
			raio += 1;
			break;
		case 'x':
			raio -= 1;
			break;
	}
	glutPostRedisplay();
	
}


void processSpecialKeys(int key, int xx, int yy) {

	switch(key){
		case GLUT_KEY_UP:
			slices++;
			drawCylinder(radius,height,slices);
			break;
		case GLUT_KEY_DOWN:
			if (slices != 0)
			slices--;
			drawCylinder(radius,height,slices);
			break;
		
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
