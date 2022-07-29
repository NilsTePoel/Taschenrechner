#pragma once

#include <Arduino.h>
#include <LCDWIKI_KBV.h>

#include "Calculator.h"
#include "Input.h"

enum class Action {
  ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
  ADD, SUBTRACT, MULTIPLY, DIVIDE,
  NEGATE, SQUARE, TAKE_SQUARE_ROOT, ENABLE_DECIMAL_POINT, CALCULATE, RESET,
};

struct Button {
  char symbol;
  uint16_t color;
  Action action;
};

class CalculatorUI {
public:
  CalculatorUI(LCDWIKI_KBV &display, Input &input);

  void init();

  void loop();

private:
  Calculator m_calculator;

  LCDWIKI_KBV &m_display;
  const int16_t m_width, m_height;
  const int16_t m_columnWidth, m_rowHeight;

  Input &m_input;

  void initDisplay();
  void drawLines();
  void drawSymbols();
  void drawOperandsAndOperator();

  const char* operatorToString(MathOperator op) const;
};
