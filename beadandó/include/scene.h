#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Cube
{
    float x, y;
    bool collected;
} Cube;

typedef struct Scene
{
    Material material;

    Model ground;
    GLuint ground_texture_id;

    Model skybox;
    GLuint skybox_texture_id;

    Model cube;
    GLuint cube_texture_id;

    float light;

    GLuint help_texture_id;
    GLuint end_texture_id;

    int showHelp;
    int collected_cubes;

    Cube cubes[10];

    bool game_over;

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float x);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void help(GLuint texture);

#endif /* SCENE_H */
