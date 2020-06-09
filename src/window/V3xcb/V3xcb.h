/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** xcb
*/

#pragma once

#include <stdint.h>
#include <xcb/xcb.h>
#include <xkbcommon/xkbcommon.h>
#include "../V3Window.h"

typedef struct xcb_window XCBWindow;

struct xcb_window {
    V3Window parent;

    /** PRIVATE **/

    xcb_connection_t *connect;
    xcb_screen_t *screen;
    xcb_window_t win;
    xcb_atom_t wmDeleteWin;

    struct xkb_context *xkb_ctx;
    struct xkb_keymap *xkb_key_map;
    struct xkb_state *xkb_state;

    /** ------- **/
};

// From : https://github.com/renelindsay/Vulkan-WSIWindow
// Convert native EVDEV key-code to cross-platform USB HID code.
static const unsigned char EVDEV_TO_HID[256] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0, 41, 30, 31, 32, 33, 34, 35,
 36, 37, 38, 39, 45, 46, 42, 43, 20, 26,  8, 21, 23, 28, 24, 12,
 18, 19, 47, 48, 40,224,  4, 22,  7,  9, 10, 11, 13, 14, 15, 51,
 52, 53,225, 49, 29, 27,  6, 25,  5, 17, 16, 54, 55, 56,229, 85,
226, 44, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 83, 71, 95,
 96, 97, 86, 92, 93, 94, 87, 89, 90, 91, 98, 99,  0,  0,100, 68,
 69,  0,  0,  0,  0,  0,  0,  0, 88,228, 84, 70,230,  0, 74, 82,
 75, 80, 79, 77, 81, 78, 73, 76,  0,127,128,129,  0,103,  0, 72,
  0,  0,  0,  0,  0,227,231,118,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,104,
105,106,107,108,109,110,111,112,113,114,115,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

/**
 * @brief Create and initialize the window (with XCB functions)
 *
 * @param self - The XCBWindow pointer
 * @param name - The name of the V3Window
 * @param width - The width of the V3Window
 * @param height - The height of the V3Window
 *
 * @return Returns a boolean, true = success, false = failure
 */
int XCBWindow_create(XCBWindow *self, char const *name, unsigned int width, unsigned int height);

/**
 * @brief Destroy the XCBWindow
 *
 * @param self - The XCBWindow pointer
 *
 * @return Returns 1
 */
int XCBWindow_destroy(XCBWindow *self);

/**
 * @brief Poll the lastest event (doesn't block)
 *
 * @param self - The XCBWindow pointer
 * @param event - Pointer to a V3Event which the function will fill with data
 *
 */
void XCBWindow_pollEvent(XCBWindow *self, V3Event *v3_event);