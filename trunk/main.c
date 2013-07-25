#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include "SOIL.h"

// Declaration
GLuint texture;
GLuint TextureBobFront;
GLuint TextureBobBack;
GLuint TextureBobTop;
GLuint TextureBobBottom;
GLuint TextureBobRight;
GLuint TextureBobLeft;
GLuint TextureBobLeg;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

// Load Bitmaps And Convert To Textures
GLuint LoadGLTextures(char* filename)
{
	/* load an image file directly as a new OpenGL texture */
	texture = SOIL_load_OGL_texture(
		filename, SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS |
		SOIL_FLAG_INVERT_Y |
		SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT
	);
	/* check for an error during the load process */
	if(texture == 0)
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return texture;
}

void drawSpongebob()
{
//	glEnable(GL_LIGHTING);
	
	// Front Face
	glTranslatef(2.0f ,2.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, TextureBobFront);
	glBegin(GL_QUADS);
//		glDisable(GL_BLEND);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 1.0f);
	glEnd();
	
	// Back Face
	glBindTexture(GL_TEXTURE_2D, TextureBobBack);
	glBegin(GL_QUADS);
//		glDisable(GL_BLEND);
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
	glEnd();
	
	// Top Face
	glBindTexture(GL_TEXTURE_2D, TextureBobTop);
	glBegin(GL_QUADS);
//		glDisable(GL_BLEND);
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
	glEnd();
	
	// Bottom Face
	glBindTexture(GL_TEXTURE_2D, TextureBobBottom);
	glBegin(GL_QUADS);
//		glDisable(GL_BLEND);
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -1.0f, 1.0f);
	glEnd();
	
	// Right Face
	glBindTexture(GL_TEXTURE_2D, TextureBobRight);
	glBegin(GL_QUADS);
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
	glEnd();
	
	// Left Face
	glBindTexture(GL_TEXTURE_2D, TextureBobLeft);
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 0.0f);
	glEnd();
	
	// Right Leg
	glBindTexture(GL_TEXTURE_2D, TextureBobLeg);
	glEnable(GL_DEPTH_TEST);
	// Front Side
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -0.1f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -0.1f, -1.0f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, -1.0f, 0.6f);
	glEnd();
	// Back Side
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -0.1f, -1.0f, 0.4f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -0.3f, -1.0f, 0.4f);
	glEnd();
	// Left Side
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.3f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.3f, -1.0f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, -1.0f, 0.4f);
	glEnd();
	// Right Side
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f, -1.0f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, -1.0f, 0.4f);
	glEnd();
	
	// Left Leg
	// Front Side
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.9f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.9f, -1.0f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.7f, -1.0f, 0.6f);
	glEnd();
	// Back Side
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.9f, -1.0f, 0.4f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.7f, -1.0f, 0.4f);
	glEnd();
	// Left Side
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.7f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.7f, -1.0f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.7f, -1.0f, 0.4f);
	glEnd();
	// Right Side
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.9f, -2.0f, 0.4f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9f, -2.0f, 0.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9f, -1.0f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.9f, -1.0f, 0.4f);
	glEnd();
}

void drawSnowMan()
{
	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	
	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);
	
	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);
	
	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();
	
	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f
				);
	
	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	
	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++)
	{
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}
	}
	
	// Draw Spongebob
	drawSpongebob();
	
    glutSwapBuffers();
}

//void init(void)
//{
//	glClearColor (0.0, 0.0, 0.0, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0, 0.0, 0.0, 0.0, -1.0, 1.0);
//}

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
	{
		h = 1;
	}
	float ratio = 1.0* w / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45.0f,ratio,0.1f,100.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	// Bind ESC button
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{
	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (640, 320);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Patrick! Tebak aku dimana?");
//	init();
	
	glEnable(GL_TEXTURE_2D);
	TextureBobFront = LoadGLTextures("bob_front.png");
	TextureBobBack = LoadGLTextures("bob_back.png");
	TextureBobTop = LoadGLTextures("bob_top.png");
	TextureBobBottom = LoadGLTextures("bob_bottom.png");
	TextureBobRight = LoadGLTextures("bob_right.png");
	TextureBobLeft = LoadGLTextures("bob_left.png");
	TextureBobLeg = LoadGLTextures("bob_leg.png");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	return 0;
}
