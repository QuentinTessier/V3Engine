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

#elif __WIN32

#include "V3Win32/V3Win32.h"

#endif

V3Window *V3Window_allocate()
{
    #ifdef __linux__
        printf("V3Window_allocate( XCBWindow )\n");
        return malloc(sizeof(XCBWindow));
    #elif __WIN32
        printf("V3Window_allocate( XCBWindow )\n");
        return malloc(sizeof(Win32Window));
    #endif
    printf("No implementation\n");
    return 0;
}

int V3Window_create(V3Window *self, char const *name, unsigned int width, unsigned int height)
{
    if (self == 0)
        return 0;
    self->run = 1;
    self->size[0] = width;
    self->size[1] = height;
    self->position[0] = 0;
    self->position[1] = 0;
    #ifdef __linux__
        return XCBWindow_create((XCBWindow *)self, name, width, height);
    #elif __WIN32
        return Win32Window_create((Win32Window *)self, name, width, height);
    #endif
    printf("No implementation for your OS.\n");
    return 0;
}

int V3Window_destroy(V3Window *self)
{
    #ifdef __linux__
        return XCBWindow_destroy((XCBWindow *)self);
    #elif __WIN32
        return Win32Window_destroy((Win32Window *)self);
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
    #elif __WIN32
        Win32Window_pollEvent((Win32Window *)self, event);
    #endif
    return;
}