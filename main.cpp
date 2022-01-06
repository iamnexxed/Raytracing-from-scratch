#include "global.h"


const int NumOfSpheres = 3;

Sphere spheres[NumOfSpheres];

void LoadSpheres()
{
    spheres[0].center = Vector3(0, 0, 0);
    spheres[0].radius = 2;
    spheres[0].color = Vector3(0, 1, 0);

    spheres[1].center = Vector3(0, 5, 0);
    spheres[1].radius = 2;
    spheres[1].color = Vector3(0, 1, 1);

    spheres[2].center = Vector3(0, -5, 0);
    spheres[2].radius = 2;
    spheres[2].color = Vector3(1, 1, 0);
}


void DrawPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b)
{
    glColor3f(r, g, b);
    // Drawing is done by specifying a sequence of vertices.  The way these
    // vertices are connected (or not connected) depends on the argument to
    // glBegin.  GL_POLYGON constructs a filled polygon.
    glBegin(GL_POINTS);
    glVertex2i(halfWindowWidth + x, halfWindowHeight - y);
    glEnd();
}

void TraceSpheres()
{
    Vector3 Origin(0, 0, 0);

    for (int x = -CANVAS_WIDTH / 2; i <= CANVAS_WIDTH / 2; i++)
    {
        for (int y = -CANVAS_HEIGHT / 2; i <= CANVAS_HEIGHT / 2; i++)
        {
            Vector2Int canvas(x, y);
            Vector3 Dir = CanvasToViewport(canvas);
            Vector3 color = TraceRayOnSpheres(Origin, Dir, 1, INFINITY, spheres, NumOfSpheres);
            DrawPixel(x, y, color.x, color.y, color.z);
        }
    }
}

// Clears the current window and draws a triangle.
void display()
{

    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);

    //DrawPixel(0, -200, 1, 1, 1);

    TraceSpheres();
    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();
}

// Convert from canvas coordinates to viewport coordinates.
Vector3 CanvasToViewport(Vector2Int& canvasCoord)
{
    Vector3 viewport;
    viewport.x = canvasCoord.x * VIEWPORT_WIDTH / CANVAS_WIDTH;
    viewport.y = canvasCoord.y * VIEWPORT_HEIGHT / CANVAS_HEIGHT;
    viewport.z = distanceToViewport;
    return viewport;
}



// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char **argv)
{

    // Use a single buffered window in RGB mode (as opposed to a double-buffered
    // window or color-index mode).
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Position window at (80,80)-(480,380) and give it a title.
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    glutCreateWindow("CG");

    // Tell GLUT that whenever the main window needs to be repainted that it
    // should call the function display().
    glutDisplayFunc(display);

    glClear(GL_COLOR_BUFFER_BIT);

    LoadSpheres();
    // Specifies which matrix stack is the target for subsequent matrix operations. Three values are accepted: GL_MODELVIEW, GL_PROJECTION, and GL_TEXTURE.
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    

    // gluOrtho2D — define a 2D orthographic projection matrix
    gluOrtho2D(0.0, CANVAS_WIDTH, CANVAS_HEIGHT, 0.0);

    

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
    glutMainLoop();
}