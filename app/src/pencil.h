#ifndef __PENCIL_H_
#define __PENCIL_H_

#include <stdint.h>
#include <string>

#include "paper.h"

using namespace std;

class Consumable {
  private:
    uint16_t durability;
    uint16_t length;
};

class Pencil {
  private:
    Consumable point;
    Consumable eraser;

  public:
    void write(Paper& paper, const string text);
};

#endif // __PENCIL_H_
