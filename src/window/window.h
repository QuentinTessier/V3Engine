/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** window
*/

#pragma once

/**
 * @brief Opaque data type for a window
 */
typedef void *WindowHandle;

// Linux code
#ifdef __linux__

#include <xcb/xcb.h>

/**
 * @brief Basic struct storing data for an xcb window
 */
typedef struct window_linux {
    xcb_connection_t *connect;
    xcb_screen_t *screen;
    xcb_window_t win;
    xcb_atom_t wmProtocols;
    xcb_atom_t wmDeleteWin;
    int run;
} WindowLinux;

/**
 * @brief Opens a xcb window
 *
 * @param self - Pointer to a WindowLinux
 * @param name - Name of the window
 * @param width - width of the window
 * @param height - height of the window
 *
 * @return Returns true on success and false on failure
 */
int Screen_WindowLinux_Create(WindowLinux *self, char const *name, int width, int height);

/**
 * @brief Destroys a xcb window
 *
 * @param self - Pointer to a WindowLinux
 *
 * @return Returns true
 */
int Screen_WindowLinux_Destroy(WindowLinux *self);

/**
 * @brief Check if the window is openned
 */
static inline int Screen_WindowLinux_isOpen(WindowLinux *self)
{
    return self->run;
}

/**
 * @brief Temporary function
 */
static inline xcb_generic_event_t *Screen_WindowLinux_pollEvent(WindowLinux *self)
{
    return xcb_poll_for_event(self->connect);
}

/**
 * @brief Close the window
 */
static inline int Screen_WindowLinux_Close(WindowLinux *self)
{
    self->run = 0;
    return 1;
}

#endif