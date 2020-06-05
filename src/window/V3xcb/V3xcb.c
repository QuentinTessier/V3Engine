/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** xcb
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "V3xcb.h"

int XCBWindow_create(XCBWindow *self, char const *name, unsigned int width, unsigned int height)
{
    int screen_nbr = 0;
    uint32_t EventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t valueList[2] = { 0, 0 };
    xcb_screen_iterator_t ite;

    self->connect = xcb_connect(0, &screen_nbr);
    if (xcb_connection_has_error(self->connect))
        return 0;
    ite = xcb_setup_roots_iterator(xcb_get_setup(self->connect));
    for (int s = screen_nbr; s > 0; s--)
        xcb_screen_next(&ite);
    self->screen = ite.data;

    self->win = xcb_generate_id(self->connect);
    valueList[0] = self->screen->black_pixel;
    valueList[1] = XCB_EVENT_MASK_EXPOSURE |
                   XCB_EVENT_MASK_BUTTON_PRESS |
                   XCB_EVENT_MASK_KEY_PRESS;
    xcb_create_window(
        self->connect,
        XCB_COPY_FROM_PARENT,
        self->win,
        self->screen->root,
        0, 0,
        width, height,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        self->screen->root_visual,
        EventMask, valueList);

    xcb_change_property(
        self->connect,
        XCB_PROP_MODE_REPLACE,
        self->win,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        strlen(name),
        name);
    xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(self->connect, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *wmProtocolsReply = xcb_intern_atom_reply(self->connect, wmProtocolsCookie, 0);

    xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(self->connect, 0, 16, "WM_DELETE_WINDOW");
    xcb_intern_atom_reply_t *wmDeleteReply = xcb_intern_atom_reply(self->connect, wmDeleteCookie, 0);

    self->wmDeleteWin = wmDeleteReply->atom;
    xcb_change_property(self->connect, XCB_PROP_MODE_REPLACE, self->win,
        wmProtocolsReply->atom, 4, 32, 1, &wmDeleteReply->atom);
    free(wmDeleteReply);
    free(wmProtocolsReply);
    xcb_map_window(self->connect, self->win);
    xcb_flush(self->connect);
    printf("XCBWindow { \"%s\", (%u, %u) }\n", name, width, height);
    return 1;
}

int XCBWindow_destroy(XCBWindow *self)
{
    printf("XCBWindow { destroy }\n");
    xcb_destroy_window(self->connect, self->win);
    xcb_disconnect(self->connect);
    return 1;
}