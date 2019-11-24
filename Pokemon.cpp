#include "Pokemon.h"

// Public
Pokemon::Pokemon() : GameObject('P') {
  speed = 5;
  std::cout << "Pokemon default constructed.\n";
}
Pokemon::Pokemon(char in_code) : GameObject(in_code) {
  speed = 5;
  state = STOPPED;
  display_code = in_code;
}
Pokemon::Pokemon(std::string in_name, int in_id, char in_code,
                 unsigned int in_speed, Point2D in_loc)
    : GameObject(in_loc, in_id, in_code) {
  speed = in_speed;
  name = in_name;
  std::cout << "Pokemon constructed.\n";
}
// Tells the Pokemon to start moving.
void Pokemon::StartMoving(Point2D dest) {
  SetupDestination(dest);
  state = MOVING;
  if (dest == location) {
    std::cout << display_code << id_num << ": I'm already there. See?\n";
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhuasted. I may move but you cannot see me.\n";
  } else {
    std::cout << display_code << id_num << ": On my way.\n";
  }
}
// Tells the Pokemon to start moving to a PokemonCenter.
void Pokemon::StartMovingToCenter(PokemonCenter* center) {
  SetupDestination(center->GetLocation());
  state = MOVING_TO_CENTER;
  if (center->GetLocation() == location) {
    std::cout << display_code << id_num
              << ": I'm already at the Pokemon Center!\n";
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhuasted so I can't move to recover stamina...\n";
  } else {
    std::cout << display_code << id_num << ": On my way to center "
              << center->GetId() << '\n';
  }
}
// Tells the Pokemon to start moving to a PokemonGym.
void Pokemon::StartMovingToGym(PokemonGym* gym) {
  SetupDestination(gym->GetLocation());
  state = MOVING_TO_GYM;
  if (gym->GetLocation() == location) {
    std::cout << display_code << id_num
              << ": I'm already at the Pokemon Gym!\n";
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhausted so I shouldn’t be going to the gym...\n";
  } else {
    std::cout << display_code << id_num << ": On my way to gym " << gym->GetId()
              << '\n';
  }
}
// Utility function to find minimum of two unsigned ints
unsigned int Minimum(unsigned int x, unsigned int y) {
  return y ^ ((x ^ y) & -(x < y));
}

// Tells the Pokemon to start training (num_training_units) in a PokemonGym.
void Pokemon::StartTraining(unsigned int num_training_units) {
  // Pokemon can train
  if (!IsExhausted() && is_in_gym &&
      current_gym->IsAbleToTrain(num_training_units, pokemon_dollars,
                                 stamina) &&
      !(current_gym->IsBeaten())) {
    state = TRAINING_IN_GYM;
    std::cout << display_code << id_num << ": Started to train at Pokemon Gym "
              << current_gym << " with " << num_training_units
              << " training units.\n";
    training_units_to_buy = Minimum(
        num_training_units, current_gym->GetNumTrainingUnitsRemaining());
  } else {
    if (IsExhausted()) {
      std::cout << display_code << id_num
                << ": I am exhuasted so no more training for me...\n";
    }
    if (!is_in_gym) {
      std::cout << display_code << id_num
                << ": I can only train in a Pokemon Gym!\n";
    }
    if (!(current_gym->IsAbleToTrain(num_training_units, pokemon_dollars,
                                     stamina))) {
      std::cout << display_code << id_num
                << ": Not enough stamina and/or money for training.\n";
    }
    if (current_gym->IsBeaten()) {
      std::cout << display_code << id_num
                << ": Cannot train! This Pokemon Gym is already beaten!\n";
    }
  }
}
// Tells the Pokemon to start recovering at a PokemonCenter
void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points) {
  if (is_in_center &&
      current_center->CanAffordStaminaPoints(num_stamina_points,
                                             pokemon_dollars) &&
      current_center->HasStaminaPoints()) {
    state = RECOVERING_STAMINA;
    std::cout << display_code << id_num << ": Started recovering "
              << num_stamina_points << " stamina point(s) at Pokemon Center "
              << current_center->GetId() << ".\n";
  } else {
    if (!is_in_center) {
      std::cout << display_code << id_num << ": I can only recover stamina at a Pokemon Center!\n";
    }
    if (!(current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars))) {
      std::cout << display_code << id_num << ": Not enough money to recover stamina.\n";
    }
    if (!(current_center->HasStaminaPoints())) {
      std::cout << display_code << id_num << ": Cannot recover! No stamina points remaining in this Pokemon Center.\n";
    }
  }
}
void Pokemon::Stop() {}
bool Pokemon::IsExhausted() {}
bool Pokemon::ShouldBeVisible() {}
void Pokemon::ShowStatus() {}
bool Pokemon::Update() {}

// Protected
bool Pokemon::UpdateLocation() {}
void Pokemon::SetupDestination(Point2D dest) {}

double GetRandomAmountOfPokemonDollars() {}