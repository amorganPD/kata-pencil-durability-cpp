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
    Consumable Graphite;
    Consumable Eraser;

  public:
    Pencil();
    Pencil(uint16_t);
    Pencil(uint16_t, uint16_t);

    void write(Paper&, const string);
    uint16_t sharpen();
    uint8_t getCharCost(char);
    uint16_t getStringCost(string text);

    uint16_t pointDurability();
    uint16_t graphiteDurability();
};

enum CHARCOST {
  COST_NONE = 0,
  COST_LOWERCASE,
  COST_UPPERCASE
};

#endif // __PENCIL_H_
