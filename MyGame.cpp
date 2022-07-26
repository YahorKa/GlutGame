
#include "MainWindow.h"
#include "PidRegSpeed.cpp"

int cordX, cordY;
bool state_cursor_in_window;

// PID regulator for moving spaseship
PidRegSpeed pid_x(glutGet(GLUT_ELAPSED_TIME), spaceshipX);
PidRegSpeed pid_y(glutGet(GLUT_ELAPSED_TIME), spaceshipY);

// GET MOUSE CORD
void mouse(int x, int y)
{
    cordX = x;
    cordY = 1000 - y;
}

void mouse_cursor(int state)
{
    if (state)
        glutSetCursor(GLUT_CURSOR_NONE);
    state_cursor_in_window = state;
}

void update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (!state_cursor_in_window)
    {
        return;
    }
    if (game_over)
    {
        speed = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);
        drawText("GAME OVER", 360, 455);
        glutPostRedisplay();
        return;
    }

    // while healthy
    glClear(GL_COLOR_BUFFER_BIT);
    drawHurdle();
    spaceshipX = spaceshipX + pid_x.update_pid(glutGet(GLUT_ELAPSED_TIME), spaceshipX, cordX);
    spaceshipY = spaceshipY + pid_y.update_pid(glutGet(GLUT_ELAPSED_TIME), spaceshipY, cordY);
    drawSpaceship();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    try
    {
        create_window(argc, argv);
        init();
        glutEntryFunc(mouse_cursor);
        glutSpecialFunc(Specialkey);
        glutPassiveMotionFunc(mouse);
        glutDisplayFunc(update);
        glutMainLoop();
    }
    catch (int err)
    {
        printf("EXT %i", err);
    }
    return 0;
}
