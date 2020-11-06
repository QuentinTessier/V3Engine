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

int XCBWindow_create(XCBWindow *self, char const *name, u32 width, u32 height)
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
    valueList[1] = XCB_EVENT_MASK_KEY_PRESS |
                   XCB_EVENT_MASK_KEY_RELEASE |
                   XCB_EVENT_MASK_BUTTON_PRESS |
                   XCB_EVENT_MASK_BUTTON_RELEASE |
                   XCB_EVENT_MASK_POINTER_MOTION |
                   XCB_EVENT_MASK_BUTTON_MOTION |
                   XCB_EVENT_MASK_STRUCTURE_NOTIFY |
                   XCB_EVENT_MASK_FOCUS_CHANGE;
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

    // -- Keyboard

        self->xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);

        self->xkb_key_map = xkb_keymap_new_from_names(self->xkb_ctx, 0, XKB_KEYMAP_COMPILE_NO_FLAGS);

        self->xkb_state = xkb_state_new(self->xkb_key_map);

    //

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
    free(self->xkb_ctx);
    return 1;
}

static void XCBWindow_convertEvent(XCBWindow *self, xcb_generic_event_t *xcb_event, V3Event *v3_event)
{
    xcb_button_press_event_t *e = (xcb_button_press_event_t *)xcb_event;

    switch (xcb_event->response_type & ~0x80) {
        case XCB_MOTION_NOTIFY:
            v3_event->type = V3EVENT_MOUSE_MOVE;
            v3_event->vec[0] = e->event_x;
            v3_event->vec[1] = e->event_y;
            break;

        case XCB_BUTTON_PRESS:
            v3_event->type = V3EVENT_MOUSE_BUTTON_PRESSED;
            v3_event->mouseButton.id = e->detail;
            v3_event->mouseButton.pos[0] = e->event_x;
            v3_event->mouseButton.pos[1] = e->event_y;
            break;

        case XCB_BUTTON_RELEASE:
            v3_event->type = V3EVENT_MOUSE_BUTTON_RELEASED;
            v3_event->mouseButton.id = e->detail;
            v3_event->mouseButton.pos[0] = e->event_x;
            v3_event->mouseButton.pos[1] = e->event_y;
            break;

        case XCB_KEY_PRESS: {
                uint8_t keycode = EVDEV_TO_HID[e->detail];
                // xkb_state_key_get_utf8(self->xkb_state, e->detail, /* char buffer[4] */, sizeof(buffer)); // For text input (not handeled yet)
                xkb_state_update_key(self->xkb_state, e->detail, XKB_KEY_DOWN);
                v3_event->type = V3EVENT_KEY_PRESSED;
                v3_event->key = keycode;
            }
            break;
        case XCB_KEY_RELEASE: {
                uint8_t keycode = EVDEV_TO_HID[e->detail];
                xkb_state_update_key(self->xkb_state, e->detail, XKB_KEY_UP);
                v3_event->type = V3EVENT_KEY_RELEASED;
                v3_event->key = keycode;
            }
            break;
        case XCB_CLIENT_MESSAGE:
            if (((xcb_client_message_event_t *)xcb_event)->data.data32[0] == self->wmDeleteWin)
                v3_event->type = V3EVENT_CLOSE;
            break;
        case XCB_CONFIGURE_NOTIFY: {
                xcb_configure_notify_event_t *notify = (xcb_configure_notify_event_t *)xcb_event;
                if (notify->width != self->parent.size[0] || notify->height != self->parent.size[1]) {
                    v3_event->type = V3EVENT_RESIZE;
                    v3_event->vec[0] = notify->width;
                    v3_event->vec[1] = notify->height;
                } else if (notify->x != self->parent.position[0] || notify->y != self->parent.position[1]) {
                    v3_event->type = V3EVENT_MOVE;
                    v3_event->vec[0] = notify->x;
                    v3_event->vec[1] = notify->y;
                }
            }
            break;
        default:
            v3_event->type = V3EVENT_UNKNOWN;
            v3_event->detail = xcb_event->response_type & ~0x80;
            break;
    }
    return;
}

void XCBWindow_pollEvent(XCBWindow *self, V3Event *v3_event)
{
    xcb_generic_event_t *xcb_event = 0;

    xcb_event = xcb_poll_for_event(self->connect);
    while (xcb_event) {
        XCBWindow_convertEvent(self, xcb_event, v3_event);
        if (v3_event->type == V3EVENT_UNKNOWN)
            xcb_event = xcb_poll_for_event(self->connect);
        else
            return;
    }
    v3_event->type = V3EVENT_NONE;
    return;
}