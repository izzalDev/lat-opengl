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
float azimuth = 0;
float elevation = 0;
char key = -1;
float vAng = v/r;

float randf() {
    return static_cast<float>(rand()) / RAND_MAX;
}

void drawSide(float px, float py, float pz, float sx, float sy, float sz){
    glBegin(GL_QUADS);    //segiempat depan kamera               
    glVertex3f(px+sx,py+sy,0); //'kanan atas
    glVertex3f(px+sx,py-sy,0);//'kanan bawah 
    glVertex3f(px-sx,py-sy,0); //'kiri bawah 
    glVertex3f(px-sx,py+sy,0); //'kiri atas
    glEnd();
}

void drawCube(float px, float py, float pz, float sx, float sy, float sz) {
    float sx2 = sx/2;
    float sy2 = sy/2;
    float sz2 = sz/2;
    glBegin(GL_QUADS);
    // //  depan
    glColor3f(randf(),randf(),randf());
    glVertex3f(px+sx2,py+sy2,pz+sz2); //'kanan atas
    glVertex3f(px+sx2,py-sy2,pz+sz2);//'kanan bawah 
    glVertex3f(px-sx2,py-sy2,pz+sz2); //'kiri bawah 
    glVertex3f(px-sx2,py+sy2,pz+sz2); //'kiri atas
    // belakang
    glColor3f(randf(),randf(),randf());
    glVertex3f(px+sx2,py+sy2,pz-sz2); //'kanan atas
    glVertex3f(px+sx2,py-sy2,pz-sz2);//'kanan bawah 
    glVertex3f(px-sx2,py-sy2,pz-sz2); //'kiri bawah 
    glVertex3f(px-sx2,py+sy2,pz-sz2); //'kiri atas
    // kiri
    glColor3f(randf(),randf(),randf());
    glVertex3f(px-sx2,py+sy2,pz+sz2); //'kanan atas
    glVertex3f(px-sx2,py-sy2,pz+sz2);//'kanan bawah 
    glVertex3f(px-sx2,py-sy2,pz-sz2); //'kiri bawah 
    glVertex3f(px-sx2,py+sy2,pz-sz2); //'kiri atas
    // kanan
    glColor3f(randf(),randf(),randf());
    glVertex3f(px+sx2,py+sy2,pz+sz2); //'kanan atas
    glVertex3f(px+sx2,py-sy2,pz+sz2);//'kanan bawah 
    glVertex3f(px+sx2,py-sy2,pz-sz2); //'kiri bawah 
    glVertex3f(px+sx2,py+sy2,pz-sz2); //'kiri atas
    // atas
    glColor3f(randf(),randf(),randf());
    glVertex3f(px+sx2,py+sy2,pz+sz2); //'kanan atas
    glVertex3f(px-sx2,py+sy2,pz+sz2);//'kanan bawah 
    glVertex3f(px-sx2,py+sy2,pz-sz2); //'kiri bawah 
    glVertex3f(px+sx2,py+sy2,pz-sz2); //'kiri atas
    // bawah
    glColor3f(randf(),randf(),randf());
    glVertex3f(px+sx2,py-sy2,pz+sz2); //'kanan atas
    glVertex3f(px-sx2,py-sy2,pz+sz2);//'kanan bawah 
    glVertex3f(px-sx2,py-sy2,pz-sz2); //'kiri bawah 
    glVertex3f(px+sx2,py-sy2,pz-sz2); //'kiri atas
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float camX = r * cos(elevation) * sin(azimuth);
    float camY = r * sin(elevation);
    float camZ = r * cos(elevation) * cos(azimuth);

    gluLookAt(camX, camY, camZ,  // eye position
              0.0, 0.0, 0.0,      // look-at position
              0.0, 1.0, 0.0);     // up vector    // mulai menggambar
    drawCube(0, 0.275, 0, 1.2, 0.05, 0.8);
    drawCube(-0.55, -0.025, 0.35, 0.1, 0.55, 0.1); //kaki depan kiri
    drawCube(0.55, -0.025, 0.35, 0.1, 0.55, 0.1); //kaki depan kanan
    drawCube(-0.55, -0.025, -0.35, 0.1, 0.55, 0.1); //kaki belakang kiri
    drawCube(0.55, -0.025, -0.35, 0.1, 0.55, 0.1); //kaki belakang kanan

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
        cout << "Elevation :" << elevation << endl;
    }
}

void update(int value) {
    // Meminta agar tampilan diupdate
    switch (key){
        case 100: azimuth = fmod(azimuth-vAng,RAD_E);
            break;
        case 101: elevation = fmod(elevation+vAng,RAD_E);
            break;
        case 102: azimuth = fmod(azimuth+vAng,RAD_E);
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
    console();
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
    glEnable(GL_DEPTH_TEST);
    update(0);
    glutMainLoop();
    return 0;
}