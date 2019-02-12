#ifndef __PENCIL_H_
#define __PENCIL_H_

#include <stdint.h>
#include <string>

#include "paper.h"
#include "consumable.h"

using namespace std;

class Pencil {
  private:
    Consumable Point;
    Consumable Eraser;

  public:
    Pencil();
    Pencil(uint16_t pointDurability);

    void write(Paper&, const string);
    uint8_t getCharCost(char);

    uint16_t pointDurability();
};

enum CHARCOST {
  COST_NONE = 0,
  COST_LOWERCASE,
  COST_UPPERCASE
};

#endif // __PENCIL_H_
