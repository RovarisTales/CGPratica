

#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float dx,dz;
float camX = 00, camY = 30, camZ = 40, radius = 100.0f;
float lookX = 00, lookY = 00, lookZ = 00;
int startX, startY, tracking = 0;
float a = 0;

int alpha = 0, beta = 45, r = 50;
float raio = 10;
float arr[1000];
unsigned int t, tw, th;
unsigned char *imageData;

GLuint *buffers;
GLuint verticeCount;

double h(int i, int j) {
	double x = imageData[i * tw + j];
	return x /5;
}

double hf(float x,float y){
	int x1 = floor(x);
	int y1 = floor(y);

	int x2 = x1+1;
	int y2 = y1+1;

	float fy = y - y1;
	float fx = x - x1;

	float h_x1_z = h(x1,y1) * (1-fy) + h(x1,y2) * fy;
 	float h_x2_z = h(x2,y1) * (1-fy) + h(x2,y2) * fy;

	float height_xz = h_x1_z * (1 - fx) + h_x2_z * fx;
	return height_xz;
}

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alpha);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alpha);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawBules(){
	glColor3f(1.0f,1.0f,1.0f);
	float ang = 0.0f;
	float pontox;
	float pontoz;
	raio = 15;
	float quantos = 360/8;
	for(int i = 0; i<8; i ++){
		
		glPushMatrix();
		pontox = sin(ang)*raio;
		pontoz = cos(ang)*raio;
		
		glTranslatef(pontox,2.0f,pontoz);
		glRotatef((quantos*i)-90,0.0f,1.0f,0.0f);
		glutSolidTeapot(2);
		glPopMatrix();

		ang += 2*M_PI/8;


	}
	ang = 0;
	raio = 35;
	quantos = 360/16;
	for(int i = 0; i<16; i ++){
		
		glPushMatrix();
		pontox = sin(ang)*raio;
		pontoz = cos(ang)*raio;
		
		glTranslatef(pontox,2.0f,pontoz);
		glRotatef(quantos*i,0.0f,1.0f,0.0f);
		glutSolidTeapot(2);
		glPopMatrix();

		ang += 2*M_PI/16;


	}


}


void generate(float* arr,int x){
	float randx = ((rand()%8192)-(8192/2))/32;
	float randz = ((rand()%8192)-(8192/2))/32 ;
		
	while(pow(randx,2)+pow(randz,2)<pow(50,2)){
		randx = ((rand()%8192)-(8192/2))/32;
	    randz = ((rand()%8192)-(8192/2))/32;
	}
	int y;
	y = 2*x;
	arr[y] = randx;
	arr[y+1] = randz;
}
void drawThree(){
	
	for(int i = 0;i<500;i++){
		float y = hf(arr[2*i]+(256/2),arr[2*i+1]+(256/2));

		glPushMatrix();
		
		glTranslatef(arr[2*i],y,arr[2*i+1]);
		glRotated(-90, 1, 0, 0);
		glColor3ub(102,62,36);
		glutSolidCone(0.5,2,10,10);
		glTranslatef(0,0,2);
		glColor3ub(0,100,0);
		glutSolidCone(2,4,10,10);
		glPopMatrix();



	}


}
void drawPlane(){


	for(int strip = 0; strip < th-1; strip++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffers[strip]);
		glVertexPointer(3, GL_DOUBLE, 0, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, verticeCount);
	}
}

void drawTerrain() {

    // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
	drawBules();
	drawThree();

}



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      lookX,lookY,lookZ,
			  0.0f,1.0f,0.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	drawPlane();

	drawTerrain();

	// just so that it renders something before the terrain is built
	// to erase when the terrain is ready
	//glutWireTeapot(2.0);

// End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {

	switch(key){
		case 'p':
			a = 0;
			camX = 0.0f;
			camZ = 0.0f;
			camY = hf(camX+(256/2),camZ+(256/2))+1;
			lookX = camX + sin(a);
			lookZ = camZ + cos(a);
			lookY = camY;
			break;
		case 'i':
			a += M_PI/16;
			
			lookX = camX + sin(a);
			lookZ = camZ + cos(a);
			lookY = camY;
			break;
		case 'o':
			a -= M_PI/16;
			
			lookX = camX + sin(a);
			lookZ = camZ + cos(a);
			lookY = camY;
			break;
		case 'w':

			dx = (lookX-camX);
			dz = (lookZ-camZ);
			camX = camX + dx;
			camZ = camZ + dz;
			camY = hf(camX+(256/2),camZ+(256/2))+1;
			//camY = hf(camX+(256/2),camZ+(256/2))+1;
			lookX = lookX +  dx;
			lookZ = lookZ +  dz;
			lookY = camY;
			//lookY = camY;
			break;
		case 's':

			dx = (lookX-camX);
			dz = (lookZ-camZ);
			camX = camX - dx;
			camZ = camZ - dz;
			camY = hf(camX+(256/2),camZ+(256/2))+1;
			//camY = hf(camX+(256/2),camZ+(256/2))+1;
			lookX = lookX -  dx;
			lookZ = lookZ -  dz;
			lookY = camY;
			//lookY = camY;
			break;
		case 'a':
			
			camX += 1;
			camY = hf(camX+(256/2),camZ+(256/2))+1;
			lookX = camX + sin(a);
			lookZ = camZ + cos(a);
			lookY = camY;
			break;
		case 'd':
			
			camX -= 1;
			camY = hf(camX+(256/2),camZ+(256/2))+1;
			lookX = camX + sin(a);
			lookZ = camZ + cos(a);
			lookY = camY;
			break;
		
	}
	
}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}


void init() {

// 	Load the height map "terreno.jpg"
	ilGenImages(1,&t);
	ilBindImage(t);
// terreno.jpg is the image containing our height map
	ilLoadImage((ILstring)"terreno.jpg");
// convert the image to single channel per pixel
// with values ranging between 0 and 255
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
// important: check tw and th values
// both should be equal to 256
// if not there was an error loading the image
// most likely the image could not be found
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	if (tw == 256 && th == 256)
        printf("Estamos bem\n");
// imageData is a LINEAR array with the pixel values
	imageData = ilGetData();

// 	Build the vertex arrays
	buffers = (GLuint *)calloc(th-1, sizeof(GLuint));
	glGenBuffers(th-1, buffers);

	int halfW = tw / 2;
	int halfH = th / 2;

	verticeCount = 2 * tw;

	for(int n_strip = 0; n_strip < th - 1; n_strip++) {
		std::vector<double> strip;
		for(int j = 0; j < tw; j++) {
			strip.push_back(n_strip - halfH);
			strip.push_back(h(n_strip,j));
			//strip.push_back(0);
			strip.push_back(j - halfW);

			strip.push_back(n_strip + 1 - halfH);
			strip.push_back(h(n_strip + 1,j));
			//strip.push_back(0);
			strip.push_back(j - halfW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, buffers[n_strip]);
    	glBufferData(GL_ARRAY_BUFFER,
					strip.size() * sizeof(double),
					strip.data(),
					GL_STATIC_DRAW);
	}

// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

	for(int j = 0;j<500;j++){
		generate(arr,j);
	}


// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(900,900);
	glutCreateWindow("CG@DI-UM");
		

// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);


	

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	
	glewInit();
	glEnableClientState(GL_VERTEX_ARRAY);
	ilInit();

	init();	

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

