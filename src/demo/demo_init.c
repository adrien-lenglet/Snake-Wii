/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void snake_init(void)
{
    _demo->cam.pos = ivec3_init(0, 0, 0);
    _demo->cam.r = ivec3_init(1, 0, 0);
    _demo->cam.u = ivec3_init(0, 1, 0);
    _demo->cam.f = ivec3_init(0, 0, 1);
    _demo->cam.pos_prev = _demo->cam.pos;
    _demo->cam.r_prev = _demo->cam.r;
    _demo->cam.u_prev = _demo->cam.u;
    _demo->cam.f_prev = _demo->cam.f;
    _demo->cam.rot_anim = 0;
    _demo->cam.pos_anim = 0;
    _demo->cam.speed = 45;
    _demo->world.snake_cubes_start = 0;
    _demo->world.snake_cubes_count = 1;
    _demo->world.snake_cubes[0] = _demo->cam.pos;
}

void snake_spawn_target(void)
{
    ivec3 pos;
    entity3 *target = _demo->world.snake->sub.ent[CUBE_COUNT];
    dvec3 bias = dvec3_init(0.5, 0.5, 0.5);

    do
        pos = ivec3_init(rand() % CUBE_SIZE, rand() % CUBE_SIZE, rand() % CUBE_SIZE);
    while (!snake_is_pos_safe(pos));
    _demo->world.snake_target = pos;
    target->trans.pos = dvec3_sub(ivec3_dvec3(pos), bias);
    target->trans.scale = dvec3_init(2.0, 2.0, 2.0);
    entity3_set_render(target, 0, mesh_full_ref_bank_init(MESH_BANK_BOX), MATERIAL_BLOOD);
    entity3_trans_update(target);
}

static void init_cam(demo_t *demo)
{
    demo->cam.ratiowh = (long double)demo->win.w / (long double)demo->win.h;
    demo->cam.fovw = M_PI / 2.0f;
    demo->cam.near = 1.0L;
    demo->cam.proj = PROJ_TYPE_PERSPECTIVE;
    snake_init();
}

demo_t* demo_init(void)
{
    demo_t *res;

    res = malloc_safe(sizeof(demo_t));
    _demo = res;
    demo_init_win(res);
    init_cam(res);
    init();
    clocks_init(res);
    _dungeons.cur_origin = (dvec3){0, 0, 0};
    tex_init(res);
    iu_init(res);
    player_init(res);
    gl_gen(res);
    shader_init(res);
    material_init(res);
    mesh_bank_init();
    world_init(res);
    demo_update_cursor_visibility(res);
    sounds_init();
    return (res);
}

void demo_quit(demo_t *demo)
{
    world_quit(demo);
    mesh_bank_quit();
    shader_quit(demo);
    gl_delete(demo);
    iu_quit();
    tex_quit(demo);
    quit();
    //sfRenderWindow_destroy(demo->win.window);
    //sfClock_destroy(demo->win.frametime);
    clocks_quit(demo);
    slider_free();
    sounds_quit();
    free(demo);
}
