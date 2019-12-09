#include "BattleArena.h"

BattleArena::BattleArena() {
  display_code = 'A';
  pokemon_count = 0;
  max_num_rivals = 3;
  num_rivals_remaining = max_num_rivals;
  dollar_cost_per_fight = 4;
  stamina_cost_per_fight = 3;
  state = RIVALS_AVAILABLE;
  std::cout << "BattleArena default constructed.\n";
}

BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost,
                         double dollar_cost, int in_id, Point2D in_loc) {
  display_code = 'A';
  id_num = in_id;
  location = in_loc;
  max_num_rivals = max_rivals;
  num_rivals_remaining = max_num_rivals;
  dollar_cost_per_fight = dollar_cost;
  stamina_cost_per_fight = stamina_cost;
  state = RIVALS_AVAILABLE;
  std::cout << "BattleArena constructed.\n";
}

bool BattleArena::IsAbleToFight(double budget, unsigned int stamina) {
  if ((budget - GetDollarCost() >= 0) && (stamina - GetStaminaCost() >= 0)) {
    return true;
  } else {
    return false;
  }
}

bool BattleArena::HasEnoughRivals() {
  if (num_rivals_remaining > 0)
    return true;
  else
    return false;
}

bool BattleArena::IsBeaten() {
  if (num_rivals_remaining == 0)
    return true;
  else
    return false;
}

bool BattleArena::Update() {
  if (IsBeaten() && state == RIVALS_AVAILABLE) {
    state = NO_RIVALS_AVAILABLE;
    display_code = 'a';
    std::cout << display_code << id_num << " has been beaten.\n";
    return true;
  } else {
    return false;
  }
}

void BattleArena::ShowStatus() {
  std::cout << "Battle Arena Status: ";
  Building::ShowStatus();
  std::cout << "\tStamina cost per fight: " << stamina_cost_per_fight << '\n'
            << "\tPokemon dollar cost per fight: " << dollar_cost_per_fight
            << '\n' << '\t' << num_rivals_remaining
            << " rival(s) are remaining for this arena\n";
}
void BattleArena::RemoveOneRival() {
  num_rivals_remaining -= 1;
}