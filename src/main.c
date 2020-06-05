#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "window/V3Window.h"

int main(int ac, char * const *av)
{
    V3Window *win = V3Window_allocate();
    V3Window_create(win, "MyWindow", 1280, 768);

    // Loop

    V3Window_destroy(win);
    free(win);
    return 0;
}