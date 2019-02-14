#include "consumable.h"

Consumable::Consumable() {}
Consumable::Consumable(uint16_t durability) {
  Durability = durability;
  Length = durability;
}

const uint16_t& Consumable::length(){
  return Length;
}

bool Consumable::consume(uint16_t cost) {
  if (Length < cost) {
    Length = 0;
    return false;
  }
  else {
    Length = (uint16_t)(Length - cost);
  }
  return true;
}

/*
Renewable Class derived from Consumable
*/
uint16_t Renewable::restoreLength() {
  Length = Durability;
  return Length;
}

Renewable::Renewable() {}
Renewable::Renewable(uint16_t durability) {
  Durability = durability;
  Length = durability;
}
