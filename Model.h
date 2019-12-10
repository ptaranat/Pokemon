#ifndef MODEL_H
#define MODEL_H

#include <list>
#include "BattleArena.h"
#include "Input_Handling.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "View.h"

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
  void NewCommand(char type, int id, Point2D loc);
};
#endif