#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
#include <cstddef>
#include <vector>
#include <cstring>

#define NUMBER_METEOR 10;
#define METEOR_SPEED  5;

int spaceshipX = 500, spaceshipY = 70, start_position = 1000 ,  tick_count = 0;
static int speed =1;
bool game_over = false;

//conrainer of meteors
std::vector<std::pair<int, int>> meteor;

void init()
{
  // glClearColor(0.62352,0.372549,0.623529,0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 1800, 0, 1000);
  glMatrixMode(GL_MODELVIEW);
}

void drawString(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)*c);  // Updates the position
  }
}

void drawText(char ch[],int xpos, int ypos)//draw score/message on screen
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos, ypos);
    for (int i = 0; i < numofchar; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);
    }
}

void Specialkey(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_HOME:
        if(game_over == true)
        {
            game_over = false;
            meteor.clear();

        }
        break;
    }
}

void create_window(int argc, char *argv[])
{
  glutInit(&argc, argv);                       //Передаём параметры функции main
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /*Иницилизируем дисплей с одним буфером(GLUT_SINGLE) в фрмате RGB 24 битный цвет*/
  glutInitWindowSize(1800, 1000);
  glutInitWindowPosition(100, 100); /*Расположение окна (x,y)*/
  glColor3f(0, 1, 1);
  glutCreateWindow("SPACE BATTLE"); /*Команда для создания окна;Название окна*/
  glMatrixMode(GL_PROJECTION);        /*Настроим 2-х мерный вид*/
  glLoadIdentity();
  //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); /*Задаём в каких пределах изменяеются координаты x,y,z*/
}
void drawSpaceship()
{
  glPointSize(10);
  glBegin(GL_POINTS); // front shooter
  glColor3f(1, 1, 1); // 111
  glVertex2f(spaceshipX, spaceshipY + 40);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.137255, 0.419608, 0.556863); // middle body
  glVertex2f(spaceshipX - 25, spaceshipY + 25);
  glVertex2f(spaceshipX - 25, spaceshipY - 25);
  glVertex2f(spaceshipX + 25, spaceshipY - 25);
  glVertex2f(spaceshipX + 25, spaceshipY + 25);
  glEnd();

  glBegin(GL_POINTS); // design on middle
  glColor3f(0.90, 0.91, 0.98);
  glVertex2f(spaceshipX - 10, spaceshipY - 5);
  glVertex2f(spaceshipX + 10, spaceshipY - 5);
  glEnd();

  glBegin(GL_POINTS); // thrusters
  glColor3f(1, 1, 1);
  glVertex2f(spaceshipX - 10, spaceshipY - 30);
  glVertex2f(spaceshipX + 10, spaceshipY - 30);
  glEnd();

  glBegin(GL_TRIANGLES); // right wing
  glColor3f(0.196078, 0.8, 0.196078);
  glVertex2f(spaceshipX + 25, spaceshipY + 25);
  glVertex2f(spaceshipX + 25, spaceshipY - 25);
  glVertex2f(spaceshipX + 45, spaceshipY - 35);
  glEnd();

  glBegin(GL_TRIANGLES); // left wing
  glColor3f(0.196078, 0.8, 0.196078);
  glVertex2f(spaceshipX - 25, spaceshipY + 25);
  glVertex2f(spaceshipX - 25, spaceshipY - 25);
  glVertex2f(spaceshipX - 45, spaceshipY - 35);
  glEnd();

  glBegin(GL_QUADS); // up body
  glColor3f(0.99609, 0.83984, 0);
  glVertex2f(spaceshipX - 25, spaceshipY + 25);
  glVertex2f(spaceshipX - 18, spaceshipY + 40);
  glVertex2f(spaceshipX + 18, spaceshipY + 40);
  glVertex2f(spaceshipX + 25, spaceshipY + 25);
  glEnd();
  glutSwapBuffers();
}

void drawHurdle() // hurdles
{
  //container with start pos of each meteor
  std::pair<int, int> met_pos;
  tick_count ++;
  // give start positions
  if (meteor.size() <=10)
  {
    met_pos.first =50+ rand()%1700;
    met_pos.second = start_position + rand()%800;
    meteor.push_back(met_pos);
  }

  for (auto i = meteor.begin(); i != meteor.end(); i++)
  {

    glBegin(GL_TRIANGLES); // left wing
    glColor3f(0.0, 0.3, 0.3);
    glVertex2f(i->first, i->second);
    glVertex2f(i->first - 20, i->second + 50);
    glVertex2f(i->first + 20, i->second + 50);
    glEnd(); // End of drawing color-cube
    if (((spaceshipX)>i->first-20)&&((spaceshipX)<i->first+20)&&((spaceshipY)>i->second-20)&&((spaceshipY)<i->second+20))
    game_over = true;
    i->second -= speed;
    if (i->second < -50)
    meteor.erase(i);
    //accumulate speed 
    if (tick_count>10000) {
    speed += 1;
    printf("%i\n",tick_count);
    tick_count = 0;
    }
  }
}

void search_intersection(void){
}