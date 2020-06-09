#pragma once

#include "V3Event.h"

typedef struct window V3Window;

/**
 * @brief Structure used to store cross-platform data for the window
 */
struct window {
    int run;
    uint32_t size[2];
    uint32_t position[2];
};

/**
 * @brief Allocate memory for a new window
 *
 * @return Returns a valid pointer to a V3Window or NULL
 */
V3Window *V3Window_allocate();

/**
 * @brief Create and initialize the window
 *
 * @param self - The V3Window pointer
 * @param name - The name of the V3Window
 * @param width - The width of the V3Window
 * @param height - The height of the V3Window
 *
 * @return Returns a boolean, true = success, false = failure
 */
int V3Window_create(V3Window *self, char const *name, unsigned int width, unsigned int height);

/**
 * @brief Destroy the V3Window
 *
 * @param self - The V3Window pointer
 *
 * @return Returns 1
 */
int V3Window_destroy(V3Window *self);

/**
 * @brief Check if the window is open
 *
 * @param self - The V3Window pointer
 *
 * @return Returns a boolean
 */
int V3Window_isOpen(V3Window *self);

/**
 * @brief Close the V3Window
 *
 * @param self - The V3Window pointer
 *
 * @return Returns 1
 */
int V3Window_close(V3Window *self);

/**
 * @brief Poll the lastest event (doesn't block)
 *
 * @param self - The V3Window pointer
 * @param event - Pointer to a V3Event which the function will fill with data
 *
 */
void V3Window_pollEvent(V3Window *self, V3Event *event);