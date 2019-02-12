#include "pencil.h"
#include <iostream>

/* Private */
bool Pencil::IsUppercase(const char singleChar) {
  return ((singleChar >= 'A') && (singleChar <= 'Z'));
}
bool Pencil::IsLowercase(const char singleChar) {
  return ((singleChar >= 'a') && (singleChar <= 'z'));
}
uint8_t Pencil::GetCharCost(const char singleChar) {
  if (IsUppercase(singleChar)) {
    return COST_UPPERCASE;
  }
  else if (IsLowercase(singleChar)) {
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

/*
### Assumption
- No clear spec on non-alphabetic chars; therefore no cost for other characters
  - Could assign a cost or restrict writing of non-alphabetic chars
*/
void Pencil::write(Paper& paper, const string text) {
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

/*
### Assumption
- It is unclear in the spec if editing costs point durability.
- It will be assumed that it does, but the conflict symbol `@` will not cost durability
*/
void Pencil::edit(Paper& paper, const string text, const uint16_t position) {
  for(string::size_type i = 0; i < text.size(); ++i) {
    char character = (IsLowercase(paper.text[position + i]) || IsLowercase(paper.text[position + i])) ? '@' : text[i];
    if (Point.consume(GetCharCost(character)) ) {
      paper.text[position + i] = character;
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
