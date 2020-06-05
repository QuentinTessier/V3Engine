/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** window_linux
*/

#include <stdio.h>
#include <stdlib.h>
#include "V3Window.h"

#ifdef __linux__

#include "V3xcb/V3xcb.h"

#endif

V3Window *V3Window_allocate()
{
    #ifdef __linux__
        printf("V3Window_allocate( XCBWindow )\n");
        return malloc(sizeof(XCBWindow));
    #endif
}

int V3Window_create(V3Window *self, char const *name, unsigned int width, unsigned int height)
{
    self->run = 1;
    self->size[0] = width;
    self->size[1] = height;
    self->position[0] = 0;
    self->position[1] = 0;
    #ifdef __linux__
        return XCBWindow_create((XCBWindow *)self, name, width, height);
    #endif
    printf("No implementation for your OS.\n");
    return 0;
}

int V3Window_destroy(V3Window *self)
{
    #ifdef __linux__
        return XCBWindow_destroy((XCBWindow *)self);
    #endif
    printf("No implementation for your OS.\n");
    return 0;
}

int V3Window_isOpen(V3Window *self)
{
    return self->run;
}

int V3Window_close(V3Window *self)
{
    self->run = 0;
    return 1;
}

void V3Window_pollEvent(V3Window *self, V3Event *event)
{
    #ifdef __linux__
        XCBWindow_pollEvent((XCBWindow *)self, event);
    #endif
    return;
}