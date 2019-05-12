/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

void error_display(char *fmt, ...)
{
    va_list ap;
    va_list cpy;

    va_start(ap, fmt);
    while (1) {
        printf("\nError.\n");
        va_copy(cpy, ap);
        vprintf(fmt, cpy);
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
