#include "pencil.h"

Pencil::Pencil() : Point(1000) {}
Pencil::Pencil(uint16_t pointDurability) : Point(pointDurability) {}

void Pencil::write(Paper& paper, const string text) {
  paper.text += text;
}

uint16_t Pencil::pointDurability() {
  return Point.durability();
}
