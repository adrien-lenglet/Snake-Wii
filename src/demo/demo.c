/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

extern GXRModeObj *rmode;

extern u32 texture[1];   // Storage for one texture
extern void *boxList[5]; // Storage for the display lists
extern u32 boxSize[5];   // Real display list sizes
extern u32 xloop;        // Loop for x axis
extern u32 yloop;        // Loop for y axis

extern f32 xrot; // Rotates cube on the x axis
extern f32 yrot; // Rotates cube on the y axis

void DrawScene  ();
int  BuildLists (GXTexObj texture);
void SetLight   (Mtx view);

static void move(int chan)
{
    u16 directions = PAD_ButtonsHeld(chan);
    (void)directions;
    s8 x = PAD_StickX(chan), y = PAD_StickY(chan);
    dvec3 cam_x = dvec3_muls(dmat4_mul_dvec3(_demo->world.camera->trans.world_rot,
    dvec3_init(1.0, 0.0, 0.0)), _demo->win.framelen);
    dvec3 cam_z = dvec3_muls(dmat4_mul_dvec3(_demo->world.camera->trans.world_rot,
    dvec3_init(0.0, 0.0, 1.0)), _demo->win.framelen);
    double x_ratio = (abs(x) > 8) ? ((double)x / 128.0) : 0.0;
    double y_ratio = (abs(y) > 8) ? ((double)y / 128.0) : 0.0;
    x_ratio *= 10.0;
    y_ratio *= 10.0;

    _demo->world.player->trans.pos = dvec3_add(_demo->world.player->trans.pos, dvec3_muls(cam_x, x_ratio));
    _demo->world.player->trans.pos = dvec3_add(_demo->world.player->trans.pos, dvec3_muls(cam_z, y_ratio));
    x = PAD_SubStickX(chan);
    y = PAD_SubStickY(chan);
    x_ratio = (abs(x) > 8) ? ((double)x / 128.0) : 0.0;
    y_ratio = (abs(y) > 8) ? ((double)y / 128.0) : 0.0;
    x_ratio *= 3.0;
    y_ratio *= 3.0;

    _demo->world.camera->trans.rot.x += y_ratio * _demo->win.framelen;
    _demo->world.player->trans.rot.y -= x_ratio * _demo->win.framelen;
    //printf("%x: %d, %d\n", directions, PAD_StickX(0), PAD_StickY(0));
//_demo->world.player->trans.pos.z += 0.01;
}

static void snake_rot_anim(void)
{
    _demo->cam.r_prev = _demo->cam.r;
    _demo->cam.u_prev = _demo->cam.u;
    _demo->cam.f_prev = _demo->cam.f;
    _demo->cam.rot_anim = 0;
}

static void snake_pos_anim(void)
{
    _demo->cam.pos_prev = _demo->cam.pos;
    _demo->cam.pos_anim = 0;
}

int snake_is_pos_safe(ivec3 pos)
{
    if (!((pos.x >= 0) && (pos.x < CUBE_SIZE) &&
    (pos.y >= 0) && (pos.y < CUBE_SIZE) &&
    (pos.z >= 0) && (pos.z < CUBE_SIZE)))
        return 0;
    return !_demo->world.cube[pos.x][pos.y][pos.z];
}

static void rot_vec(ivec3 *a, ivec3 *b, int is_cw)
{
    ivec3 a_b = *a;
    ivec3 b_b = *b;

    snake_rot_anim();
    *a = ivec3_muls(b_b, is_cw ? 1 : -1);
    *b = ivec3_muls(a_b, is_cw ? -1 : 1);
    if (!snake_is_pos_safe(ivec3_add(_demo->cam.pos, _demo->cam.f))) {
        *a = a_b;
        *b = b_b;
    }
}

void snake_set_visible(ivec3 pos, int value)
{
    entity3 *part = _demo->world.snake->sub.ent[pos.z + pos.y * CUBE_SIZE + pos.x * CUBE_SIZE * CUBE_SIZE];

    if (value)
        entity3_set_render(part, 0, mesh_full_ref_bank_init(MESH_BANK_BOX), MATERIAL_GRASS);
    else
        entity3_set_render(part, 0, mesh_full_ref_get_null(), MATERIAL_MAX);
}

void snake_set(ivec3 pos, int value)
{
    snake_set_visible(pos, value);
    _demo->world.cube[pos.x][pos.y][pos.z] = value;
}

void snake_add_cube(ivec3 pos)
{
    _demo->world.snake_cubes[(_demo->world.snake_cubes_start + _demo->world.snake_cubes_count++) % CUBE_COUNT] = pos;
    snake_set(pos, 1);
}

void snake_remove_last_cube(void)
{
    ivec3 pos;

    pos = _demo->world.snake_cubes[(_demo->world.snake_cubes_start++) % CUBE_COUNT];
    _demo->world.snake_cubes_count--;
    snake_set(pos, 0);
}

void demo_loop(demo_t *demo)
{
    (void)demo;
    size_t frame = 0;
    u16 dir, dir_prev = 0;
    u16 dir_press;
    int do_stall = 0;

    //main_quest_start();
    world_load_map();
    //for (size_t i = 0; i < 32; i++)
        //snake_set(ivec3_init(rand() % CUBE_SIZE, rand() % CUBE_SIZE, rand() % CUBE_SIZE), 1);
    /*fatInitDefault();
    FILE *file = fopen("test.txt", "w+");
    fputs("XDDDDD\n", file);
    fclose(file);
    error_display("%p\n", file);*/
	while (1) {
		WPAD_ScanPads();
        PAD_ScanPads();
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
            exit(0);
        dir_prev = dir;
		dir = PAD_ButtonsHeld(0);
        dir_press = (~dir_prev) & dir;
        if (dir & PAD_BUTTON_START)
            return;
        if (dir_press & PAD_BUTTON_LEFT)
            rot_vec(&_demo->cam.f, &_demo->cam.r, 0);
        if (dir_press & PAD_BUTTON_RIGHT)
            rot_vec(&_demo->cam.f, &_demo->cam.r, 1);
        if (dir_press & PAD_BUTTON_UP)
            rot_vec(&_demo->cam.f, &_demo->cam.u, 1);
        if (dir_press & PAD_BUTTON_DOWN)
            rot_vec(&_demo->cam.f, &_demo->cam.u, 0);
        frame++;
        if (frame >= _demo->cam.speed) {
            snake_pos_anim();
            _demo->cam.pos = ivec3_add(_demo->cam.pos, _demo->cam.f);
            frame = 0;
            if (!snake_is_pos_safe(_demo->cam.pos)) {
                while (_demo->world.snake_cubes_count)
                    snake_remove_last_cube();
                snake_init();
            }
            snake_add_cube(_demo->cam.pos);
            if (do_stall)
                do_stall = 0;
            else
                snake_remove_last_cube();
            if (ivec3_eq(_demo->cam.pos, _demo->world.snake_target)) {
                snake_spawn_target();
                do_stall = 1;
                _demo->cam.speed--;
                if (_demo->cam.speed < 16)
                    _demo->cam.speed = 16;
            }
        }
        move(0);

        world_update();
        for (size_t i = 0; i < _demo->world.snake_cubes_count; i++)
            snake_set_visible(_demo->world.snake_cubes[(_demo->world.snake_cubes_start + i) % CUBE_COUNT], i < _demo->world.snake_cubes_count - 1);

        Mtx view;
        dmat4_Mtx(_demo->cam.mvp.view, view);
        // BUG: Light ignores underlying polygon colors.
        SetLight(view);
        world_render();

		GX_CopyDisp(_demo->buf.frameBuffer[_demo->buf.fb],GX_TRUE);

		GX_DrawDone();

		VIDEO_SetNextFramebuffer(_demo->buf.frameBuffer[_demo->buf.fb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
		_demo->buf.fb ^= 1;
	}
}

static void jukebox(int start)
{
    if (start) {
        play_new_sound(SOUNDS_FOREST, 1, 80);
        play_new_sound(SOUNDS_WATER, 1, 50);
    } else {
        stop_sound(SOUNDS_FOREST);
        stop_sound(SOUNDS_WATER);
    }
}

int demo(arg_t args, int mode_dev)
{
    demo_t *demo = demo_init();

    (void)args;
    _iu.data.mode_dev = mode_dev;
    /*if (!start(demo)) {
        demo_quit(demo);
        return 0;
    }*/
    jukebox(1);
    while (1) {
        demo_loop(demo);
        if (demo->win.do_reboot) {
            demo_quit(demo);
            demo = demo_init();
        } else
            break;
    }
    jukebox(0);
    demo_quit(demo);
    return (0);
}
