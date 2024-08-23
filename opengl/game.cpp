#include <GL/glut.h>
#include <stdio.h>
#include<iostream>
#include<string>
#include<math.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

int phyWidth = 1000;
int phyHeight = 1000;
int logWidth = 100;
int logHeight = 100;

int centerX = logWidth / 2;
int centerY = logHeight / 2;

int sqWid = 10;
int alphaX = 0;
int alphaY = 0;

float bulletY = 0;
int score=0;
char str[20]; // Initial bullet position along the y-axis

bool shootBullet = false; // Flag to indicate whether to shoot the bullet
int characterx=10;
int charactery=20;
int timeLeft = 10;

bool showGameOverMessage = false;
bool showVictoryMessage = false;

bool drawSmallPolygon = true;
bool drawSmallPolygon2 = true;
bool drawSmallPolygon3 = true;
bool drawSmallPolygon4 = true;
bool drawSmallPolygon5 = true;
bool drawSmallPolygon6 = true;

bool game= true;

bool startgame = false; // Initially false to show the menu
bool showInstructions = false;


enum GameState { MENU, GAME, INSTRUCTIONS };
GameState currentState = MENU;

std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}







void DrawCircleGreen(float cx, float cy, float r, int num_segments)
{

glBegin(GL_POLYGON);
glColor3f(0.0, 0.5, 0.0);

for (int i = 0; i < num_segments; i++) {
float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
float x = r * cosf(theta);//calculate the x component
float y = r * sinf(theta);//calculate the y component
glVertex2f(x + cx, y + cy);//output vertex
}
glEnd();
}
void DrawCircleblack(float cx, float cy, float r, int num_segments)
{

glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 0.0);

for (int i = 0; i < num_segments; i++) {
float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
float x = r * cosf(theta);//calculate the x component
float y = r * sinf(theta);//calculate the y component
glVertex2f(x + cx, y + cy);//output vertex
}
glEnd();
}
void init2D(float r, float g, float b) {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}


void printSome(char *str, int x, int y) {
    glColor3f(0.5, 0.5, 0.5);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(str); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]); // Larger font size
    }
    glFlush();
}

void displayMenu()
{   if(currentState==MENU){
     glClear(GL_COLOR_BUFFER_BIT);
    printSome("1. Start Game", 40, 60);
    printSome("2. Instructions", 40, 50);
    glFlush();

}

}
void displayInstructions()
{
    glClear(GL_COLOR_BUFFER_BIT);
    printSome("Instructions:", 40, 70);
    printSome("Use a,w,s,d keys to move", 40, 60);
    printSome("Letter c to shoot", 40, 50);
    printSome("Destroy all the stars before the time ends", 40, 40);
    printSome("Press 'M' to return to menu", 40, 30);
    glFlush();
}


// create ground
void createGround(){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,40);
    glVertex2f(100,40);
    glVertex2f(100,0);
    glEnd();

}

//create tree
void createTree(){
    glBegin(GL_POLYGON);
    glVertex2f(10,30);
    glVertex2f(10,60);
    glVertex2f(15,60);
    glVertex2f(15,30);
    glEnd();
}
//tree leaves
void createTreeLeaves(){
    glColor3f(0.4, 0.1, 0.1);
    DrawCircleGreen(10,60,5,100);
    DrawCircleGreen(12,65,5,100);
    DrawCircleGreen(15,60,5,100);
}

//create house
void createHouse(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(70, 40);
    glVertex2i(70, 60);
    glVertex2i(90, 60);
    glVertex2i(90, 40);
    glEnd();

    // Windows
    glColor3f(0.5, 0.5, 0.5); // Grey color for the windows

    // First window
    glBegin(GL_POLYGON);
    glVertex2i(74, 48);
    glVertex2i(76, 48);
    glVertex2i(76, 52);
    glVertex2i(74, 52);
    glEnd();

    // Second window
    glBegin(GL_POLYGON);
    glVertex2i(84, 48);
    glVertex2i(86, 48);
    glVertex2i(86, 52);
    glVertex2i(84, 52);
    glEnd();


    // First window
    glBegin(GL_POLYGON);
    glVertex2i(74, 48);
    glVertex2i(76, 48);
    glVertex2i(76, 52);
    glVertex2i(74, 52);
    glEnd();

    // Second window
    glBegin(GL_POLYGON);
    glVertex2i(84, 48);
    glVertex2i(86, 48);
    glVertex2i(86, 52);
    glVertex2i(84, 52);

    glEnd();
}
//house roof
void createHouseRoof(){
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(70, 60);
    glVertex2i(80, 70);
    glVertex2i(90, 60);
    glEnd();
}

// Create the chimney
void createChimney() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(87, 60);
    glVertex2i(87, 70);
    glVertex2i(89, 70);
    glVertex2i(89, 60);
    glEnd();

    // Chimney top
    glBegin(GL_POLYGON);
    glVertex2i(86, 70);
    glVertex2i(90, 70);
    glVertex2i(88, 72);
    glEnd();
}

//house door
void createHouseDoor(){
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(76+2, 40);
    glVertex2i(76+2, 44+2);
    glVertex2i(80+2, 44+2);
    glVertex2i(80+2, 40);
    glEnd();
    DrawCircleblack(81,43,0.5,100);
}

//plane
void createPlane(){
glColor3f(0.5, 0.5, 0.5);//plane head
     glBegin(GL_POLYGON);
       glVertex2f(characterx+alphaX, charactery+7+alphaY);
        glVertex2f(characterx+2+alphaX, charactery+7+alphaY);
        glVertex2f(characterx+1+alphaX, charactery+9+alphaY);
        glEnd();
    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_POLYGON);//plane body
        glVertex2f(characterx+alphaX, charactery+alphaY);
        glVertex2f(characterx+alphaX, charactery+7+alphaY);
        glVertex2f(characterx+2+alphaX, charactery+7+alphaY);
        glVertex2f(characterx+2+alphaX, charactery+alphaY);
        glEnd();
    glColor3f(0.5, 0.5, 0.5);//plane wing
     glBegin(GL_POLYGON);
       glVertex2f(characterx+2+alphaX, charactery+6+alphaY);
        glVertex2f(characterx+2+alphaX, charactery+4+alphaY);
        glVertex2f(characterx+4+alphaX, charactery+4+alphaY);
        glEnd();
        glColor3f(0.5, 0.5, 0.5);//plane wing
     glBegin(GL_POLYGON);
       glVertex2f(characterx+alphaX, charactery+6+alphaY);
        glVertex2f(characterx+alphaX, charactery+4+alphaY);
        glVertex2f(characterx-2+alphaX, charactery+4+alphaY);
        glEnd();
        glBegin(GL_POLYGON);//tail
        glVertex2f(characterx+alphaX, charactery+alphaY);
        glVertex2f(characterx-2+alphaX, charactery+alphaY);
        glVertex2f(characterx-2+alphaX, charactery+1+alphaY);
        glVertex2f(characterx+alphaX, charactery+2+alphaY);
        glEnd();
        glBegin(GL_POLYGON);//tail
        glVertex2f(characterx+2+alphaX, charactery+alphaY);
        glVertex2f(characterx+4+alphaX, charactery+alphaY);
        glVertex2f(characterx+4+alphaX, charactery+1+alphaY);
        glVertex2f(characterx+2+alphaX, charactery+2+alphaY);
        glEnd();
}

void drawStars(){
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.5);
    glBegin(GL_POINTS);
    for (int i = 0; i < 500; ++i) {
        int random_number = rand() % (100 - 40 + 1) + 40;//for half of the width
        float x = (float)(rand() % phyWidth);
        float y = (float)(random_number);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();

}

void displayGame(void) {

    if(game == true){


    glClear(GL_COLOR_BUFFER_BIT);
    createGround();
    //createTree();
    //createTreeLeaves();
    drawStars();
    createHouse();
    createHouseRoof();
    createChimney();
    createHouseDoor();
    glClearColor(0.0, 0.0, 0.2, 1.0);
    createPlane();
    // Draw enemy if the flag is true
    glColor3f(0.5, 0.5, 0.5);
    if (drawSmallPolygon) {
    glBegin(GL_POLYGON);
    glVertex2i(10, 82);
    glVertex2i(12, 85);
    glVertex2i(10, 88);
    glVertex2i(8, 85);
    glEnd();
    }
    if (drawSmallPolygon2) {
    glBegin(GL_POLYGON);
    glVertex2i(30, 82);
    glVertex2i(32, 85);
    glVertex2i(30, 88);
    glVertex2i(28, 85);
    glEnd();
    }

    if (drawSmallPolygon3) {
    glBegin(GL_POLYGON);
     glVertex2i(50, 82);
    glVertex2i(52, 85);
    glVertex2i(50, 88);
    glVertex2i(48, 85);
    glEnd();
    }
    if (drawSmallPolygon4) {
    glBegin(GL_POLYGON);
    glVertex2i(10, 62);
    glVertex2i(12, 65);
    glVertex2i(10, 68);
    glVertex2i(8, 65);
    glEnd();
}

if (drawSmallPolygon5) {
    glBegin(GL_POLYGON);
    glVertex2i(30, 62);
    glVertex2i(32, 65);
    glVertex2i(30, 68);
    glVertex2i(28, 65);
    glEnd();
}

if (drawSmallPolygon6) {
    glBegin(GL_POLYGON);
    glVertex2i(50, 62);
    glVertex2i(52, 65);
    glVertex2i(50, 68);
    glVertex2i(48, 65);
    glEnd();
}
    // Draw the bullet if the flag is true
    if (shootBullet) {
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2i(characterx + alphaX, bulletY);
        glVertex2i(characterx + 2 + alphaX, bulletY);
        glVertex2i(characterx + 2 + alphaX, bulletY + 2);
        glVertex2i(characterx + alphaX, bulletY + 2);
        glEnd();
        bulletY += 1.5;
        if (bulletY > phyHeight) // Reset bullet position
            shootBullet = false;
    }
}
    // Check if character hits an enemy -> lost
if (((characterx + alphaX <= 15) && (characterx + alphaX >= 10) &&
     (charactery + alphaY <= 78) && (charactery + alphaY >= 72)) ||
    ((characterx + alphaX <= 35) && (characterx + alphaX >= 30) &&
     (charactery + alphaY <= 78) && (charactery + alphaY >= 72)) ||
    ((characterx + alphaX <= 55) && (characterx + alphaX >= 50) &&
     (charactery + alphaY <= 78) && (charactery + alphaY >= 72)) ||
    ((characterx + alphaX <= 15) && (characterx + alphaX >= 10) &&
     (charactery + alphaY <= 58) && (charactery + alphaY >= 52)) ||
    ((characterx + alphaX <= 35) && (characterx + alphaX >= 30) &&
     (charactery + alphaY <= 58) && (charactery + alphaY >= 52)) ||
    ((characterx + alphaX <= 55) && (characterx + alphaX >= 50) &&
     (charactery + alphaY <= 58) && (charactery + alphaY >= 52))) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(50, 50);
    std::string message = "You lost!";
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    game=false;

     }
//show score and timer
   string text = "score: " + intToString(score);
    printSome((char*)text.c_str(),80,90);
    string timeText = "Time: " + intToString(timeLeft) + "s";
    printSome((char*)timeText.c_str(), 10, 90);

    if (showGameOverMessage)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(50, 50);
        string message = "You lost!";
        for (int i = 0; i < message.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
        }
    }
    else if (showVictoryMessage)
    {
         glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 1.0, 0.0);
        glRasterPos2f(50, 50);
        std::string message = "You win!";
        for (int i = 0; i < message.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
        }
    }


    glFlush();
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen before drawing

    switch (currentState) {
        case MENU:
            displayMenu();
            break;
        case GAME:
            displayGame();
            break;
        case INSTRUCTIONS:
            displayInstructions();
            break;
    }

    glutSwapBuffers();
}

void countdown(int value)
{
    if (timeLeft > 0)
    {
        timeLeft--;
        glutTimerFunc(1000, countdown, 0);
    }
    else
    {
        if (score != 6)
        {
            showGameOverMessage = true;
        }
        else
        {
            showVictoryMessage = true;
        }
    }

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    if (currentState == MENU) {
        switch (key) {
            case '1':
                currentState = GAME;
                glutTimerFunc(1000, countdown, 0);
                 glutPostRedisplay();
                break;
            case '2':
                currentState = INSTRUCTIONS;
                 glutPostRedisplay();
                break;
            case 27: // Escape key
                exit(0);
        }
    } else if (currentState == INSTRUCTIONS) {
        if (key == 'm' || key == 'M') {
            currentState = MENU;
             glutPostRedisplay();
        }
    } else if (currentState == GAME) {
               if (key == 'w')
            alphaY += 5;
        if (key == 's')
            alphaY -= 5;
        if (key == 'a')
            alphaX -= 5;
        if (key == 'd')
            alphaX += 5;
        if (key == 'c') {
            shootBullet = true;
            bulletY = charactery  + alphaY;
        }

        glutPostRedisplay();
        }
    }



/*void keyboard(unsigned char key, int x, int y) {
    if (key == 'w')
        alphaY += 5;
    if (key == 's')
        alphaY -= 5;
    if (key == 'a')
        alphaX -= 5;
    if (key == 'd')
        alphaX += 5;
    if (key == 'c') {
        shootBullet = true;
        bulletY = charactery  + alphaY;
    }

    glutPostRedisplay();
}*/





void checkCollision() {

      if (shootBullet&& drawSmallPolygon4  &&
        characterx + alphaX >= 8 &&
        characterx + alphaX <= 12 &&
        bulletY + 2 >= 80 &&
        bulletY <= 90) {
        drawSmallPolygon4= false;
        shootBullet = false;
        score++;
    }
    if (shootBullet && drawSmallPolygon5 &&
    characterx + alphaX >= 28 &&
    characterx + alphaX <= 32 &&
    bulletY + 2 >= 80 &&
    bulletY <= 90) {
    drawSmallPolygon5 = false;
    shootBullet = false;
    score++;
}

if (shootBullet && drawSmallPolygon6 &&
    characterx + alphaX >= 48 &&
    characterx + alphaX <= 52 &&
    bulletY + 2 >= 80 &&
    bulletY <= 90) {
    drawSmallPolygon6 = false;
    shootBullet = false;
    score++;
}

if (shootBullet && drawSmallPolygon &&
    characterx + alphaX >= 8 &&
    characterx + alphaX <= 12 &&
    bulletY + 2 >= 80 &&
    bulletY <= 85) {
    drawSmallPolygon = false;
    shootBullet = false;
    score++;
}

if (shootBullet && drawSmallPolygon2 &&
    characterx + alphaX >= 28 &&
    characterx + alphaX <= 32 &&
    bulletY + 2 >= 80 &&
    bulletY <= 90) {
    drawSmallPolygon2 = false;
    shootBullet = false;
    score++;
}

if (shootBullet && drawSmallPolygon3 &&
    characterx + alphaX >= 48 &&
    characterx + alphaX <= 52 &&
    bulletY + 2 >= 80 &&
    bulletY <= 90) {
    drawSmallPolygon3 = false;
    shootBullet = false;
    score++;
}



    if (bulletY >= phyHeight) { // If the bullet reaches the top of the frame
        shootBullet = false;    // Stop shooting the bullet
    }

    glutPostRedisplay(); // Redraw the scene after updating bullet position
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(phyWidth, phyHeight);

    glutInitWindowSize(phyWidth, phyHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("chicken invaders");
    init2D(0.529, 0.808, 0.922);

    srand(time(NULL));

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(checkCollision);// Check for collision continuously

    glutMainLoop();

    return 0;
}
