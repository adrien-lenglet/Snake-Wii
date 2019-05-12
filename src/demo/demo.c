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

void DrawScene  (Mtx view);
int  BuildLists (GXTexObj texture);
void SetLight   (Mtx view);

void demo_loop(demo_t *demo)
{
    (void)demo;
	guVector cam = {0.0F, 0.0F, 0.0F},
			up = {0.0F, 1.0F, 0.0F},
		  look = {0.0F, 0.0F, -1.0F};
	Mtx view; // view and perspective matrices
	Mtx44 perspective;

    //main_quest_start();
    world_load_map();
	guLookAt(view, &cam, &up, &look);
	f32 w = rmode->viWidth;
	f32 h = rmode->viHeight;
	//printf("That is a typical error msg, taking up to 4MB OF VRAM. Please note this has nothing to do with you, now you can reboot your system.");
	while(1) {
        printf("w: %f, h: %f\n", w, h);
        guPerspective(perspective, 40.0f, w /h , 0.1f, 1000.0f);
        GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);

		WPAD_ScanPads();
        PAD_ScanPads();
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) exit(0);

		u16 directions = PAD_ButtonsHeld(0);
        (void)directions;

        world_update();
		// draw things
		DrawScene(view);
        world_render();

		GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
		GX_SetAlphaUpdate(GX_TRUE);
		GX_SetColorUpdate(GX_TRUE);
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
