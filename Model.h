#ifndef MODEL_H
#define MODEL_H

#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "BattleArena.h"
#include "View.h"
// PA4 Step 2
#include "list"

class Model {
 private:
  int time;
  // PA4 replaced with linkedlist
  std::list<GameObject*> object_ptrs;
  std::list<GameObject*> active_ptrs;
  std::list<Pokemon*> pokemon_ptrs;
  std::list<PokemonCenter*> center_ptrs;
  std::list<PokemonGym*> gym_ptrs;
  std::list<Rival*> rival_ptrs;
  std::list<BattleArena*> arena_ptrs;

 public:
  Model();
  ~Model();
  Pokemon* GetPokemonPtr(int id);
  PokemonCenter* GetPokemonCenterPtr(int id);
  PokemonGym* GetPokemonGymPtr(int id);
  BattleArena* GetBattleArenaPtr(int id);
  Rival* GetRivalPtr(int id);
  bool Update();
  void Display(View& view);
  void ShowStatus();
};
#endif