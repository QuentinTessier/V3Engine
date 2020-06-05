/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** xcb
*/

#pragma once

#include <xcb/xcb.h>
#include "../V3Window.h"

typedef struct xcb_window XCBWindow;

struct xcb_window {
    V3Window parent;

    /** PRIVATE **/

    xcb_connection_t *connect;
    xcb_screen_t *screen;
    xcb_window_t win;
    xcb_atom_t wmDeleteWin;

    /** ------- **/
};

int XCBWindow_create(XCBWindow *self, char const *name, unsigned int width, unsigned int height);
int XCBWindow_destroy(XCBWindow *self);