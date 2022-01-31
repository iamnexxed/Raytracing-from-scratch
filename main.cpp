#include "global.h"
#include "lights.h"

const int NumOfSpheres = 4;

Sphere spheres[NumOfSpheres];

void LoadSpheres()
{

    int i = 0;
    // Green
    if(i < NumOfSpheres)
    {
        spheres[i].center = Vector3(-50, 0, 1000);
        spheres[i].radius = 70;
        spheres[i].color = Vector3(0, 1, 0);
        spheres[i].specular = 50;
        i++;
    }
    

    // Blue
    if (i < NumOfSpheres)
    {
        spheres[i].center = Vector3(100, 70, 1000);
        spheres[i].radius = 100;
        spheres[i].color = Vector3(0, 0, 1);
        spheres[i].specular = 0;
        i++;
    }
    // Red
    if (i < NumOfSpheres)
    {
        spheres[i].center = Vector3(0, 300, 1000);
        spheres[i].radius = 100;
        spheres[i].color = Vector3(1, 0, 0);
        spheres[i].specular = 30;
        i++;
    }

    // White
    if (i < NumOfSpheres)
    {
        spheres[i].center = Vector3(0, -100, 1000);
        spheres[i].radius = 100;
        spheres[i].color = Vector3(1, 1, 1);
        spheres[i].specular = 1000;
        i++;
    }
}

Vector2 IntersectRaySphere(Vector3 rayOrigin, Vector3 rayDirection, Sphere &sphere)
{
    Vector2 t(-INFINITY, -INFINITY);

    // (t2D, D) + t(2CO, D) + (CO, CO) − r2 = 0

    double a = DotProduct(rayDirection, rayDirection);

    double b = 2 * DotProduct(rayOrigin - sphere.center, rayDirection);

    double c = DotProduct(rayOrigin - sphere.center, rayOrigin - sphere.center) - sphere.radius * sphere.radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        t.x = (-b + sqrt(discriminant)) / (2 * a);
        t.y = (-b - sqrt(discriminant)) / (2 * a);
    }

    return t;
}

Vector3 TraceRayOnSpheres(Vector3 rayOrigin, Vector3 rayDirection, double tMin, double tMax, Sphere *spheres, const int NUM_SPHERES)
{
    Vector3 color = BLACK;

    double closestT = tMax;

    Sphere *closestSphere = nullptr;

    for (int i = 0; i < NUM_SPHERES; i++)
    {
        Vector2 t = IntersectRaySphere(rayOrigin, rayDirection, spheres[i]);

        if (t.x >= tMin && t.x <= tMax && t.x < closestT)
        {
            closestT = t.x;
            closestSphere = &spheres[i];
        }

        if (t.y >= tMin && t.y <= tMax && t.y < closestT)
        {
            closestT = t.y;
            closestSphere = &spheres[i];
        }
    }

    if (closestSphere != nullptr)
    {

        Vector3 P = rayOrigin + rayDirection * closestT;
        Vector3 N = P - closestSphere->center;
        N.Normalize();

        color = closestSphere->color * ComputeLighting(P, N, -rayDirection, closestSphere->specular);

        //color = closestSphere->color * ComputeLighting(P, N);
        //color = closestSphere->color;
    }

    

    return color;
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

    for (int x = -CANVAS_WIDTH / 2; x <= CANVAS_WIDTH / 2; x++)
    {
        for (int y = -CANVAS_HEIGHT / 2; y <= CANVAS_HEIGHT / 2; y++)
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