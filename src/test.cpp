#include <GLUT/glut.h>
#include <math.h>
#include <algorithm>

GLfloat cameraAngleX = 0.0f;
GLfloat cameraAngleY = 0.0f;
GLfloat cameraDistance = 5.0f;
GLfloat cameraX = cameraDistance * cos(cameraAngleY) * cos(cameraAngleX);
GLfloat cameraY = cameraDistance * sin(cameraAngleX);
GLfloat cameraZ = cameraDistance * sin(cameraAngleY) * cos(cameraAngleX);


// Function to draw a simple cube as the object
void drawCube() {
    glutWireCube(1.0f); // You can replace this with your own object drawing code
}

// Function to handle all drawings
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera position
    

    gluLookAt(cameraX, cameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Draw the object (in this case, a cube)
    drawCube();

    glutSwapBuffers();
}

// Function to calculate Euclidean distance
GLfloat calculateDistance(GLfloat x, GLfloat y, GLfloat z) {
    return sqrt(x * x + y * y + z * z);
}

// Function to handle resizing of the window
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    GLfloat prevCameraDistance;
    switch (key) {
        case 'x':
            cameraAngleX += 0.01f; // Rotate around the x-axis
            break;
        case 'y':
            cameraAngleY += 0.01f; // Rotate around the y-axis
            break;
        case 'n':
            // Generate new camera position based on the previous one
            prevCameraDistance = calculateDistance(cameraX, cameraY, cameraZ);
            cameraDistance = std::max(0.1f, prevCameraDistance - 0.1f); // Ensure distance is not negative
            break;
        case 'm':
            // Generate new camera position based on the previous one
            prevCameraDistance = calculateDistance(cameraX, cameraY, cameraZ);
            cameraDistance = prevCameraDistance + 0.1f;
            break;
        // Add additional cases for other keys if needed
    }

    glutPostRedisplay();
}

// Function to handle updates (e.g., camera rotation)
void update(int value) {
    glutTimerFunc(16, update, 0); // Update every 16 milliseconds (approximately 60 FPS)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Rotate Camera Around Object");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0); // Start the update timer

    glutMainLoop();

    return 0;
}