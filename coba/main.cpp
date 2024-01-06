#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <tgmath.h>
#include <stdlib.h>  

using namespace std;

const float RAD_E = 2*M_PI;
float v= 0.2;
float r = 5.0;
float azimuth = -90*(M_PI / 180);
float elevation = 0;
char key = -1;
float vAng = v/r;

void drawCube() {
    glBegin(GL_QUADS);    //segiempat depan kamera    
    glColor3f(1,0,0);             
    glVertex3f(1,1,-1); //'kanan atas
    glColor3f(0,1,0);
    glVertex3f(1,-1,-1);//'kanan bawah 
    glColor3f(0,0,1);
    glVertex3f(-1,-1,-1); //'kiri bawah 
    glColor3f(1,1,0);
    glVertex3f(-1,1,-1); //'kiri atas
    glEnd();     
    // Menggambar kotak
    // glBegin(GL_QUADS);
    // Sisi depan
    // glVertex3f(-1.0, -1.0, 1.0);
    // glVertex3f(1.0, -1.0, 1.0);
    // glVertex3f(1.0, 1.0, 1.0);
    // glVertex3f(-1.0, 1.0, 1.0);
    // // Sisi belakang
    // glVertex3f(-1.0, -1.0, -1.0);
    // glVertex3f(1.0, -1.0, -1.0);
    // glVertex3f(1.0, 1.0, -1.0);
    // glVertex3f(-1.0, 1.0, -1.0);
    // // Sisi kanan
    // glVertex3f(1.0, -1.0, 1.0);
    // glVertex3f(1.0, -1.0, -1.0);
    // glVertex3f(1.0, 1.0, -1.0);
    // glVertex3f(1.0, 1.0, 1.0);
    // // Sisi kiri
    // glVertex3f(-1.0, -1.0, 1.0);
    // glVertex3f(-1.0, -1.0, -1.0);
    // glVertex3f(-1.0, 1.0, -1.0);
    // glVertex3f(-1.0, 1.0, 1.0);
    // // Sisi atas
    // glVertex3f(-1.0, 1.0, 1.0);
    // glVertex3f(1.0, 1.0, 1.0);
    // glVertex3f(1.0, 1.0, -1.0);
    // glVertex3f(-1.0, 1.0, -1.0);
    // // Sisi bawah
    // glVertex3f(-1.0, -1.0, 1.0);
    // glVertex3f(1.0, -1.0, 1.0);
    // glVertex3f(1.0, -1.0, -1.0);
    // glVertex3f(-1.0, -1.0, -1.0);
    // glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float camX = r * cos(elevation) * cos(azimuth);
    float camZ = r * cos(elevation) * sin(azimuth);
    float camY = r * sin(elevation);

    gluLookAt(camX, camY, camZ,  // eye position
              0.0, 0.0, 0.0,      // look-at position
              0.0, 1.0, 0.0);     // up vector    // mulai menggambar
    drawCube();

    // selesai menggambar
    glutSwapBuffers();
}

void reshape(int width, int height) {
    // Mengatur viewport sesuai ukuran jendela baru
    glViewport(0, 0, width, height);

    // Memilih matriks proyeksi dan mengatur ulang
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Mengatur perspektif pandangan
    // gluOrtho2D(-2.5, 10, -1.0, 1.0);
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
}


void console(){
    if (key!=0)
    {
        if(__APPLE__){
            system("clear");
        } else {
            system("cls"); 
        }
        cout << "Speed     :" << v << endl;
        cout << "Azimuth   :" << azimuth << endl;
        cout << "Elevation :" << azimuth << endl;
    }
}

void update(int value) {
    // Meminta agar tampilan diupdate
    switch (key){
        case 100: azimuth = fmod(azimuth+vAng,RAD_E);
            break;
        case 101: elevation = fmod(elevation+vAng,RAD_E);
            break;
        case 102: azimuth = fmod(azimuth-vAng,RAD_E);
            break;
        case 103: elevation = fmod(elevation-vAng,RAD_E);
            break;
        case 61: r -= v;
            break;
        case 45: r += v;
            break;
        case '.':
            v += 0.001;
            vAng = v/r;
            break;
        case ',':
            if (v>0){
                v -= 0.001;
            } else {
                v = 0;
            }
            vAng = v/r;
            break;
    }
    // console();
    glutPostRedisplay();
    
    glutTimerFunc(16, update, 0); // Call update function every 16 milliseconds (about 60 frames per second)
}

void specialCallback(int _key, int x, int y) {
    key = (unsigned char)_key;
}

void keyCallback(unsigned char _key, int x, int y) {
    key = _key;
}

void specialUpCallback(int _key, int x, int y) {
    switch (_key){
        default:
            key = 0;
    }
}

void keyUpCallback(unsigned char _key, int x, int y) {
    switch (_key){
        default:
            key = 0;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("TA Makul Komputer Grafik");
    glutSpecialFunc(specialCallback);
    glutSpecialUpFunc(specialUpCallback);
    glutKeyboardFunc(keyCallback);
    glutKeyboardUpFunc(keyUpCallback);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    update(0);
    glutMainLoop();
    return 0;
}