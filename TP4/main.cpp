#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

using namespace std;


float alfa = 0.0f, betah = 0.0f, radius = 5.0f;
float camX, camY, camZ;
GLuint buffers[1];
GLuint verticeCount;

int timebase;
float frame;


void spherical2Cartesian() {

	camX = radius * cos(betah) * sin(alfa);
	camY = radius * sin(betah);
	camZ = radius * cos(betah) * cos(alfa);
}


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


/*----------------------------------------------------------------------------------- 
	Draw Cylinder with strips and fans

	  parameters: radius, height, sides

-----------------------------------------------------------------------------------*/


void cylinder0(float radius, float height, int sides) {

	int i;
	float step;

	step = 360.0/sides;

	glColor3f(1,0,0);
	glBegin(GL_TRIANGLE_FAN);

		glVertex3f(0,height*0.5,0);
		for (i=0; i <= sides; i++) {
			glVertex3f(cos(i * step * M_PI/180.0)*radius,height*0.5,-sin(i * step *M_PI/180.0)*radius);
		}
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_TRIANGLE_FAN);

		glVertex3f(0,-height*0.5,0);
		for (i=0; i <= sides; i++) {
			glVertex3f(cos(i * step * M_PI/180.0)*radius,-height*0.5,sin(i * step *M_PI/180.0)*radius);
		}
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_TRIANGLE_STRIP);

		for (i=0; i <= sides; i++) {
			glVertex3f(cos(i * step * M_PI/180.0)*radius, height*0.5,-sin(i * step *M_PI/180.0)*radius);
			glVertex3f(cos(i * step * M_PI/180.0)*radius,-height*0.5,-sin(i * step *M_PI/180.0)*radius);
		}
	glEnd();
}


/*-----------------------------------------------------------------------------------
	Draw Cylinder

		parameters: radius, height, sides

-----------------------------------------------------------------------------------*/


void cylinder(float radius, float height, int sides) {

	int i;
	float step;

	step = 360.0 / sides;

	glBegin(GL_TRIANGLES);

	// top
	for (i = 0; i < sides; i++) {
		glVertex3f(0, height*0.5, 0);
		glVertex3f(cos(i * step * M_PI / 180.0)*radius, height*0.5, -sin(i * step *M_PI / 180.0)*radius);
		glVertex3f(cos((i+1) * step * M_PI / 180.0)*radius, height*0.5, -sin((i + 1) * step *M_PI / 180.0)*radius);
	}

	// bottom
	for (i = 0; i < sides; i++) {
		glVertex3f(0, -height*0.5, 0);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0)*radius, -height*0.5, -sin((i + 1) * step *M_PI / 180.0)*radius);
		glVertex3f(cos(i * step * M_PI / 180.0)*radius, -height*0.5, -sin(i * step *M_PI / 180.0)*radius);
	}

	// body
	for (i = 0; i <= sides; i++) {

		glVertex3f(cos(i * step * M_PI / 180.0)*radius, height*0.5, -sin(i * step *M_PI / 180.0)*radius);
		glVertex3f(cos(i * step * M_PI / 180.0)*radius, -height*0.5, -sin(i * step *M_PI / 180.0)*radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0)*radius, height*0.5, -sin((i + 1) * step *M_PI / 180.0)*radius);

		glVertex3f(cos(i * step * M_PI / 180.0)*radius, -height*0.5, -sin(i * step *M_PI / 180.0)*radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0)*radius, -height*0.5, -sin((i + 1) * step *M_PI / 180.0)*radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0)*radius, height*0.5, -sin((i + 1) * step *M_PI / 180.0)*radius);
	}
	glEnd();
}

void drawCylinder(){

	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, 0, verticeCount);


}

void prepareCylinder(float radius, float height, int slices){
	
	vector<float> p;

	float ang = 0;

	for(int i = 0; i!= slices; i++){
		
		p.push_back(0.0f);
		p.push_back(height/2);
		p.push_back(0.0f);
		
		
		p.push_back(sin(ang)*radius);
		p.push_back(height/2);
		p.push_back(cos(ang)*radius);
		

		p.push_back(sin(ang+(M_PI*2/slices))*radius);
		p.push_back(height/2);
		p.push_back(cos(ang+(M_PI*2/slices))*radius);
		

		p.push_back(sin(ang)*radius);
		p.push_back(height/2);
		p.push_back(cos(ang)*radius);


		p.push_back(sin(ang)*radius);
		p.push_back(-height/2);
		p.push_back(cos(ang)*radius);
		

		p.push_back(sin(ang+(M_PI*2/slices))*radius);
		p.push_back(height/2);
		p.push_back(cos(ang+(M_PI*2/slices))*radius);
		
		
		
		p.push_back(sin(ang+(M_PI*2/slices))*radius);
		p.push_back(height/2);
		p.push_back(cos(ang+(M_PI*2/slices))*radius);


		p.push_back(sin(ang)*radius);
		p.push_back(-height/2);
		p.push_back(cos(ang)*radius);
		

		p.push_back(sin(ang+(M_PI*2/slices))*radius);
		p.push_back(-height/2);
		p.push_back(cos(ang+(M_PI*2/slices))*radius);
		
		

		p.push_back(0.0f);
		p.push_back(-height/2);
		p.push_back(0.0f);
		

		p.push_back(sin(ang+(M_PI*2/slices))*radius);
		p.push_back(-height/2);
		p.push_back(cos(ang+(M_PI*2/slices))*radius);
		

		p.push_back(sin(ang)*radius);
		p.push_back(-height/2);
		p.push_back(cos(ang)*radius);
		
		
		ang +=  M_PI*2/(slices);
	}

	verticeCount = p.size() / 3;

	glGenBuffers(1, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * p.size(), // tamanho do vector em bytes
		p.data(), // os dados do array associado ao vector
		GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)


	
}

void showFPS(){
	int time;
	float fps;
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
		timebase = time;
		frame = 0;
		char s[64];
		sprintf(s,"FPS: %6.2f",fps);
		glutSetWindowTitle(s);
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	drawCylinder();

	

	// End of frame
	glutSwapBuffers();

	showFPS();
	
}


void processKeys(unsigned char key, int xx, int yy) {

	switch(key){
		case 'a':
			alfa -= M_PI/16;
			break;
		case 'd':
			alfa += M_PI/16;
			break;
		case 'w':
			if(!(betah+M_PI/16>M_PI/2)){
				betah += M_PI/16;
			}
			break;
		case 's':
			if(!(betah-M_PI/16<-M_PI/2)){
				betah -= M_PI/16;
			}
			break;
		case 'z':
			radius += 1;
			break;
		case 'x':
			radius -= 1;
			break;
	}
	glutPostRedisplay();

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		betah += 0.1f;
		if (betah > 1.5f)
			betah = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		betah -= 0.1f;
		if (betah < -1.5f)
			betah = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 0.1f;
		if (radius < 0.1f)
			radius = 0.1f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 0.1f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Page Up and Page Down control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

	timebase = glutGet(GLUT_ELAPSED_TIME);
	glutGet(GLUT_ELAPSED_TIME);
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	// init GLEW
#ifndef __APPLE__
	glewInit();
#endif


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPolygonMode(GL_FRONT, GL_LINE);

	spherical2Cartesian();

	printInfo();

	prepareCylinder(1,2,10);

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
