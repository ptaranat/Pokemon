#ifndef BATTLEARENA_H
#define BATTLEARENA_H

#include "Building.h"

class BattleArena : public Building {
  enum BattleArenaStates { RIVALS_AVAILABLE = 0, NO_RIVALS_AVAILABLE = 1 };

 private:
  unsigned int max_num_rivals;
  unsigned int num_rivals_remaining;
  double dollar_cost_per_fight;
  unsigned int stamina_cost_per_fight;
  unsigned int pokemon_count;

 public:
  BattleArena();
  BattleArena(Point2D in_loc, int in_id);
  ~BattleArena() { std::cout << "BattleArena destructed.\n"; };
  BattleArena(unsigned int max_rivals, unsigned int stamina_cost,
              double dollar_cost, int in_id, Point2D in_loc);
  unsigned int GetNumRivalsRemaining() { return num_rivals_remaining; }
  bool HasEnoughRivals();
  double GetDollarCost() { return dollar_cost_per_fight; }
  unsigned int GetStaminaCost() { return stamina_cost_per_fight; }
  bool IsAbleToFight(double budget, unsigned int stamina);
  bool Update();
  bool IsBeaten();
  void ShowStatus();
  void RemoveOneRival();
  void AddOneRival();
};

#endif