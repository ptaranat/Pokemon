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
  if (dest == location) {
    std::cout << display_code << id_num << ": I'm already there. See?\n";
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhuasted. I may move but you cannot see me.\n";
  } else {
    state = MOVING;
    std::cout << display_code << id_num << ": On my way.\n";
  }
}
// Tells the Pokemon to start moving to a PokemonCenter.
void Pokemon::StartMovingToCenter(PokemonCenter* center) {
  current_center = center;
  SetupDestination(center->GetLocation());
  if (center->GetLocation() == location) {
    std::cout << display_code << id_num
              << ": I'm already at the Pokemon Center!\n";
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhuasted so I can't move to recover stamina...\n";
  } else {
    state = MOVING_TO_CENTER;
    std::cout << display_code << id_num << ": On my way to center "
              << center->GetId() << '\n';
  }
}
// Tells the Pokemon to start moving to a PokemonGym.
void Pokemon::StartMovingToGym(PokemonGym* gym) {
  current_gym = gym;
  SetupDestination(gym->GetLocation());
  if (gym->GetLocation() == location) {
    std::cout << display_code << id_num
              << ": I'm already at the Pokemon Gym!\n";
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhausted so I shouldn’t be going to the gym...\n";
  } else {
    state = MOVING_TO_GYM;
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
      std::cout << display_code << id_num
                << ": I can only recover stamina at a Pokemon Center!\n";
    }
    if (!(current_center->CanAffordStaminaPoints(num_stamina_points,
                                                 pokemon_dollars))) {
      std::cout << display_code << id_num
                << ": Not enough money to recover stamina.\n";
    }
    if (!(current_center->HasStaminaPoints())) {
      std::cout << display_code << id_num
                << ": Cannot recover! No stamina points remaining in this "
                   "Pokemon Center.\n";
    }
  }
}
// Tells this Pokemon to stop doing whatever it was doing.
void Pokemon::Stop() {
  state = STOPPED;
  std::cout << display_code << id_num << ": Stopping...\n";
}
// Returns true if stamina is 0.
bool Pokemon::IsExhausted() {
  if (stamina == 0) {
    return true;
  } else {
    return false;
  }
}
// Returns true if this Pokemon is NOT exhuasuted.
bool Pokemon::ShouldBeVisible() {
  if (!IsExhausted()) {
    return true;
  } else {
    return false;
  }
}
// Prints specific status information.
void Pokemon::ShowStatus() {
  std::cout << name << " status: ";
  GameObject::ShowStatus();
  std::cout << ' ';
  switch (state) {
    case STOPPED: {
      std::cout << "stopped\n";
      break;
    }
    case MOVING: {
      std::cout << "moving at a speed of " << speed << " to destination "
                << destination << " at each step of " << delta << '\n';
      break;
    }
    case MOVING_TO_CENTER: {
      std::cout << "heading to Pokemon Center " << current_center->GetId()
                << " at a speed of " << speed << " at each step of " << delta
                << '\n';
      break;
    }
    case MOVING_TO_GYM: {
      std::cout << "heading to Pokemon Gym " << current_gym->GetId()
                << " at a speed of " << speed << " at each step of " << delta
                << '\n';
      break;
    }
    case IN_CENTER: {
      std::cout << "inside Pokemon Center " << current_center->GetId() << '\n';
      break;
    }
    case IN_GYM: {
      std::cout << "inside Pokemon Gym " << current_gym->GetId() << '\n';
      break;
    }
    case TRAINING_IN_GYM: {
      std::cout << "training in Pokemon Gym " << current_gym->GetId() << '\n';
      break;
    }
    case RECOVERING_STAMINA: {
      std::cout << "recovering stamina in Pokemon Center "
                << current_center->GetId() << '\n';
      break;
    }
    default: {
      std::cout << "\tStamina: " << stamina << '\n'
                << "\tPokemon Dollars: " << pokemon_dollars << '\n'
                << "\tExperience Points: " << experience_points << '\n';
      break;
    }
  }
  std::cout << "\tStamina: " << stamina << '\n'
            << "\tPokemon Dollars: " << pokemon_dollars << '\n'
            << "\tExperience Points: " << experience_points << '\n';
}
// Updates depending on state.
bool Pokemon::Update() {
  switch (state) {
    case STOPPED: {
      return false;
    }
    case MOVING: {
      UpdateLocation();
      if (destination == location) {
        state = STOPPED;
        return true;
      }
      else {
        return false;
      }
    }
    case MOVING_TO_CENTER: {
      UpdateLocation();
      if (destination == location) {
        current_center->AddOnePokemon();
        state = IN_CENTER;
        return true;
      }
      else {
        return false;
      }
    }
    case MOVING_TO_GYM: {
      UpdateLocation();
      if (destination == location) {
        current_gym->AddOnePokemon();
        state = IN_GYM;
        return true;
      }
      else {
        return false;
      }
    }
    case IN_CENTER: {
      return false;
    }
    case IN_GYM: {
      return false;
    }
    case TRAINING_IN_GYM: {
      stamina -= current_gym->GetStaminaCost(training_units_to_buy);
      pokemon_dollars -= current_gym->GetDollarCost(training_units_to_buy);
      unsigned int exp_gained =
          current_gym->TrainPokemon(training_units_to_buy);
      experience_points += exp_gained;
      std::cout << "** " << name << " completed " << training_units_to_buy
                << " training unit(s)! **\n";
      std::cout << "** " << name << " gained " << exp_gained
                << " experienced point(s)! **\n";
      state = IN_GYM;
      return true;
    }
    case RECOVERING_STAMINA: {
      unsigned int stamina_gained =
          current_center->DistributeStamina(stamina_points_to_buy);
      stamina += stamina_gained;
      pokemon_dollars -= current_center->GetDollarCost(stamina_points_to_buy);
      std::cout << "** " << name << " recovered " << stamina_gained
                << " stamina point(s)! **\n";
      state = IN_CENTER;
      return true;
    }
    default: {
      std::cout << "\tStamina: " << stamina << '\n'
                << "\tPokemon Dollars: " << pokemon_dollars << '\n'
                << "\tExperience Points: " << experience_points << '\n';
      return false;
    }
  }
}

// Protected

// Updates object's location while it is moving.
bool Pokemon::UpdateLocation() {
  if (std::fabs(destination.x - location.x) <= std::fabs(delta.x) &&
      std::fabs(destination.y - location.y) <= std::fabs(delta.y)) {
    location = destination;
    std::cout << display_code << id_num << ": I'm there!\n";
    return true;
  } else {
    std::cout << display_code << id_num << ": step...\n";
    location = location + delta;
    return false;
  }
}
// Sets up the object to start moving to dest.
void Pokemon::SetupDestination(Point2D dest) {
  destination = dest;
  delta = (destination - location) *
          (speed / GetDistanceBetween(destination, location));
}

// Non-members

// Returns a random number between 0.0 and 2.0 inclusive.
double GetRandomAmountOfPokemonDollars() {
  double output =
      static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX / 2.0));
  return output;
}