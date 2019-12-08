#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "GameObject.h"

class Rival : public GameObject {
    enum RivalStates {
        ALIVE_RIVAL = 0,
        FAINTED_RIVAL = 1
    };
 protected:
  double health = 20;
  double physical_damage = 5;
  double magical_damage = 4;
  double defense = 15;
  bool is_in_arena() { return true; }
  BattleArena* current_arena;

 public:
  Rival(std::string name, double speed, double hp, double phys_dmg, double magic_dmg,
        double def, int in_id, Point2D in_loc)
      : GameObject(in_loc, in_id, 'R'){};
  void TakeHit(double phys_dmg, double magic_dmg, double def);
  double GetPhysDmg() {
      return physical_damage;
  }
  double GetMagicDmg() {
      return magical_damage;
  }
  double GetDefense() {
      return defense;
  }
  double GetHealth() {
      return health;
  }
  std::string GetName() {
      return this->name;
  }
  bool Update();
  void ShowStatus();
  bool isAlive() {
      if (health > 0) {
          return true;
      }
  }
  private:
  double speed;

    std::string name;
};

#endif