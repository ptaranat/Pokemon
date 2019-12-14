#ifndef ATTACK_H
#define ATTACK_H

#include <string>

struct Attack {
  std::string name;
  std::string type;
  double damage;
  // TODO chance to hit
  Attack() {
    name = "attack";
    type = "type";
    damage = 0.0;
  }
  Attack(std::string in_name, std::string in_type, double dmg) {
    name = in_name;
    type = in_type;
    damage = dmg;
  }
};

#endif