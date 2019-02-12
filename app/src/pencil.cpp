#include "pencil.h"

Pencil::Pencil() : Point(1000) {}
Pencil::Pencil(uint16_t pointDurability) : Point(pointDurability) {}

void Pencil::write(Paper& paper, const string text) {
  // loop through
  for(string::size_type i = 0; i < text.size(); ++i) {
    char character = text[i];
    if (Point.Consume(getCharCost(character)) ) {
      paper.text += character;
    }
    else {
      paper.text += " ";
    }
  }
}

uint16_t Pencil::pointDurability() {
  return Point.length();
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
