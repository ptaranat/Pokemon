#ifndef POKEMONGYM_H
#define POKEMONGYM_H

#include "Building.h"

class PokemonGym : public Building {
  enum PokemonGymStates { NOT_BEATEN = 0, BEATEN = 1 };

 private:
  // The amount of training units remaining in the PokemonGym.
  unsigned int num_training_units_remaining;
  // Training unit capacity for this Pokemon Gym.
  unsigned int max_number_of_training_units;
  // Stamina cost for a single unit of training.
  unsigned int stamina_cost_per_training_unit;
  // Pokemon dollar cost for single unit of training.
  unsigned int dollar_cost_per_training_unit;
  // Amount of experience points gained for each completed training unit.
  unsigned int experience_points_per_training_unit;

 public:
  PokemonGym();
  PokemonGym(unsigned int max_training_units, unsigned int stamina_cost,
             double dollar_cost, unsigned int exp_points_per_unit, int in_id,
             Point2D in_loc);
  // Returns the cost of purchasing "unit_qty" training units.
  double GetDollarCost(unsigned int unit_qty);
  // Returns the amount of stamina required for "unit_qty" training units.
  unsigned int GetStaminaCost(unsigned int unit_qty);
  // Returns the number of training units remaining in this Pokemon Gym.
  unsigned int GetNumTrainingUnitsRemaining();
  // Returns true if a Pokemon with a given budget and stamina can request to
  // train unit_qty training units
  bool IsAbleToTrain(unsigned int unit_qty, double budget,
                     unsigned int stamina);
  // Subtracts training_units from num_training_units_remaining if this
  // PokemonGym has enough units. If the amount of units requested is greater
  // than the amount available at this gym, then num_training_units_remaining
  // will be used instead of training_units when calculating experience points.
  // Returns the number of experience points gained by completing the training
  // units
  unsigned int TrainPokemon(unsigned int training_units);
  // If the PokemonGym has zero training units remaining, set the state to
  // BEATEN and display_code to 'g'.
  bool Update();
  // Returns true if training units remaining is 0
  bool IsBeaten();
  // Prints out the status of the object by calling GameObject’s show status and
  // then the values of its member variables:
  void ShowStatus();
};

#endif