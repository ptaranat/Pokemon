#ifndef RIVAL_H
#define RIVAL_H

#include <string>
#include "BattleArena.h"

class Rival : public GameObject {
  enum RivalStates { ALIVE_RIVAL = 0, FAINTED_RIVAL = 1 };

 protected:
  double health = 20;
  double physical_damage = 5;
  double magical_damage = 4;
  double defense = 15;
  bool is_in_arena;
  BattleArena* current_arena = nullptr;

 public:
  Rival(BattleArena* arena, Point2D in_loc, int in_id);
  Rival(std::string name, double hp, double phys_dmg, double magic_dmg,
        double def, BattleArena* arena, int in_id, Point2D in_loc);
  ~Rival() { std::cout << "Rival destructed.\n"; };
  void TakeHit(double phys_dmg, double magic_dmg, double def);
  double GetPhysDmg() { return physical_damage; }
  double GetMagicDmg() { return magical_damage; }
  double GetDefense() { return defense; }
  double GetHealth() { return health; }
  std::string GetName() { return this->name; }
  bool Update();
  void ShowStatus();
  bool IsAlive() {
    if (health > 0)
      return true;
    else
      return false;
  }
  bool ShouldBeVisible();

 private:
  double speed;

  std::string name;
};

#endif