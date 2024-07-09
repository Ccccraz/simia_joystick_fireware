#include <Arduino.h>
#include <FastLED.h>
#include <USB.h>

#include <cstring>

#include "joystick.h"

constexpr int num_leds{1};
constexpr int led_pin{21};
CRGB leds[num_leds];

struct DataFrame {
  byte header1{0xAB};
  byte header2{0xCD};
  byte data;
};

USBCDC USBSerial{};

simia::Stick define{.left = 1, .right = 2, .up = 3, .down = 4};

simia::Joystick joystick{define};

void setup() {
  FastLED.addLeds<NEOPIXEL, led_pin>(leds, num_leds);
  Serial.begin(9600);

  USB.begin();
  USBSerial.begin();
}

void loop() {
  auto result{joystick.read()};
  if (result != simia::DIRECTION::CENTER) {
    leds[0] = CRGB::White;
    FastLED.show();
    DataFrame data_frame{};
    byte buf[sizeof(data_frame)]{};
    data_frame.data = result;
    std::memcpy(buf, &data_frame, sizeof(data_frame));
    USBSerial.write(buf, sizeof(buf));
    leds[0] = CRGB::Black;
    FastLED.show();
  }

  delay(10);
}