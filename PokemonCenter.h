#ifndef POKEMONCENTER_H
#define POKEMONCENTER_H

#include "Building.h"

class PokemonCenter : public Building {
  enum PokemonCenterStates {
    STAMINA_POINTS_AVAILABLE    = 0,
    NO_STAMINA_POINTS_AVAILABLE = 1
  };

 private:
  // The maximum number of stamina points this Pokemon Center can hold.
  unsigned int stamina_capacity = 100;
  // The amount of stamina currently in this Pokemon Center, initially
  // stamina_capacity
  unsigned int num_stamina_points_remaining = stamina_capacity;
  // The per stamina point cost in Pokemon Dollars
  double dollar_cost_per_stamina_point = 5;

 public:
  // Default constructor initializes the member variables to these values:
  // - display_code = 'C'
  // - stamina_capacity = 100
  // - num_stamina_points = stamina_capacity
  // - dollar_cost_per_stamina_point = 5
  PokemonCenter();
  // Initializes the member variables to these values:
  // - ID number = in_id
  // - location = in_loc
  // - dollar_cost_per_stamina_point = stamina_cost
  // - stamina_capacity = stamina_cap
  // The rest are default.
  PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_cap,
                Point2D in_loc);
  // Returns true if this PokemonCenter contains at least one stamina point.
  // Returns false otherwise.
  bool HasStaminaPoints();
  // Returns the number of stamina points remaining in this Pokemon Center.
  unsigned int GetNumStaminaPointsRemaining();
  // Returns true if this Pokemon can afford to purchase stamina_points with the
  // given budget.
  bool CanAffordStaminaPoints(unsigned int stamina_points, double budget);
  // Returns the Pokemon dollar cost for the specified number of stamina points.
  double GetDollarCost(unsigned int stamina_points);
  // if the amount num_stamina_points_remaining in the Pokemon Center is greater
  // than or equal to points_needed, it subtracts points_needed from
  // PokemonCenter’s amount and returns points_needed. If the amount of stamina
  // points in the PokemonCenter is less, it returns the PokemonCenter’s current
  // amount, and the PokemonCenter stamina amount is set to 0.
  unsigned int DistributeStamina(unsigned int points_needed);
  // If the PokemonCenter has no stamina points remaining
  // - Its state is set to NO_STAMINA_POINTS_AVAILABLE
  // - display_code is changed to ‘c’
  // - Prints PokemonCenter (id) has ran out of stamina points.
  // - Returns true if stamina is depleted; returns false if it is not depleted.
  bool Update();
  // Prints out status of the object
  void ShowStatus();
};

#endif