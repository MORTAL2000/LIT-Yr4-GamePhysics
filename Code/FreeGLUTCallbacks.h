#ifndef _FREEGLUTCALLBACKS_H_
#define _FREEGLUTCALLBACKS_H_

#include "BulletOpenGLApplication.h"

static BulletOpenGLApplication* g_pApp;		// global pointer to our application object

/* 
	Various static functions that will be handed to FreeGLUT to be called during various events (our callbacks). 
	Each calls an equivalent function in our (global) application object. 
*/
static void KeyboardCallback(unsigned char key, int x, int y) {
	g_pApp->Keyboard(key, x, y);
}
static void KeyboardUpCallback(unsigned char key, int x, int y) {
	g_pApp->KeyboardUp(key, x, y);
}
static void SpecialCallback(int key, int x, int y) {
	g_pApp->Special(key, x, y);
}
static void SpecialUpCallback(int key, int x, int y) {
	g_pApp->SpecialUp(key, x, y);
}
static void ReshapeCallback(int w, int h) {
	g_pApp->Reshape(w, h);
}
static void IdleCallback() {
	g_pApp->Idle();
}
static void MouseCallback(int button, int state, int x, int y) {
	g_pApp->Mouse(button, state, x, y);
	/*
	// JOR
	switch(button) {		
		case 2: if (state == 0) ShootBox(GetPickingRay(x, y)); break;						// Ch5.1right mouse button, pressed down, shoot a box
		case 1: if (state == 0) ShootBall(GetPickingRay(x, y)); break;						// JOR Middle button pressed, shoot a sphere
	}
	*/
}
static void MotionCallback(int x,int y) {
	g_pApp->Motion(x, y);
}
static void DisplayCallback(void) {
	g_pApp->Display();
}

// our custom-built 'main' function, which accepts a reference to a  BulletOpenGLApplication object.
int glutmain(int argc, char **argv, int width, int height, const char* title, BulletOpenGLApplication* pApp) {    
	g_pApp = pApp;																	// store the application object so we can access it globally

	// initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		
	g_pApp->Initialize();															// perform custom initialization our of application

	// give our static
	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutSpecialFunc(SpecialCallback);
	glutSpecialUpFunc(SpecialUpCallback);
	glutReshapeFunc(ReshapeCallback);
	glutIdleFunc(IdleCallback);
	glutMouseFunc(MouseCallback);
	glutPassiveMotionFunc(MotionCallback);
	glutMotionFunc(MotionCallback);
	glutDisplayFunc(DisplayCallback);
		
	g_pApp->Idle();																	// perform one render before we launch the application	
	
	glutMainLoop();																	// hand application control over to the FreeGLUT library. This function remains in a while-loop until the application is exited.

	return 0;
}

#endif