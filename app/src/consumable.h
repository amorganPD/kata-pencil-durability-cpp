#ifndef __CONSUMABLE_H_
#define __CONSUMABLE_H_

#include <stdint.h>

using namespace std;

class Consumable {
  private:
    uint16_t Durability;
    uint16_t Length;
  public:
    Consumable();
    Consumable(uint16_t durability);

    const uint16_t& durability();
};

#endif // __CONSUMABLE_H_
