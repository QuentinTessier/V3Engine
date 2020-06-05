/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** window
*/

#pragma once

typedef struct window V3Window;

struct window {
    int run;
};

V3Window *V3Window_allocate();
int V3Window_create(V3Window *self, char const *name, unsigned int width, unsigned int height);
int V3Window_destroy(V3Window *self);
int V3Window_isOpen(V3Window *self);
int V3Window_close(V3Window *self);