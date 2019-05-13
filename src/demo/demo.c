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
    _demo->world.player->trans.pos = dvec3_sub(_demo->world.player->trans.pos, dvec3_muls(cam_z, y_ratio));
    x = PAD_SubStickX(chan);
    y = PAD_SubStickY(chan);
    x_ratio = (abs(x) > 8) ? ((double)x / 128.0) : 0.0;
    y_ratio = (abs(y) > 8) ? ((double)y / 128.0) : 0.0;
    x_ratio *= 3.0;
    y_ratio *= 3.0;

    _demo->world.camera->trans.rot.x -= y_ratio * _demo->win.framelen;
    _demo->world.player->trans.rot.y += x_ratio * _demo->win.framelen;
    //printf("%x: %d, %d\n", directions, PAD_StickX(0), PAD_StickY(0));
}

void demo_loop(demo_t *demo)
{
    (void)demo;

    //main_quest_start();
    world_load_map();
    //printf("That is a typical error msg, taking up to 4MB OF VRAM. Please note this has nothing to do with you, now you can reboot your system.");
	while(1) {
        //guPerspective(perspective, 40.0f, w /h , 0.1f, 1000.0f);
        //GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);

		WPAD_ScanPads();
        PAD_ScanPads();
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
            exit(0);
		u16 directions = PAD_ButtonsHeld(0);
        if (directions & PAD_BUTTON_START)
            return;
        move(0);
        //_demo->world.player->trans.pos.z -= 0.1;

        world_update();
		// draw things
		DrawScene();
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
