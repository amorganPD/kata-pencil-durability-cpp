#include "pencil.h"

void Pencil::write(Paper& paper, const string text) {
  paper.text += text;
}
