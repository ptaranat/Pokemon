#include "PokemonGym.h"

PokemonGym::PokemonGym() {
  display_code = 'G';
  state = NOT_BEATEN;
  max_number_of_training_units = 10;
  num_training_units_remaining = max_number_of_training_units;
  stamina_cost_per_training_unit = 1;
  dollar_cost_per_training_unit = 1.0;
  experience_points_per_training_unit = 2;
  std::cout << "PokemonGym default constructed.\n";
}
PokemonGym::PokemonGym(unsigned int max_training_units,
                       unsigned int stamina_cost, double dollar_cost,
                       unsigned int exp_points_per_unit, int in_id,
                       Point2D in_loc) {
  id_num = in_id;
  max_number_of_training_units = max_training_units;
  num_training_units_remaining = max_number_of_training_units;
  stamina_cost_per_training_unit = stamina_cost;
  experience_points_per_training_unit = exp_points_per_unit;
  dollar_cost_per_training_unit = dollar_cost;
  display_code = 'G';
  state = NOT_BEATEN;
  std::cout << "PokemonGym constructed.\n";
}
// Returns the cost of purchasing "unit_qty" training units.
double PokemonGym::GetDollarCost(unsigned int unit_qty) {
  return dollar_cost_per_training_unit * unit_qty;
}
// Returns the amount of stamina required for "unit_qty" training units.
unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty) {
  return stamina_cost_per_training_unit * unit_qty;
}
// Returns the number of training units remaining in this Pokemon Gym.
unsigned int PokemonGym::GetNumTrainingUnitsRemaining() {
  return num_training_units_remaining;
}
// Returns true if a Pokemon with a given budget and stamina can request to
// train unit_qty training units
bool PokemonGym::IsAbleToTrain(unsigned int unit_qty, double budget,
                               unsigned int stamina) {
  if ((GetDollarCost(unit_qty) - budget >= 0) &&
      (GetStaminaCost(unit_qty) - stamina >= 0)) {
    return true;
  } else {
    return false;
  }
}
// Subtracts training_units from num_training_units_remaining if this
// PokemonGym has enough units. If the amount of units requested is greater
// than the amount available at this gym, then num_training_units_remaining
// will be used instead of training_units when calculating experience points.
// Returns the number of experience points gained by completing the training
// units
unsigned int PokemonGym::TrainPokemon(unsigned int training_units) {
  if (GetNumTrainingUnitsRemaining() >= training_units) {
    num_training_units_remaining -= training_units;
    return training_units * experience_points_per_training_unit;
  } else {
    unsigned int temp = num_training_units_remaining;
    num_training_units_remaining = 0;
    return temp * experience_points_per_training_unit;
  }
}
// If the PokemonGym has zero training units remaining, set the state to
// BEATEN and display_code to 'g'.
bool PokemonGym::Update() {
  if (GetNumTrainingUnitsRemaining() == 0 && state == NOT_BEATEN) {
    display_code = 'g';
    std::cout << display_code << id_num << " has been beaten.\n";
    return true;
  } else {
    return false;
  }
}
// Returns true if training units remaining is 0
bool PokemonGym::IsBeaten() {
  if (GetNumTrainingUnitsRemaining() == 0) {
    return true;
  } else {
    return false;
  }
}
// Prints out the status of the object by calling GameObject’s show status and
// then the values of its member variables:
void PokemonGym::ShowStatus() {
  std::cout << "Pokemon Gym Status: ";
  Building::ShowStatus();
  std::cout 
  << "Max number of training units: " << max_number_of_training_units << '\n'
  << "Stamina cost per training unit: " << stamina_cost_per_training_unit << '\n'
  << "Pokemon dollar per training unit: " << dollar_cost_per_training_unit << '\n'
  << "Experience point per training unit: " << experience_points_per_training_unit << '\n'
  << num_training_units_remaining << " training unit(s) are remaining in this gym.\n";
}