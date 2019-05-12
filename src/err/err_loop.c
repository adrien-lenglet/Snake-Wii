/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

void error_display(void)
{
    printf("\nError.\n");
    VIDEO_SetNextFramebuffer(_demo->buf.frameBuffer[0]);
    while (1) {
		VIDEO_Flush();
		VIDEO_WaitVSync();
    }
}
