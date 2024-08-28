#include <Arduino.h>
#include <USB.h>

#include "config.h"
#include "joystick.h"

simia::Stick define{.left = LeftPin, .right = RightPin, .up = UpPin, .down = DownPin};

#if Mode == 0
#include "Joystick_keyboard.h"
simia::JoystickKeyboard joystick{define};

#elif Mode == 1
#include "Joystick_keyboard.h"

simia::KeyboardDefine keyboard_define{.left = HID_KEY_A, .right = HID_KEY_D, .up = HID_KEY_W, .down = HID_KEY_S};
simia::JoystickKeyboard joystick{define, keyboard_define};

#elif Mode == 2
#include "Joystick_gamepad.h"

simia::JoystickGamepad joystick{define};

#elif Mode == 3
#include "Joystick_stick.h"

simia::JoystickStick joystick{define};
#endif // Mode

void setup()
{
    USB.begin();
    joystick.start();
}

void loop()
{
}