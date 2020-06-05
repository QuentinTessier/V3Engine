#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "window/V3Window.h"

int main(int ac, char * const *av)
{
    V3Window *win = V3Window_allocate();
    V3Window_create(win, "MyWindow", 1280, 768);

    while (V3Window_isOpen(win)) {
        V3Event e;
        V3Window_pollEvent(win, &e);
        if (e.type != V3EVENT_NONE) {
            if (e.type == V3EVENT_CLOSE)
                V3Window_close(win);
            else if (e.type == V3EVENT_MOUSE_MOVE) {
                printf("%u %u\n", e.vec[0], e.vec[1]);
            }
        }
    }

    V3Window_destroy(win);
    free(win);
    return 0;
}