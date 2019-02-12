#include "pencil.h"

Pencil::Pencil() : Point(1000), Graphite(100) {}
Pencil::Pencil(uint16_t pointDurability) : Point(pointDurability) {}
Pencil::Pencil(uint16_t pointDurability, uint16_t graphiteDurability) : Point(pointDurability), Graphite(graphiteDurability) {}

uint16_t Pencil::pointDurability() {
  return Point.length();
}
uint16_t Pencil::graphiteDurability() {
  return Graphite.length();
}

void Pencil::write(Paper& paper, const string text) {
  // loop through
  for(string::size_type i = 0; i < text.size(); ++i) {
    char character = text[i];
    if (Point.consume(getCharCost(character)) ) {
      paper.text += character;
    }
    else {
      paper.text += " ";
    }
  }
}

uint16_t Pencil::sharpen() {
  if (Graphite.consume(1)) {
    Point.restoreLength();
  }
  return Graphite.length();
}

uint8_t Pencil::getCharCost(char singleChar) {
  if ((singleChar >= 'A') && (singleChar <= 'Z')) {
    return COST_UPPERCASE;
  }
  else if (singleChar >= 'a' && (singleChar) <= 'z') {
    return COST_LOWERCASE;
  }
  else {
    return 0;
  }
}

uint16_t Pencil::getStringCost(string text) {
  uint16_t stringCost = 0;
  for(string::size_type i = 0; i < text.size(); ++i) {
    char character = text[i];
    stringCost  = (uint16_t)(stringCost + getCharCost(character));
  }
  return stringCost;
}
