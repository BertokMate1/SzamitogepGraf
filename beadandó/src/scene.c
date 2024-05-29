#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdlib.h>

void init_scene(Scene *scene)
{

    scene->game_over = false;

    srand(time(NULL)); // Initialize random seed

    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.25);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    load_model(&(scene->ground), "assets/models/ground.obj");
    scene->ground_texture_id = load_texture("assets/textures/grund.jpg");

    load_model(&(scene->cube), "assets/models/cube.obj");
    scene->cube_texture_id = load_texture("assets/textures/cube.jpg");

    load_model(&(scene->skybox), "assets/models/skybox.obj");
    scene->skybox_texture_id = load_texture("assets/textures/sky.jfif");

    scene->help_texture_id = load_texture("assets/textures/help.png");

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->light = 1.0f;

    scene->collected_cubes = 0;

    scene->showHelp = 1;

    scene->end_texture_id = load_texture("assets/textures/gameover.png");

    // Initialize cubes
    for (int i = 0; i < 10; ++i)
    {
        scene->cubes[i].x = ((float)rand() / RAND_MAX) * 16 - 8; // Random position between -8 and 8
        scene->cubes[i].y = ((float)rand() / RAND_MAX) * 16 - 8; // Random position between -8 and 8
        scene->cubes[i].collected = 0;
    }
}

void set_lighting(float x)
{
    float ambient_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diffuse_light[] = {x, x, x, 1.0f};
    float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    set_lighting(scene->light);
}

void render_scene(const Scene *scene)
{
    // ground
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->ground));
    glPopMatrix();

    // skybox
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->skybox));
    glPopMatrix();

    // cubes
    for (int i = 0; i < 10; ++i)
    {
        if (!scene->cubes[i].collected)
        {
            glPushMatrix();
            glTranslatef(scene->cubes[i].x, scene->cubes[i].y, 0.5);
            glScalef(0.5, 0.5, 0.5);
            glBindTexture(GL_TEXTURE_2D, scene->cube_texture_id);
            draw_model(&(scene->cube));
            glPopMatrix();
        }
    }

    if (scene->collected_cubes == 10)
    {
        help(scene->end_texture_id);
    }
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void help(GLuint texture)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}