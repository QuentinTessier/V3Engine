/*
** EPITECH PROJECT, 2020
** V3Engine
** File description:
** V3KeyCodes
*/

#pragma once

enum V3Keycode {
    V3_NONE          = 0,   // Undefined. (No event)
    V3_A             = 4,
    V3_B             = 5,
    V3_C             = 6,
    V3_D             = 7,
    V3_E             = 8,
    V3_F             = 9,
    V3_G             = 10,
    V3_H             = 11,
    V3_I             = 12,
    V3_J             = 13,
    V3_K             = 14,
    V3_L             = 15,
    V3_M             = 16,
    V3_N             = 17,
    V3_O             = 18,
    V3_P             = 19,
    V3_Q             = 20,
    V3_R             = 21,
    V3_S             = 22,
    V3_T             = 23,
    V3_U             = 24,
    V3_V             = 25,
    V3_W             = 26,
    V3_X             = 27,
    V3_Y             = 28,
    V3_Z             = 29,
    V3_1             = 30,  // 1 and !
    V3_2             = 31,  // 2 and @
    V3_3             = 32,  // 3 and #
    V3_4             = 33,  // 4 and $
    V3_5             = 34,  // 5 and %
    V3_6             = 35,  // 6 and ^
    V3_7             = 36,  // 7 and &
    V3_8             = 37,  // 8 and *
    V3_9             = 38,  // 9 and (
    V3_0             = 39,  // 0 and )
    V3_Enter         = 40,  // (Return)
    V3_Escape        = 41,
    V3_Delete        = 42,
    V3_Tab           = 43,
    V3_Space         = 44,
    V3_Minus         = 45,  // - and (underscore)
    V3_Equals        = 46,  // = and +
    V3_LeftBracket   = 47,  // [ and {
    V3_RightBracket  = 48,  // ] and }
    V3_Backslash     = 49,  // \ and |
 // V3_NonUSHash     = 50,  // # and ~
    V3_Semicolon     = 51,  // ; and :
    V3_Quote         = 52,  // ' and "
    V3_Grave         = 53,
    V3_Comma         = 54,  // , and <
    V3_Period        = 55,  // . and >
    V3_Slash         = 56,  // / and ?
    V3_CapsLock      = 57,
    V3_F1            = 58,
    V3_F2            = 59,
    V3_F3            = 60,
    V3_F4            = 61,
    V3_F5            = 62,
    V3_F6            = 63,
    V3_F7            = 64,
    V3_F8            = 65,
    V3_F9            = 66,
    V3_F10           = 67,
    V3_F11           = 68,
    V3_F12           = 69,
    V3_PrintScreen   = 70,
    V3_ScrollLock    = 71,
    V3_Pause         = 72,
    V3_Insert        = 73,
    V3_Home          = 74,
    V3_PageUp        = 75,
    V3_DeleteForward = 76,
    V3_End           = 77,
    V3_PageDown      = 78,
    V3_Right         = 79,  // Right arrow
    V3_Left          = 80,  // Left arrow
    V3_Down          = 81,  // Down arrow
    V3_Up            = 82,  // Up arrow
    V3_NumLock        = 83,
    V3_Divide         = 84,
    V3_Multiply       = 85,
    V3_Subtract       = 86,
    V3_Add            = 87,
    V3_Enter          = 88,
    V3_1              = 89,
    V3_2              = 90,
    V3_3              = 91,
    V3_4              = 92,
    V3_5              = 93,
    V3_6              = 94,
    V3_7              = 95,
    V3_8              = 96,
    V3_9              = 97,
    V3_0              = 98,
    V3_Point          = 99, // . and Del
    V3_Equals         = 103,
    V3_F13           = 104,
    V3_F14           = 105,
    V3_F15           = 106,
    V3_F16           = 107,
    V3_F17           = 108,
    V3_F18           = 109,
    V3_F19           = 110,
    V3_F20           = 111,
    V3_F21           = 112,
    V3_F22           = 113,
    V3_F23           = 114,
    V3_F24           = 115,
 // V3_Help          = 117,
    V3_Menu          = 118,
    V3_Mute          = 127,
    V3_VolumeUp      = 128,
    V3_VolumeDown    = 129,
    V3_LeftControl   = 224, // WARNING : Android has no Ctrl keys.
    V3_LeftShift     = 225,
    V3_LeftAlt       = 226,
    V3_LeftGUI       = 227,
    V3_RightControl  = 228,
    V3_RightShift    = 229, // WARNING : Win32 fails to send a WM_KEYUP message if both shift keys are pressed, and one released.
    V3_RightAlt      = 230,
    V3_RightGUI      = 231
};
// clang-format on