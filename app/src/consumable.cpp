#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(uint16_t durability) {
  Durability = durability;
  Length = durability;
}

const uint16_t& Consumable::length(){
  return Length;
}

bool Consumable::Consume(uint16_t cost) {
  if (Length < cost) {
    Length = 0;
    return false;
  }
  else {
    Length = (uint16_t)(Length - cost);
  }
  return true;
}
