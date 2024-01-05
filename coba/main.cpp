#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

void drawCube() {
    // Menggambar kotak
    glBegin(GL_QUADS);
    // Sisi depan
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    // Sisi belakang
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    // Sisi kanan
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    // Sisi kiri
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    // Sisi atas
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    // Sisi bawah
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
}

void display() {
    // Membersihkan buffer warna dan depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Memilih matriks modelview dan mengatur ulang
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Mengatur posisi dan orientasi kamera menggunakan gluLookAt
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Gambar kotak
    drawCube();

    // Menukar buffer dalam double buffering
    glutSwapBuffers();
}

void reshape(int width, int height) {
    // Mengatur viewport sesuai ukuran jendela baru
    glViewport(0, 0, width, height);

    // Memilih matriks proyeksi dan mengatur ulang
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Mengatur perspektif pandangan
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
}

int main(int argc, char** argv) {
    // Inisialisasi GLUT
    glutInit(&argc, argv);

    // Mengatur mode tampilan
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Membuat jendela
    glutCreateWindow("Kotak dan Kamera dengan gluLookAt");

    // Menetapkan fungsi-fungsi callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Mengaktifkan uji kedalaman (depth test)
    glEnable(GL_DEPTH_TEST);

    // Memulai loop utama GLUT
    glutMainLoop();
    
    return 0;
}