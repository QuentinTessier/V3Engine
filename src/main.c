#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "window/V3Window.h"

void test_math()
{
    vec_f32 v = vec_f32_(10.f, 10.f);

    char buffer[64] = {0};

    to_string_vec_f32(buffer, 63, 2, v);
    printf("%s\n", buffer);
}

int main(int ac, char * const *av)
{
    test_math();

    V3Window *win = V3Window_allocate();
    V3Window_create(win, "MyWindow", 1280, 768);
    vec_f32 v = {10.f, 10.f};
    vec_f32 res = vec_f32_add(v, v);

    while (V3Window_isOpen(win)) {
        V3Event e;
        memset(&e, 0, sizeof(V3Event));
        e.type = V3EVENT_NONE;
        V3Window_pollEvent(win, &e);
        if (e.type != V3EVENT_NONE) {
            if (e.type == V3EVENT_CLOSE)
                V3Window_close(win);
            else if (e.type == V3EVENT_MOUSE_MOVE) {
                printf("Mouse pos : %u %u\n", e.vec[0], e.vec[1]);
            } else if (e.type == V3EVENT_KEY_RELEASED)
                printf("Key : %d\n", e.key);
        }
    }

    V3Window_destroy(win);
    free(win);
    return 0;
}