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
		//GX_CopyDisp(_demo->buf.frameBuffer[0],GX_TRUE);

		GX_DrawDone();

		VIDEO_SetNextFramebuffer(_demo->buf.frameBuffer[0]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
		//_demo->buf.fb ^= 1;
    }
}
