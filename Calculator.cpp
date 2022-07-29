#include <math.h>

#include "Calculator.h"

Calculator::Calculator()
  : m_currentOperand(0.0), m_previousOperand(0.0), m_decimalPointSet(false), m_numDecimalDigits(0), m_operator(MathOperator::NOT_SET) { 
}

void Calculator::setOperator(MathOperator op) {
  if (m_operator == MathOperator::NOT_SET) {
    // Es wurde bisher nur ein Operand eingegeben
    // Daher den aktuelle Operanden in den vorherigen Operanden verschieben,
    // damit eine weitere Zahl eingegeben werden kann
    m_previousOperand = m_currentOperand;
    m_currentOperand = 0.0;
    m_decimalPointSet = false;
    m_numDecimalDigits = 0;
  }
  m_operator = op;
}

void Calculator::addToCurrentOperand(float digit) {
  if (m_decimalPointSet) {
    // Ziffer als neue Nachkommastelle an die Zahl anfügen
    float decimalDigit = digit / pow(10, m_numDecimalDigits + 1);
    if (m_currentOperand < 0) {
      m_currentOperand = m_currentOperand - decimalDigit;
    } else {
      m_currentOperand = m_currentOperand + decimalDigit;
    }
    m_numDecimalDigits++;
  } else {
    // Ziffer hinten an die Zahl anfügen
    m_currentOperand = m_currentOperand * 10 + digit;
  }
}

void Calculator::negateCurrentOperand() {
  m_currentOperand = -m_currentOperand;
}

void Calculator::squareCurrentOperand() {
  m_currentOperand = m_currentOperand * m_currentOperand;
}

void Calculator::takeSquareRootOfCurrentOperand() {
  m_currentOperand = sqrt(m_currentOperand);
}

void Calculator::enableDecimalPoint() {
  m_decimalPointSet = true;
}

void Calculator::calculate() {
  const float zeroThreshold = 0.01;
  float result;

  switch (m_operator) {
    case MathOperator::ADD:
      result = m_previousOperand + m_currentOperand;
      break;
    case MathOperator::SUBTRACT:
      result = m_previousOperand - m_currentOperand;
      break;
    case MathOperator::MULTIPLY:
      result = m_previousOperand * m_currentOperand;
      break;
    case MathOperator::DIVIDE:
      // Genauer Vergleich mit 0 ist aufgrund von Ungenauigkeiten bei Fließkommazahlen nicht möglich
      if (fabs(m_previousOperand) < zeroThreshold) {
        // Berechnung sofort abbrechen, da eine Division durch 0 nicht möglich ist
        return;
      }
      result = m_previousOperand / m_currentOperand;
      break;
    case MathOperator::NOT_SET:
      // Nichts tun, falls noch kein Operator gesetzt wurde
      result = m_previousOperand;
      break;
  }

  m_currentOperand = result;
  m_decimalPointSet = false;
  m_numDecimalDigits = 0;
  m_operator = MathOperator::NOT_SET;
}

void Calculator::reset() {
  m_currentOperand = m_previousOperand = 0.0;
  m_decimalPointSet = false;
  m_numDecimalDigits = 0;
  m_operator = MathOperator::NOT_SET;
}

float Calculator::getCurrentOperand() {
  return m_currentOperand;
}

float Calculator::getPreviousOperand() {
  return m_previousOperand;
}

bool Calculator::isPreviousOperandPresent() {
  return m_operator != MathOperator::NOT_SET;
}

bool Calculator::isDecimalPointSet() {
  return m_decimalPointSet;
}

MathOperator Calculator::getOperator() {
  return m_operator;
}
