#include "PokemonCenter.h"

// Default constructor initializes the member variables to these values:
// - display_code = 'C'
// - stamina_capacity = 100
// - num_stamina_points = stamina_capacity
// - dollar_cost_per_stamina_point = 5
// (int in_id, double stamina_cost, unsigned int stamina_cap, Point2D in_loc)
PokemonCenter::PokemonCenter() {
  display_code = 'C';
  state = STAMINA_POINTS_AVAILABLE;
  std::cout << "PokemonCenter default constructed.\n";
}
// Initializes the member variables to these values:
// - ID number = in_id
// - location = in_loc
// - dollar_cost_per_stamina_point = stamina_cost
// - stamina_capacity = stamina_cap
// The rest are default.
PokemonCenter::PokemonCenter(int in_id, double stamina_cost,
                             unsigned int stamina_cap, Point2D in_loc) {
  id_num = in_id;
  location = in_loc;
  dollar_cost_per_stamina_point = stamina_cost;
  stamina_capacity = stamina_cap;
  num_stamina_points_remaining = stamina_capacity;
  display_code = 'C';
  state = STAMINA_POINTS_AVAILABLE;
  std::cout << "PokemonCenter constructed.\n";
}
// Returns true if this PokemonCenter contains at least one stamina point.
// Returns false otherwise.
bool PokemonCenter::HasStaminaPoints() {
  if (GetNumStaminaPointsRemaining() >= 1) {
    return true;
  } else {
    return false;
  }
}
// Returns the number of stamina points remaining in this Pokemon Center.
unsigned int PokemonCenter::GetNumStaminaPointsRemaining() {
  return num_stamina_points_remaining;
}
// Returns true if this Pokemon can afford to purchase stamina_points with the
// given budget.
bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points,
                                           double budget) {
  if (budget - GetDollarCost(stamina_points) >= 0) {
    return true;
  } else {
    return false;
  }
}
// Returns the Pokemon dollar cost for the specified number of stamina points.
double PokemonCenter::GetDollarCost(unsigned int stamina_points) {
  return stamina_points * dollar_cost_per_stamina_point;
}
// if the amount num_stamina_points_remaining in the Pokemon Center is greater
// than or equal to points_needed, it subtracts points_needed from
// PokemonCenter’s amount and returns points_needed. If the amount of stamina
// points in the PokemonCenter is less, it returns the PokemonCenter’s current
// amount, and the PokemonCenter stamina amount is set to 0.
unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed) {
  if (GetNumStaminaPointsRemaining() >= points_needed) {
    num_stamina_points_remaining -= points_needed;
    return points_needed;
  } else {
    unsigned int temp = num_stamina_points_remaining;
    num_stamina_points_remaining = 0;
    return temp;
  }
}
// If the PokemonCenter has no stamina points remaining
// - Its state is set to NO_STAMINA_POINTS_AVAILABLE
// - display_code is changed to ‘c’
// - Prints PokemonCenter (id) has ran out of stamina points.
// - Returns true if stamina is depleted; returns false if it is not depleted.
bool PokemonCenter::Update() {
  if (HasStaminaPoints() == false &&
      state == STAMINA_POINTS_AVAILABLE) {
    state = NO_STAMINA_POINTS_AVAILABLE;
    display_code = 'c';
    std::cout << "PokemonCenter " << id_num
              << " has ran out of stamina points.\n";
    return true;
  } else {
    return false;
  }
}
// Prints out status of the object
void PokemonCenter::ShowStatus() {
  std::cout << "Pokemon Center Status: ";
  Building::ShowStatus();
  std::cout << "\tPokemon dollars per stamina point: "
            << dollar_cost_per_stamina_point << '\n'
            << "\thas " << num_stamina_points_remaining
            << " stamina point(s) remaining.\n";
}