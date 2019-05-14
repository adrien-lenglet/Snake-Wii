/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void init_cam(demo_t *demo)
{
    demo->cam.ratiowh = (long double)demo->win.w / (long double)demo->win.h;
    demo->cam.fovw = M_PI / 2.0f;
    demo->cam.near = 1.0L;
    demo->cam.proj = PROJ_TYPE_PERSPECTIVE;
    demo->cam.pos = ivec3_init(0, 0, -10);
    demo->cam.r = ivec3_init(1, 0, 0);
    demo->cam.u = ivec3_init(0, 1, 0);
    demo->cam.f = ivec3_init(0, 0, 1);
    demo->cam.r_prev = demo->cam.r;
    demo->cam.u_prev = demo->cam.u;
    demo->cam.f_prev = demo->cam.f;
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
