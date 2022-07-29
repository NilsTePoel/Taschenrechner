#include <LCDWIKI_GUI.h>

#include "CalculatorUI.h"

// Farben
const uint16_t colorBlack = 0x0000;
const uint16_t colorWhite = 0xFFFF;
const uint16_t colorGray  = 0x9492;
const uint16_t colorRed   = 0xF800;
const uint16_t colorCyan  = 0x07FF;
const uint16_t colorGreen = 0x5F48;

const uint8_t numRows = 5;
const uint8_t numCols = 4;

const Button buttons[numRows][numCols] = {
  { {'C', colorRed, Action::RESET }, {'S', colorCyan, Action::SQUARE }, {'R', colorCyan, Action::TAKE_SQUARE_ROOT }, {'+', colorCyan, Action::ADD } },
  { {'7', colorWhite, Action::SEVEN }, {'8', colorWhite, Action::EIGHT }, {'9', colorWhite, Action::NINE }, {'-', colorCyan, Action::SUBTRACT } },
  { {'4', colorWhite, Action::FOUR }, {'5', colorWhite, Action::FIVE }, {'6', colorWhite, Action::SIX }, {'x', colorCyan, Action::MULTIPLY } },
  { {'1', colorWhite, Action::ONE }, {'2', colorWhite, Action::TWO }, {'3', colorWhite, Action::THREE }, {'/', colorCyan, Action::DIVIDE } },
  { {'N', colorCyan, Action::NEGATE }, {'0', colorWhite, Action::ZERO }, {',', colorWhite, Action::ENABLE_DECIMAL_POINT }, {'=', colorCyan, Action::CALCULATE} }
  };

CalculatorUI::CalculatorUI(LCDWIKI_KBV &display, Input &input)
  : m_display(display), m_width(m_display.Get_Width()), m_height(m_display.Get_Height()),
    m_columnWidth(m_width / numCols), m_rowHeight(m_height / (numRows + 1)),
    m_input(input) {
}

void CalculatorUI::init() {
  initDisplay();
  drawLines();
  drawSymbols();
  drawOperandsAndOperator();
}

void CalculatorUI::initDisplay() {
  // Display initialisieren und leeren
  m_display.Init_LCD();
  m_display.Set_Rotation(0);
  m_display.Fill_Screen(colorBlack);

  // Textfarbe und -größe setzen
  m_display.Set_Text_Size(3);
  m_display.Set_Text_Back_colour(colorBlack);

  // Linienfarbe setzen
  m_display.Set_Draw_color(colorWhite);
}

void CalculatorUI::drawLines() {
  // Vertikale Trennlinien
  for (uint8_t col = 1; col < numCols; col++) {
    m_display.Draw_Fast_VLine(col * m_columnWidth, m_rowHeight, m_height - m_rowHeight - 1); 
  }

  // Horizontale Trennlinien
  for (uint8_t row = 1; row <= numRows; row++) {
    m_display.Draw_Fast_HLine(0, row * m_rowHeight, m_width - 1); 
  }
}

void CalculatorUI::drawSymbols() {
  int16_t columnCenterOffset = (m_columnWidth / 2) - 10;
  int16_t rowCenterOffset = (m_rowHeight / 2) + 10;

  for (uint8_t row = 0; row < numRows; row++) {
    for (uint8_t col = 0; col < numCols; col++) {
      int16_t x = col * m_columnWidth + columnCenterOffset;
      int16_t y = (row + 2) * m_rowHeight - rowCenterOffset;
      m_display.Draw_Char(x, y, buttons[row][col].symbol, buttons[row][col].color, colorBlack, 3, true);
    }
  }
}

void CalculatorUI::drawOperandsAndOperator() {
  // Aktueller Operand
  if (m_calculator.isDecimalPointSet()) {
    // In der Benutzeroberfläche soll erkennbar sein, dass man gerade die Nachkommastellen bearbeitet
    m_display.Set_Text_colour(colorGreen);
  } else {
    m_display.Set_Text_colour(colorWhite);
  }
  m_display.Set_Text_Size(4);
  m_display.Print_Number_Float(m_calculator.getCurrentOperand(), 2, 8, 40, ',', 13, ' ');

  m_display.Set_Text_colour(colorGray);
  m_display.Set_Text_Size(3);

  // Vorheriger Operand
  if (m_calculator.isPreviousOperandPresent()) {
    m_display.Print_Number_Float(m_calculator.getPreviousOperand(), 2, 55, 10, ',', 13, ' ');
  } else {
    // Veraltetes Ergebnis mit einem schwarzen Rechteck überdecken
    m_display.Set_Draw_color(colorBlack);
    m_display.Fill_Rectangle(0, 0, m_width - 1, 34);
    m_display.Set_Draw_color(colorWhite);
  }

  // Operator
  m_display.Print_String(operatorToString(m_calculator.getOperator()), 295, 10);
}

void CalculatorUI::loop() {
  m_input.checkForInput();

  // Wurde ein Knopf gedrückt?
  if (m_input.hasInput()) {
    // Gedrückten Knopf bestimmen
    Point pressedButton = m_input.getPressedPoint(numRows, numCols);

    // Entsprechende Aktion durchführen
    Action btn = buttons[pressedButton.row][pressedButton.col].action;

    switch (btn) {
      case Action::ZERO: m_calculator.addToCurrentOperand(0); break;
      case Action::ONE: m_calculator.addToCurrentOperand(1); break;
      case Action::TWO: m_calculator.addToCurrentOperand(2); break;
      case Action::THREE: m_calculator.addToCurrentOperand(3); break;
      case Action::FOUR: m_calculator.addToCurrentOperand(4); break;
      case Action::FIVE: m_calculator.addToCurrentOperand(5); break;
      case Action::SIX: m_calculator.addToCurrentOperand(6); break;
      case Action::SEVEN: m_calculator.addToCurrentOperand(7); break;
      case Action::EIGHT: m_calculator.addToCurrentOperand(8); break;
      case Action::NINE: m_calculator.addToCurrentOperand(9); break;
      case Action::ADD: m_calculator.setOperator(MathOperator::ADD); break;
      case Action::SUBTRACT: m_calculator.setOperator(MathOperator::SUBTRACT); break;
      case Action::MULTIPLY: m_calculator.setOperator(MathOperator::MULTIPLY); break;
      case Action::DIVIDE: m_calculator.setOperator(MathOperator::DIVIDE); break;
      case Action::NEGATE: m_calculator.negateCurrentOperand(); break;
      case Action::SQUARE: m_calculator.squareCurrentOperand(); break;
      case Action::TAKE_SQUARE_ROOT: m_calculator.takeSquareRootOfCurrentOperand(); break;
      case Action::ENABLE_DECIMAL_POINT: m_calculator.enableDecimalPoint(); break;
      case Action::CALCULATE: m_calculator.calculate(); break;
      case Action::RESET: m_calculator.reset(); break;
    }

    // Benutzeroberfläche aktualisieren
    drawOperandsAndOperator();
  }
}

const char* CalculatorUI::operatorToString(MathOperator op) const {
  switch (op) {
    case MathOperator::NOT_SET:
      return " ";
    case MathOperator::ADD:
      return "+";
    case MathOperator::SUBTRACT:
      return "-";
    case MathOperator::MULTIPLY:
      return "x";
    case MathOperator::DIVIDE:
      return "/";
  }

  return "";
}
