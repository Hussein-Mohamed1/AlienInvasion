//
// Created by youss on 3/30/2024.
//
#include "unit.h"

void unit::print() const {
    cout << "ID: " << ID << " type: " << type << " joinTime: " << joinTime << " health: "
              << health
              << " power: " << power << " attackCapacity: " << attackCapacity << " simPtr: " << simPtr;
}
