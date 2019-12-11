#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"

class Pokemon : public GameObject {
  enum PokemonStates {
    STOPPED = 0,
    MOVING = 1,
    EXHAUSTED = 2,
    IN_GYM = 3,
    IN_CENTER = 4,
    MOVING_TO_GYM = 5,
    MOVING_TO_CENTER = 6,
    TRAINING_IN_GYM = 7,
    RECOVERING_STAMINA = 8,
    IN_ARENA = 9,
    MOVING_TO_ARENA = 10,
    BATTLE = 11,
    FAINTED = 12
  };

 public:
  Pokemon();
  Pokemon(char in_code);
  Pokemon(Point2D in_loc, int in_id);
  Pokemon(std::string in_name, double in_speed, double hp, double phys_dmg,
          double magic_dmg, double def, int in_id, char in_code,
          Point2D in_loc);
  ~Pokemon() { std::cout << "Pokemon destructed.\n"; };
  void StartMoving(Point2D dest);
  void StartMovingToCenter(PokemonCenter* center);
  void StartMovingToGym(PokemonGym* gym);
  void StartMovingToArena(BattleArena* arena);
  void StartTraining(unsigned int num_training_units);
  void StartRecoveringStamina(unsigned int num_stamina_points);
  void Stop();
  bool IsExhausted();
  bool ShouldBeVisible();
  void ShowStatus();
  bool Update();
  std::string GetName() { return this->name; }
  // PA4 Step 1
  bool IsAlive() {
    if (state == FAINTED)
      return false;
    else
      return true;
  }
  void TakeHit(double phys_dmg, double magic_dmg, double def);
  void ReadyBattle(Rival* in_target);
  bool StartBattle();
  // Move_list
  void SetMoves(std::vector<Attack> attacks) {
    for (int i = 0; i < attacks.size(); ++i) {
      move_list.insert({i, attacks[i]});
    }
  }
  void TakeHit(std::string type, double dmg);

 protected:
  bool UpdateLocation();
  void SetupDestination(Point2D dest);
  // PA4 Step 1
  double health = 20;
  double store_health = health;
  double physical_damage = 5;
  double magical_damage = 4;
  double defense = 15;  // Parry a percentage of attack received
  Rival* target = nullptr;
  bool is_in_arena = false;  // true if Pokemon inside area
  BattleArena* current_arena = nullptr;

 private:
  // The speed this object travels, expressed as distance per update time unit.
  double speed = 5;
  bool is_in_gym = false;
  bool is_in_center = false;
  unsigned int stamina = 20;
  unsigned int experience_points = 0;
  double pokemon_dollars = 0;
  unsigned int training_units_to_buy = 0;
  unsigned int stamina_points_to_buy = 0;
  std::string name;
  PokemonCenter* current_center = nullptr;
  PokemonGym* current_gym = nullptr;
  // This object's current destination coordinates in the real plane.
  Point2D destination;
  // The x and y amounts that the object will move on each time unit.
  Vector2D delta;
  // Movelist
  std::map<int, Attack> move_list;
};

double GetRandomAmountOfPokemonDollars();

#endif