/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** V3Event
*/

#pragma once

#include <maths/types.h>

typedef struct event V3Event;

enum V3EventTypes {
    V3EVENT_UNKNOWN,
    V3EVENT_NONE,
    V3EVENT_KEY_PRESSED,
    V3EVENT_KEY_RELEASED,
    V3EVENT_MOUSE_BUTTON_PRESSED,
    V3EVENT_MOUSE_BUTTON_RELEASED,
    V3EVENT_MOUSE_MOVE,
    V3EVENT_FOCUS,
    V3EVENT_CLOSE,
    V3EVENT_RESIZE,
    V3EVENT_MOVE,
};

/**
 * @brief Stores an event in a cross-plaform way
 */
struct event {
    int type;
    union {
        uint32_t detail;            // V3EVENT_UNKNOWN
        uint32_t key;               // V3EVENT_KEY_{PRESSED / RELEASED}
        struct {
            uint32_t id;
            uint32_t pos[2];
        } mouseButton;              // V3EVENT_MOUSE_BUTTON_{PRESSED / RELEASED}
        i8 asFocus;            // V3EVENT_FOCUS
        i32 vec[2];           // V3EVENT_{RESIZE / MOVE / MOUSE_MOVE}
    };
};