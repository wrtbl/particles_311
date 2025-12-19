#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include "ParticleSystem.h"

ParticleSystem* rainSystem;
float lastTime = 0.0f;

// Настройки тумана
void setupFog() {
    GLfloat fogColor[4] = { 0.6f, 0.6f, 0.7f, 1.0f };
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.03f);
    glHint(GL_FOG_HINT, GL_NICEST);
}

// Настройка освещения
void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientColor[] = { 0.3f, 0.3f, 0.35f, 1.0f };  // тусклый свет
    GLfloat diffuseColor[] = { 0.5f, 0.5f, 0.55f, 1.0f };
    GLfloat lightPos[] = { 0.0f, 10.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

// Рисуем землю
void drawGround() {
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.5f, 0.3f); // зелёно-серый цвет травы
    glBegin(GL_QUADS);
    glVertex3f(-20.0f, 0.0f, -20.0f);
    glVertex3f(20.0f, 0.0f, -20.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Камера
    gluLookAt(0,8,15,   // глаз
        0, 0, 0,    // центр
        0, 1, 0);   // вверх

    drawGround();        // земля
    rainSystem->render(); // дождь

    glutSwapBuffers();
}

void update() {
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = time - lastTime;
    lastTime = time;

    rainSystem->update(dt);
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Цвет фона (небо)
    glClearColor(0.6f, 0.6f, 0.7f, 1.0f);

    srand((unsigned)time(0));

    rainSystem = new ParticleSystem(8000); // много капель
    rainSystem->setEffect(EffectType::RAIN);

    setupFog();
    setupLighting();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rain Scene");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}
