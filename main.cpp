/*
*----------------------------------------------------------------
*		Snake Game
*		
*		por: Antonio Lisboa de Melo Neto, Tiago Rocha Martins
*
*       Controles: Setas para cima, baixo, esquerda e direita
*
*----------------------------------------------------------------
*/

#include <windows.h>  
#include <GL/gl.h>
#include <GL/glut.h>  
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
 
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 9999
#define FPS 15


int score = 0;
bool food = true;
bool gameOver = false;
float snake_lenght = 5.0;   //Tamanho incial
int foodX,foodY;
short sDirection = RIGHT;	//Rumo inicial da cobra
float gridX, gridY;
float posX[30] = {0,0,0,0,0}, posY[30] = {0,-1,-2,-3,-4};


void initGlut() {
   glClearColor(0.4f, 0.4f, 0.4f, 0.4f); 		       // Seta a cor de fundo
   glClearDepth(1.0f);                                 // Seta o tamanho do background
   glEnable(GL_DEPTH_TEST);  			               // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    						   // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   						   // Enable smooth shading					
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
   // Adiciona cores e sombras
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);     
   glEnable(GL_LIGHTING);     
   glEnable(GL_LIGHT0);	
   glEnable(GL_COLOR_MATERIAL);
}

void grid(float gridX,float gridY) {
	gridX = -29;
 	gridY = 30;
 	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);          
	
	//Ch?o
	for(int i = -28;i < 33;i++){
		for(int j = 29; j > -30;j--){
			glLoadIdentity();                 
			glTranslatef(i, j, -91.0f); 			   				             
			glColor3f(0.0, 0.0, 0.0);
			glRotatef (0.0, 50.0, 50.0, 1.0);
			glPushMatrix();
			glScalef (1.0, 1.0, 1.0);
			glutSolidCube (1.0);
			glPopMatrix();
		}
	}
	
	//Muros             
    for(int i = 0;i < 60;i++){
    	
 		glLoadIdentity();                 
		glTranslatef(gridX, gridY, -90.0f); 			   
					             
		glColor3f(1, 0, 0);
		glRotatef (0.0, 50.0, 50.0, 1.0);
		glPushMatrix();
		glScalef (1.0, 1.0, 5.0);
		glutSolidCube (1.0);
		glPopMatrix();

        gridY = gridY - 1.0;
		 
	}
	
	for(int i = 0;i < 61;i++) {
		glLoadIdentity();                 
		glTranslatef(gridX, gridY, -90.0f); 
		
		glColor3f(1, 0, 0);
		glRotatef (0.0, 50.0, 50.0, 1.0);
		glPushMatrix();
		glScalef (1.0, 1.0, 5.0);
		glutSolidCube (1.0);
		glPopMatrix();
	
		gridX = gridX + 1.0;
	}
	
	for(int i = 0;i < 60;i++){
		glLoadIdentity();                 
		glTranslatef(gridX, gridY, -90.0f); 
			    
		glColor3f(1, 0, 0);
		glRotatef (0.0, 50.0, 50.0, 1.0);
		glPushMatrix();
		glScalef (1.0, 1.0, 5.0);
		glutSolidCube(1.0);
		glPopMatrix();

		gridY = gridY + 1.0;
	}
	
	for(int i = 0;i < 62;i++){
		glLoadIdentity();                 
		glTranslatef(gridX, gridY, -90.0f); 
					   
		glColor3f(1, 0, 0);
		glRotatef (0.0, 50.0, 50.0, 1.0);
		glPushMatrix();
		glScalef (1.0, 1.0, 5.0);
		glutSolidCube (1.0);
		glPopMatrix();
			
		gridX = gridX - 1.0;
	}
	
	//Casa da cobra
	glLoadIdentity();                 
	glTranslatef(1, -3, -89.0f); 
						   
	glColor3f(1.0, 0.0, 0.0);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 2.0, 5.0);
	glutSolidCube (1.0);
	glPopMatrix();
	
	//Telhado da casa
 	glLoadIdentity();
	glTranslatef(1, -3, -88.0f); 
						   
	glColor3f(0.7, 0.7, 0.0);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (1.0, 1.0, 3.0);
	glutSolidCone(1.0,1.0,20,1);
	glPopMatrix();
	
	//Pilastras-------------------------
	glLoadIdentity();                 
	glTranslatef(20, -20, -88.0f); 
 						  
	glColor3f(0.6, 0.6, 0.0);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 2.0, 5.0);
	glutSolidCube (1.0);
	glPopMatrix();
//---------------------------------
	glLoadIdentity();                 
	glTranslatef(19, 6, -88.0f); 
						   
	glColor3f(0.8, 1.6, 0.5);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 3.0, 5.0);
	glutSolidCube (1.0);
	glPopMatrix();
//---------------------------------
	glLoadIdentity();                 
	glTranslatef(-12, 8, -88.0f); 
						   
	glColor3f(1, 0.6, 1);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 3.0, 1.0);
	glutSolidCube (1.0);
	glPopMatrix();
//---------------------------------
	glLoadIdentity();                 
	glTranslatef(-23, -14, -88.0f); 
						   
	glColor3f(0.6, 1, 1);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 3.0, 1.0);
	glutSolidCube (1.0);
	glPopMatrix();
//---------------------------------
	glLoadIdentity();                 
	glTranslatef(5, 26, -88.0f); 
						   
	glColor3f(0.0, 1.5, 1.0);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 3.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
//---------------------------------
	glLoadIdentity();                 
	glTranslatef(10, 5, -88.0f); 
						   
	glColor3f(1.0, 1.0, 1.0);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 3.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
//---------------------------------
	glLoadIdentity();                 
	glTranslatef(5, 15, -88.0f); 
						   
	glColor3f(1.5, 1.0, 0.5);
	glRotatef (0.0, 50.0, 50.0, 1.0);
	glPushMatrix();
	glScalef (2.0, 3.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	gridX = 0;
	gridY = 0;
}

void random(int &x,int &y){
	int _maxX = 30-2;
	int _maxY = 30-2;
	int _min = -25;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);
}

void drawFood() {
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0; 
    
	if(food){
		random(foodX,foodY); //Randomizar a colis?o
		food = false;
	}
	
	//Objeto da comida
	glLoadIdentity();     	
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glTranslated(foodX + 2, foodY - 3, -90.0f); 
	glScalef (0.9, 0.9, 0.9);
	glutSolidSphere(1,100,7);
	glPopMatrix();
	glRectf(foodX,foodY,foodX+4,foodY+4);	
}

void snake() {
	for(int i = snake_lenght - 1;i > 0;i--){ 
		//Como fazer o corpo do Snake
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];	
	}
	
	if(sDirection == UP)
		posY[0]++;
	else if(sDirection == DOWN)
		posY[0]--;
	else if(sDirection == RIGHT)
		posX[0]++;
	else if(sDirection == LEFT)
		posX[0]--;
	
	for(int i = 0;i < snake_lenght;i++){
		if(i == 0){
			//Cabe?a
			glLoadIdentity();                 
			glTranslatef(gridX, gridY, -90.0f); 
						             
			glColor3f(1.0,1.0, 0.0);
			glTranslatef (1.0, -3.0, 0.0);
			glPushMatrix();
			glutSolidCube (1.0);
			glPopMatrix();
		} else {
			//Corpo
			glLoadIdentity();           
            glTranslatef(gridX, gridY, -90.0f);  
            glColor3f(1.0f, 1.5f, 0.5f);
			glTranslatef (1.0, -3.0, 0.0);
			glPushMatrix();
			glScalef (1.0, 1.0, 1.0);
			glutSolidCube (1.0);
			glPopMatrix();
		}
		
		glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
	}
	
	//Checa colis?o nos obstaculos	
	if((posX[0] == 30 || posY[0] == 32) ||
      (posX[0] == -30 || posY[0] == -27) ||
      (posX[0] == 18 && posY[0] == -18) ||
	  (posX[0] == 19 && posY[0] == 7) ||
	  (posX[0] == -13 && posY[0] == 9) || 
	  (posX[0] == -24 && posY[0] == -13) ||
	  (posX[0] == 4 && posY[0] == 28)) {
		gameOver = true; //Gera a mensagem de game over
	}
	
	if(abs(posX[0] - foodX) <= 1.0 && abs(posY[0] - foodY) <= 1.0){ // Conferir a colis?o com comida
		score++;
		snake_lenght++;
		if(snake_lenght > MAX)
			snake_lenght = MAX;
		food = true;
		PlaySound("eat-music.wav", NULL, SND_FILENAME | SND_LOOP);
		PlaySound("base-music.wav", NULL, SND_ASYNC | SND_LOOP);
	}
	
	for(int j = 1;j < snake_lenght;j++){ // Caso a cobra colida gerar gameover
    	if(posX[j] == posX[0] && posY[j] == posY[0])
			gameOver=true;
	}
}

 
void display() {
	grid(gridX,gridY);
	snake();
	drawFood();
	glutSwapBuffers();
	
	if(gameOver){
		PlaySound("game-over-music.wav", NULL, SND_FILENAME | SND_LOOP);
		char _score[10];
		itoa(score,_score,10);
		char text[50] = "Pontos coletados: ";
		strcat(text,_score);
		MessageBox(NULL,text,"Voce perdeu!",0);
		exit(0);
	}
}

void reshape(GLsizei width, GLsizei height) {  
   if (height == 0) height = 1;        					//N?o deixa dividir por 0        
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();             						//Reseta
   gluPerspective(45.0f, aspect, 1.5f, 100.0f);
   gluLookAt(0,0,1,
   	   	   	 0,-0.030,0,      
			 0,1,0);
}

void timerCallback(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timerCallback,0);
}

void keyboard_callback(int key,int,int){
	switch(key){
		case GLUT_KEY_UP:
			if(sDirection != DOWN)
				sDirection = UP;
			break;
		case GLUT_KEY_DOWN:
			if(sDirection != UP)
				sDirection = DOWN;
			break;
		case GLUT_KEY_RIGHT:
			if(sDirection != LEFT)
				sDirection = RIGHT;
			break;
		case GLUT_KEY_LEFT:
			if(sDirection != RIGHT)
				sDirection = LEFT;
			break;
	}
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);            			// Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); 			// Enable double buffered mode
   glutInitWindowSize(780,780);   				// Set the window's initial width & height
   glutInitWindowPosition(100,100); 			// Position the window's initial top-left corner
   glutCreateWindow("Snake Game");  			// Create window with the given title
   glutDisplayFunc(display);       				// Register callback handler for window re-paint event
   glutReshapeFunc(reshape);  
   glutTimerFunc(0, timerCallback, 0);
   glutSpecialFunc(keyboard_callback);     		// Register callback handler for window re-size event
   initGlut();                       			// Our own OpenGL initialization
   PlaySound("base-music.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
   glutMainLoop();                 				// Enter the infinite event-processing loop
   return 0;
}