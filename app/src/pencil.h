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
    bool IsUppercase(const char);
    bool IsLowercase(const char);
    uint8_t GetCharCost(char);

  public:
    Pencil();
    Pencil(uint16_t);
    Pencil(uint16_t, uint16_t);
    Pencil(uint16_t, uint16_t, uint16_t);

    void write(Paper&, const string);
    void edit(Paper&, const string, const uint16_t);

    uint16_t sharpen();
    bool erase(Paper&, const string);
    uint16_t getTextCost(string text);

    uint16_t pointDurability();
    uint16_t graphiteDurability();
};

enum CHARCOST {
  COST_NONE = 0,
  COST_LOWERCASE,
  COST_UPPERCASE
};

#endif // __PENCIL_H_
