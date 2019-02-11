#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(uint16_t durability) {
  Durability = durability;
}

const uint16_t& Consumable::durability(){
  return Durability;
}
