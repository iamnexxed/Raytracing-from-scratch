#include "global.h"
#include "lights.h"

const int NumOfSpheres = 4;
const int RecursionDepth = 3;

Sphere spheres[NumOfSpheres];

Camera camera;

void LoadCamera()
{
    camera.transform.position = Vector3(1000, 0, -10);
    camera.transform.SetRotationAngles((M_PI / 180) * (45), (M_PI / 180) * (-45), (M_PI / 180) * (0));
}

void LoadSpheres()
{

    int i = 0;
    // Green
    if(i < NumOfSpheres)
    {
        spheres[i].center = Vector3(100, 0, 900);
        spheres[i].radius = 70;
        spheres[i].color = Vector3(0, 1, 0);
        spheres[i].specular = 50;
        spheres[i].reflectivity = 0;
        i++;
    }
    

    // Blue
    if (i < NumOfSpheres)
    {
        spheres[i].center = Vector3(200, 70, 900);
        spheres[i].radius = 100;
        spheres[i].color = Vector3(0, 0, 1);
        spheres[i].specular = 100;
        spheres[i].reflectivity = 0;
        i++;
    }

    // Red
    if (i < NumOfSpheres)
    {
        spheres[i].center = Vector3(-100, 0, 800);
        spheres[i].radius = 100;
        spheres[i].color = Vector3(1, 0, 0);
        spheres[i].specular = 30;
        spheres[i].reflectivity = 0;
        i++;
    }

    // White
    if (i < NumOfSpheres)
    {
        spheres[i].center = Vector3(0, -1100, 1000);
        spheres[i].radius = 1000;
        spheres[i].color = Vector3(1, 0.5, 1);
        spheres[i].specular = 100;
        spheres[i].reflectivity = 0.3;
        i++;
    }
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
    Vector3 cameraRotation = camera.transform.rotation.ToEulerAngles();

    for (int x = -CANVAS_WIDTH / 2; x < CANVAS_WIDTH / 2; x++)
    {
        for (int y = -CANVAS_HEIGHT / 2; y < CANVAS_HEIGHT / 2; y++)
        {
            Vector2Int canvas(x, y);
            Vector3 Dir = camera.transform.rotation * CanvasToViewport(canvas);
            //Dir = Vector3::RotateVectorAround(CanvasToViewport(canvas), Vector3(0,0,1),M_PI_4);
            // Vector3 matDir = CanvasToViewport(canvas);
            // matDir = MultiplyMV(camera_rotation, matDir);
            // if(!(matDir == Dir))
            // {
            //     Dir.Normalize();
            // }
            //  Dir.Normalize();
            //  Vector3 color = TraceRayOnSpheres(Origin, Dir, 1, INFINITY, spheres, NumOfSpheres);
            Vector3 color = TraceRayOnObjects(camera.transform.position, Dir, 1, INFINITY, spheres, NumOfSpheres, RecursionDepth);

            DrawPixel(x, y, color.x, color.y, color.z);
        }
    }
}

// Clears the current window 
void display()
{
    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);
    
    TraceSpheres();
    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();
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
    LoadSpheres();
    LoadLightSources();
    LoadCamera();

    glutDisplayFunc(display);
    glClear(GL_COLOR_BUFFER_BIT);

    // Specifies which matrix stack is the target for subsequent matrix operations. Three values are accepted: GL_MODELVIEW, GL_PROJECTION, and GL_TEXTURE.
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();

    // gluOrtho2D — define a 2D orthographic projection matrix
    gluOrtho2D(0.0, CANVAS_WIDTH, CANVAS_HEIGHT, 0.0);

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
   
    glutMainLoop();
    
    
    
}