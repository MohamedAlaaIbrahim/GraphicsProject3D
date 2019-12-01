#include <stdio.h>
#include <glut.h>

int counter = 0;

float rotAng;
float wallTranslate = 0;
float cameraYaxis = 0;
float cameraXaxis = 0;
float cameraZaxis = 0;
float cameraRYaxis = 0;
float cameraRXaxis = 0;
float cameraRZaxis = 0;
float tSphereXMotion = 0;
float tSphereYMotion = 0;
float tSphereZMotion = 0;
float sphereXMotion = 0;
float sphereYMotion = 0;
float sphereZMotion = 0;
float slowMotionX = 0;
float slowMotionY = 0;

bool slowMotionRepeat = false;
bool sphereMotionStart = false;
bool xColDetection = false;
bool yColDetection = false;
bool zColDetection = false;

void Anim() {
	rotAng += 0.01;

	glutPostRedisplay();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightPosition[] = { 0.0f, 2.5f, 1.0f, 0.0f };
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightPosition);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.001, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0 + cameraXaxis - sphereXMotion / 5, 1.75 + cameraYaxis - sphereYMotion / 5, 3.5 + cameraZaxis + sphereZMotion, 0.0 + cameraXaxis + cameraRXaxis, 1.6 + cameraYaxis + cameraRYaxis + cameraYaxis + sphereYMotion / 10, 1 + cameraZaxis + cameraRZaxis + cameraZaxis + sphereZMotion, 0.0, 1.0, 0.0);
}

void keyBoardFunction(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'd': cameraXaxis += 0.05; break;
	case 'a': cameraXaxis -= 0.05; break;
	case 's': cameraZaxis += 0.05; break;
	case 'w': cameraZaxis -= 0.05; break;
	case 'r': cameraYaxis += 0.05; break;
	case 'f': cameraYaxis -= 0.05; break;
	case '6': tSphereXMotion < 1.45 ? tSphereXMotion += 0.05 : tSphereXMotion; break;
	case '4': tSphereXMotion > -1.45 ? tSphereXMotion -= 0.05 : tSphereXMotion; break;
	case '8': tSphereYMotion < 1.45 ? tSphereYMotion += 0.05 : tSphereYMotion; break;
	case '2': tSphereYMotion > -1.45 ? tSphereYMotion -= 0.05 : tSphereYMotion; break;
	case 32: sphereMotionStart = true; break;
	case 'm': slowMotionRepeat = true; break;
	default:
		break;
	}
}

void arrowControl(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP: cameraRYaxis += 0.05; break;
	case GLUT_KEY_DOWN: cameraRYaxis -= 0.05; break;
	case GLUT_KEY_RIGHT: cameraRXaxis += 0.05; break;
	case GLUT_KEY_LEFT: cameraRXaxis -= 0.05; break;
	default:
		break;
	}
}

void drawBrick(double thickness) {
	glPushMatrix();
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void drawWall(){
	int colorCounter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			glPushMatrix();
			glTranslatef(-1 + j, 0, -3 + i);
			switch (colorCounter) {
			case 0: glColor3f(1, 0, 0); break;
			case 1:	glColor3f(0, 1, 0); break;
			case 2: glColor3f(0, 0, 1); break;
			case 3:	glColor3f(1, 1, 0); break;
			case 4: glColor3f(1, 0, 1); break;
			case 5: glColor3f(0, 1, 1); break;
			case 6: glColor3f(0.5, 0.5, 0); break;
			case 7: glColor3f(0.5, 0, 0.5); break;
			case 8: glColor3f(0.5, 0.5, 0.5); break;
			default: glColor3f(1, 1, 1); break;
			}
			drawBrick(0.01);
			glPopMatrix();
			colorCounter+=1;
		}
	}
}

void resetGame() {
	tSphereXMotion = 0;
	tSphereYMotion = 0;
	tSphereZMotion = 0;
	sphereXMotion = 0;
	sphereYMotion = 0;
	sphereZMotion = 0;
	sphereMotionStart = false;
	xColDetection = false;
	yColDetection = false;
	zColDetection = false;
	slowMotionRepeat = false;
	counter = 0;
}

void drawStickyWall() {
	glPushMatrix();
	glScaled(3, 1, 3);
	glColor3f(0, 0, 0);
	drawBrick(0.01);
	glPopMatrix();
}

void drawRoom() {

	drawWall();
	
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(1.5, 1.5, 0);
	drawWall();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3, 0);
	drawWall();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(1.5, -1.5, 0);
	drawWall();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, -3.5, -1.5);
	drawStickyWall();
	glPopMatrix();

}

void sphereDraw() {
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0 + sphereXMotion, 1.5 + sphereYMotion, -0.5 + sphereZMotion);
	glutWireSphere(0.15, 90000, 90000);
	glPopMatrix();
}

void sphereMotion() {
	if (counter == 0 && !slowMotionRepeat) {
		slowMotionX = tSphereXMotion / 1000;
		slowMotionY = tSphereYMotion / 1000;
		counter++;
	}
	if (!slowMotionRepeat) {
		sphereXMotion += tSphereXMotion / 300;
		sphereYMotion += tSphereYMotion / 300;

		sphereZMotion > -2.925 ? sphereZMotion -= 0.001 : resetGame();

		sphereXMotion < -1.375 ? tSphereXMotion = -tSphereXMotion : xColDetection;
		sphereXMotion > 1.375 ? tSphereXMotion = -tSphereXMotion : xColDetection;

		sphereYMotion < -1.375 ? tSphereYMotion = -tSphereYMotion : yColDetection;
		sphereYMotion > 1.375 ? tSphereYMotion = -tSphereYMotion : yColDetection;
	}
	else {
		sphereXMotion += slowMotionX;
		sphereYMotion += slowMotionY;

		sphereZMotion > -2.925 ? sphereZMotion -= 0.0003 : resetGame();

		sphereXMotion < -1.375 ? slowMotionX = -slowMotionX : xColDetection;
		sphereXMotion > 1.375 ? slowMotionX = -slowMotionX : xColDetection;

		sphereYMotion < -1.375 ? slowMotionY = -slowMotionY : yColDetection;
		sphereYMotion > 1.375 ? slowMotionY = -slowMotionY : yColDetection;
	}

}

void drawShootingArrow() {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(tSphereXMotion, tSphereYMotion + 1.5, -1.5);
	glVertex3f(0.0, 1.5, -0.5);
	glEnd();
	glPopMatrix();
}

void shootingStation() {
	sphereDraw();
	if (sphereMotionStart) {
		sphereMotion();
	}
	else
		if(!slowMotionRepeat)
			drawShootingArrow();
}

void slowMotion() {
	printf("%d slow motion bool %f X %f Y\n", slowMotionRepeat, slowMotionX, slowMotionY);
	if (slowMotionRepeat)
		sphereMotion();
	//slowMotionRepeat = false;
}

void Display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setupCamera();
	setupLights();

	drawRoom();

	shootingStation();
	slowMotion();

	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("OpenGL - 3D Template");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(keyBoardFunction);
	glutSpecialFunc(arrowControl);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glutMainLoop();
}
