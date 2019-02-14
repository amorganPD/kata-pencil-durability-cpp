#ifndef __CONSUMABLE_H_
#define __CONSUMABLE_H_

#include <stdint.h>

using namespace std;

class Consumable {
  protected:
    uint16_t Durability;
    uint16_t Length;
  public:
    Consumable();
    Consumable(uint16_t durability);

    const uint16_t& length();
    bool consume(uint16_t);
};

class Renewable: public Consumable {
  public:
    Renewable();
    Renewable(uint16_t durability);
    uint16_t restoreLength();
};

#endif // __CONSUMABLE_H_
