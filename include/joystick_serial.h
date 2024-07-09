#ifndef JOYSTICK_SERIAL_H
#define JOYSTICK_SERIAL_H
#include <Arduino.h>

enum DIRECTION { LEFT, RIGHT, UP, DOWN, CENTER };

struct Stick {
  int left;
  int right;
  int up;
  int down;
};

class Joystick {
 private:
  Stick _define{};

 public:
  Joystick(Stick define);
  auto read() -> DIRECTION;
  ~Joystick();
};

inline Joystick::Joystick(Stick define) : _define(define) {
  pinMode(define.left, INPUT_PULLUP);
  pinMode(define.right, INPUT_PULLUP);
  pinMode(define.up, INPUT_PULLUP);
  pinMode(define.down, INPUT_PULLUP);
}

inline auto Joystick::read() -> DIRECTION {
  if (digitalRead(_define.left) == LOW) {
    return DIRECTION::LEFT;
  } else if (digitalRead(_define.right) == LOW) {
    return DIRECTION::RIGHT;
  } else if (digitalRead(_define.up) == LOW) {
    return DIRECTION::UP;
  } else if (digitalRead(_define.down) == LOW) {
    return DIRECTION::DOWN;
  }
  return DIRECTION::CENTER;
}

Joystick::~Joystick() {}

#endif