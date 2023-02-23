#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float posx = 0, posz = 0,posy= 0, angle = 0, scalex = 1, scaley = 1, scalez = 1,eixox = 0, eixoy=1,eixoz=0;
float face = GL_FILL;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// put axis drawing in here
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

// put the geometric transformations here
	glRotatef(angle, eixox, eixoy, eixoz);
	glTranslatef(posx,posy,posz);
	glScalef(scalex,scaley,scalez);
	

// put pyramid drawing instructions here
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f,1.0f,1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	

	
	glEnd();
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	

	
	glEnd();
	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void rotate(unsigned char key, int x, int y){
	switch(key){
		case 'a':
			posx -= 0.1;
			break;
		case 'x':
			eixox = 1;
			eixoy = 0;
			eixoz = 0;
			break;
		case 'z':
			eixox = 0;
			eixoy = 0;
			eixoz = 1;
			break;
		case 'y':
			eixox = 0;
			eixoy = 1;
			eixoz = 0;
			break;
		case 'r':
			posy += 0.1;
			break;
		case 'f':
			posy -= 0.1;
			break;
		case 'd':
			posx += 0.1;
			break;
		case 'w':
			posz -= 0.1;
			break;
		case 's':
			posz += 0.1;
			break;
		case 'q':
			angle -= 10;
			break;
		case 'e':
			angle += 10;
			break;
		case 'b':
			scaley += 1;
			break;
		case 'c':
			scaley += 1;
			scalex +=1;
			scalez +=1;
			break;
		case 'v':
			scaley -= 1;
			scalex -=1;
			scalez -=1;
			break;
		case 'n':
			scaley -= 1;
			break;
		case 'p':
			glPolygonMode(GL_FILL,GL_FRONT_AND_BACK);
			break;
		case 'o':
			glPolygonMode(GL_LINE,GL_FRONT_AND_BACK);
			break;
		case 'i':
			glPolygonMode(GL_POINT,GL_FRONT_AND_BACK);
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

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(rotate);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
