/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** window
*/

#pragma once

#include "V3Event.h"

typedef struct window V3Window;

struct window {
    int run;
    uint32_t size[2];
    uint32_t position[2];
};

V3Window *V3Window_allocate();
int V3Window_create(V3Window *self, char const *name, unsigned int width, unsigned int height);
int V3Window_destroy(V3Window *self);
int V3Window_isOpen(V3Window *self);
int V3Window_close(V3Window *self);
void V3Window_pollEvent(V3Window *self, V3Event *event);