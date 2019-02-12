#include "pencil.h"
#include <iostream>

/* Private */
uint8_t Pencil::GetCharCost(char singleChar) {
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

/* Public */
Pencil::Pencil() : Point(1000), Graphite(100), Eraser(100) {}
Pencil::Pencil(uint16_t pointDurability) : Point(pointDurability), Graphite(100), Eraser(100) {}
Pencil::Pencil(uint16_t pointDurability, uint16_t graphiteDurability) : Point(pointDurability), Graphite(graphiteDurability), Eraser(100) {}
Pencil::Pencil(uint16_t pointDurability, uint16_t graphiteDurability, uint16_t eraserDurability) : Point(pointDurability), Graphite(graphiteDurability), Eraser(eraserDurability) {}

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
    if (Point.consume(GetCharCost(character)) ) {
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

bool Pencil::erase(Paper& paper, const string text) {
  // get replacement
  string erasedText = text;  
  for(string::size_type i = text.size(); i > 0; --i) {
    if(Eraser.consume((text[i - 1] == ' ') ? 0 : 1)) {
      erasedText[i - 1] = ' ';
    }
  }

  // find word
  string::size_type position = string::npos;
  string::size_type foundPosition = 0;
  do {
    position = paper.text.find(text, foundPosition);
    foundPosition = position != string::npos ? position + 1 : foundPosition;
  } while(position != string::npos);

  // replace
  if (foundPosition != string::npos) {
    paper.text.replace(foundPosition - 1, erasedText.size(), erasedText);
    return true;
  }

  return false;
}

uint16_t Pencil::getTextCost(string text) {
  uint16_t stringCost = 0;
  for(string::size_type i = 0; i < text.size(); ++i) {
    char character = text[i];
    stringCost  = (uint16_t)(stringCost + GetCharCost(character));
  }
  return stringCost;
}
