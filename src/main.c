#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "window/window.h"

int main(int ac, char * const *av)
{
    WindowLinux win;
    xcb_generic_event_t *event = 0;
    xcb_client_message_event_t *cm;

    Screen_WindowLinux_Create(&win, "Test", 150, 150);

    while (Screen_WindowLinux_isOpen(&win)) {
        if ((event = Screen_WindowLinux_pollEvent(&win))) {
            switch (event->response_type & ~0x80) {
                case XCB_KEY_PRESS:
                    printf("Keycode pressed: %d\n", ((xcb_key_press_event_t *)event)->detail);
                    break;
                case XCB_BUTTON_PRESS:
                    printf("Button pressed : %u\n", ((xcb_button_press_event_t *)event)->detail);
                    printf("X-Coord : %u\n", ((xcb_button_press_event_t *)event)->event_x);
                    printf("Y-Coord : %u\n", ((xcb_button_press_event_t *)event)->event_y);
                case XCB_CLIENT_MESSAGE:
                    printf("Closing window /\n");
                    cm = (xcb_client_message_event_t *)event;
                    if (cm->data.data32[0] == win.wmDeleteWin) {
                        printf("Closing window\n");
                        Screen_WindowLinux_Close(&win);
                    }
                    break;
                case XCB_EXPOSE:
                    break;
            }
            free(event);
            event = 0;
        }
    }
    Screen_WindowLinux_Destroy(&win);
    return 0;
}