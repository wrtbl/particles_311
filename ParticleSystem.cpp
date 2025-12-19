#include "ParticleSystem.h"
#include <GL/glut.h>
#include <cstdlib>

ParticleSystem::ParticleSystem(int maxParticles)
    : maxParticles(maxParticles), currentEffect(EffectType::FIRE)
{
    particles.reserve(maxParticles);
}

void ParticleSystem::setEffect(EffectType type)
{
    currentEffect = type;
    particles.clear(); // очищаем старые частицы
}

void ParticleSystem::emitParticle()
{
    if (particles.size() >= maxParticles)
        return;

    Particle p;


        // ДОЖДЬ
        p.x = ((rand() % 200) - 100) / 10.0f;
        p.y = 8.0f + (rand() % 40) / 10.0f; 
        p.z = ((rand() % 200) - 100) / 10.0f;

        p.vx = ((rand() % 100) - 40) / 500.0f;
        p.vy = -5.0f - (rand() % 30) / 20.0f;
        p.vz = 0.0f;

        p.life = 0.8f;


    particles.push_back(p);
}

void ParticleSystem::update(float dt)
{
    int emitCount = rand() % 100 + 50; 

     for (int i = 0; i < emitCount; i++)
         emitParticle();

    for (auto it = particles.begin(); it != particles.end();)
    {
        it->x += it->vx * dt;
        it->y += it->vy * dt;
        it->z += it->vz * dt;

        it->life -= dt;

        if (it->life <= 0.0f || it->y < -2.0f)
            it = particles.erase(it);
        else
            ++it;
    }
}

void ParticleSystem::render()
{
    glBegin(GL_LINES);

    for (const auto& p : particles)
    {

        float blue = 0.85f + (rand() % 15) / 100.0f; 
        float green = 0.85f + (rand() % 10) / 100.0f;
        float red = 0.85f;                         

        glColor4f(red, green, blue, 1.0f); 

        glVertex3f(p.x, p.y, p.z);
        glVertex3f(p.x, p.y + 0.5f, p.z); 
    }

    glEnd();
}
