#include "Pokemon.h"

#include <iomanip>
#include <limits>
#include <sstream>

// Public

Pokemon::Pokemon() : GameObject('P') {
  state = STOPPED;
  std::cout << "Pokemon default constructed.\n";
}
Pokemon::Pokemon(char in_code) : GameObject(in_code) {
  state = STOPPED;
  display_code = in_code;
}
Pokemon::Pokemon(Point2D in_loc, int in_id) : GameObject(in_loc, in_id, 'P') {
  std::ostringstream oss;
  oss << "Pokemon " << in_id;
  name = oss.str();
  state = STOPPED;
}
Pokemon::Pokemon(std::string in_name, double in_speed, double hp,
                 double phys_dmg, double magic_dmg, double def, int in_id,
                 char in_code, Point2D in_loc)
    : GameObject(in_loc, in_id, 'P') {
  name = in_name;
  speed = in_speed;
  state = STOPPED;
  health = hp;
  store_health = health;
  physical_damage = phys_dmg;
  magical_damage = magic_dmg;
  defense = def;
}
// Tells the Pokemon to start moving.
void Pokemon::StartMoving(Point2D dest) {
  SetupDestination(dest);
  if (dest == location) {
    std::cout << display_code << id_num << ": I'm already there. See?\n";
  }
  if (IsExhausted() == true) {
    std::cout << name << " is out of stamina and can't move.\n";
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
    if (is_in_center == false) {
      is_in_center = true;
      center->AddOnePokemon();
    }
    state = IN_CENTER;
    current_center = center;
    return;
  }
  if (IsExhausted()) {
    // Remove this @383
    // Game should end if exhausted in center
    /*
    if (is_in_center) {
      state = IN_CENTER;
      return;
    }
    */
    std::cout << display_code << id_num
              << ": I am exhausted so I can't move to recover stamina...\n";
    return;
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
    if (is_in_gym == false) {
      is_in_gym = true;
      gym->AddOnePokemon();
    }
    state = IN_GYM;
    current_gym = gym;
    return;
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhausted so I shouldn't be going to the gym...\n";
    return;
  } else {
    state = MOVING_TO_GYM;
    std::cout << display_code << id_num << ": On my way to gym " << gym->GetId()
              << '\n';
  }
}
void Pokemon::StartMovingToArena(BattleArena* arena) {
  current_arena = arena;
  SetupDestination(arena->GetLocation());
  if (arena->GetLocation() == location) {
    std::cout << display_code << id_num
              << ": I'm already at the Battle Arena!\n";
    if (is_in_arena == false) {
      is_in_arena = true;
      arena->AddOnePokemon();
    }
    state = IN_ARENA;
    current_arena = arena;
    return;
  }
  if (IsExhausted()) {
    std::cout << display_code << id_num
              << ": I am exhausted so I shouldn't be going to the arena...\n";
    return;
  } else {
    state = MOVING_TO_ARENA;
    std::cout << display_code << id_num << ": On my way to arena "
              << arena->GetId() << '\n';
  }
}
// Utility function to find minimum of two unsigned ints
unsigned int Minimum(unsigned int x, unsigned int y) {
  return y ^ ((x ^ y) & -(x < y));
}

// Tells the Pokemon to start training (num_training_units) in a PokemonGym.
void Pokemon::StartTraining(unsigned int num_training_units) {
  // Pokemon can train
  if (IsExhausted() == false && is_in_gym &&
      current_gym->IsAbleToTrain(num_training_units, pokemon_dollars,
                                 stamina) &&
      current_gym->IsBeaten() == false) {
    state = TRAINING_IN_GYM;
    training_units_to_buy = num_training_units;
    std::cout << display_code << id_num << ": Started to train at Pokemon Gym "
              << current_gym->GetId() << " with " << num_training_units
              << " training units.\n";
    training_units_to_buy = Minimum(
        num_training_units, current_gym->GetNumTrainingUnitsRemaining());
  } else {
    if (IsExhausted()) {
      std::cout << display_code << id_num
                << ": I am exhausted so no more training for me...\n";
      return;
    }
    if (is_in_gym == false) {
      std::cout << display_code << id_num
                << ": I can only train in a Pokemon Gym!\n";
      return;
    }
    if (current_gym->IsAbleToTrain(num_training_units, pokemon_dollars,
                                   stamina) == false) {
      std::cout << display_code << id_num
                << ": Not enough stamina and/or money for training.\n";
      return;
    }
    if (current_gym->IsBeaten()) {
      std::cout << display_code << id_num
                << ": Cannot train! This Pokemon Gym is already beaten!\n";
      return;
    }
  }
}
// Tells the Pokemon to start recovering at a PokemonCenter
void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points) {
  if (is_in_center == true &&
      current_center->CanAffordStaminaPoints(num_stamina_points,
                                             pokemon_dollars) &&
      current_center->HasStaminaPoints()) {
    state = RECOVERING_STAMINA;
    stamina_points_to_buy = num_stamina_points;
    std::cout << display_code << id_num << ": Started recovering "
              << num_stamina_points << " stamina point(s) at Pokemon Center "
              << current_center->GetId() << ".\n";
  } else {
    if (is_in_center == false) {
      std::cout << display_code << id_num
                << ": I can only recover stamina at a Pokemon Center!\n";
      return;
    }
    if (current_center->CanAffordStaminaPoints(num_stamina_points,
                                               pokemon_dollars) == false) {
      std::cout << display_code << id_num
                << ": Not enough money to recover stamina.\n";
      return;
    }
    if (current_center->HasStaminaPoints() == false) {
      std::cout << display_code << id_num
                << ": Cannot recover! No stamina points remaining in this "
                   "Pokemon Center.\n";
      return;
    }
  }
}

void Pokemon::ReadyBattle(Rival* in_target) {
  if (state == IN_ARENA &&
      current_arena->IsAbleToFight(pokemon_dollars, stamina) &&
      current_arena->IsBeaten() == false && in_target->IsAlive()) {
    target = in_target;
    state = BATTLE;
    pokemon_dollars -= current_arena->GetDollarCost();
    stamina -= current_arena->GetStaminaCost();
    std::cout << display_code << id_num << ": Getting ready for the battle\n";
  } else {
    if (IsExhausted()) {
      std::cout << display_code << id_num
                << ": I am exhuasted so no more battling for me...\n";
      return;
    }
    if (is_in_arena == false) {
      std::cout << display_code << id_num
                << ": I can only fight in a Battle Arena!\n";
      return;
    }
    if (in_target->IsAlive() == false) {
      std::cout << in_target->GetName() << " already fainted! Cannot battle.\n";
      return;
    }
    if (current_arena->IsAbleToFight(pokemon_dollars, stamina) == false) {
      std::cout << display_code << id_num
                << ": Not enough stamina and/or money for battle.\n";
      return;
    }
    if (current_arena->IsBeaten()) {
      std::cout << display_code << id_num
                << ": Cannot train! This Battle Arena is already beaten!\n";
      return;
    }
  }
}

void Pokemon::TakeHit(double phys_dmg, double magic_dmg, double def) {
  double attack;
  std::cout << GetName() << ": ";
  if (rand() % 2 == 0) {
    attack = phys_dmg;
    std::cout << "Physical damage hurts, Master!\n";
  } else {
    attack = magic_dmg;
    std::cout << "It is magic, Master!\n";
  }
  double damage = (100.0 - defense) / 100 * attack;
  health -= damage;
  std::string hearts;
  if (health > 0) {
    hearts = std::string(int(health), '@');
  } else {
    health = 0;
    hearts = " ";
  }
  std::cout << "Damage: " << damage << '\n'
            << "Health: " << hearts << '\n'
            << "*******\n";
}

void Pokemon::TakeHit(std::string type, double dmg) {
  std::cout << GetName() << ": ";
  if (type == "physical") {
    std::cout << "Aaagh, no physical pain no gain!\n";
  } else {
    std::cout << "Ouch, I don't believe in magic!\n";
  }
  double damage = (100.0 - defense) / 100 * dmg;
  health -= damage;
  std::string hearts;
  if (health > 0) {
    hearts = std::string(int(health), '@');
  } else {
    health = 0;
    hearts = " ";
  }
  std::cout << "Damage: " << damage << '\n'
            << "Health: " << hearts << '\n'
            << "*******\n";
}

void PrintMoves(std::map<int, Attack> moves) {
  std::cout << std::string(40, '-') << '\n';
  for (int i = 0; i < moves.size(); i += 2) {
    std::stringstream s1, s2;
    s1 << '(' << i << ") " << moves[i].name << ": " << moves[i].damage;
    std::cout << std::left << std::setw(20) << s1.str();
    s2 << '(' << i + 1 << ") " << moves[i + 1].name << ": "
       << moves[i + 1].damage;
    std::cout << std::left << std::setw(20) << s2.str();
    std::cout << '\n';
  }
  std::cout << std::string(40, '-') << '\n';
}

void Pokemon::AttackSelect() {
  PrintMoves(move_list);
  std::cout << "Choose an attack! ";
  int choice;
  std::cin >> choice;
  while (std::cin.fail() || choice >= move_list.size()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Not a number! Try again: ";
    std::cin >> choice;
  }
  std::cout << name << " used " << move_list[choice].name << "!\n*******\n";
  target->TakeHit(move_list[choice].type, move_list[choice].damage);
}

void Pokemon::PrintHearts() {
    std::string hearts;
  if (health > 0) {
    hearts = std::string(int(health), '@');
  } else {
    health = 0;
    hearts = " ";
  }
  std::cout << name << ": " << hearts << '\n';
  if (target->GetHealth() > 0) {
    hearts = std::string(int(target->GetHealth()), '@');
  } else {
    hearts = " ";
  }
  std::cout << target->GetName() << ": "
            << std::string(int(target->GetHealth()), '@') << "\n*******\n";
}

bool Pokemon::StartBattle() {
  PrintHearts();
  if (health > 0 or target->GetHealth() > 0) {
    if (speed > target->GetSpeed()) {
      if (!(move_list.empty())) {
        // Go first
        AttackSelect();
        // If target has moves
        if (!(target->move_list.empty())) {
          int random = rand() % target->move_list.size();
          Attack att = target->move_list[random];
          std::cout << target->GetName() << " used " << att.name
                    << "!\n*******\n";
          TakeHit(att.type, att.damage);
          return false;
        } else {
          // Default behavior for Target
          TakeHit(target->GetPhysDmg(), target->GetMagicDmg(), defense);
          return false;
        }
      }
      // No moves
      else {
        // Rival hits first
        TakeHit(target->GetPhysDmg(), target->GetMagicDmg(), defense);
        target->TakeHit(physical_damage, magical_damage, target->GetDefense());
        return false;
      }
    }
    // Target was faster
    else {
      // Target goes first, has moves
      if (!(target->move_list.empty())) {
        int random = rand() % target->move_list.size();
        Attack att = target->move_list[random];
        std::cout << target->GetName() << " used " << att.name
                  << "!\n*******\n";
        // Your turn
        AttackSelect();
        return false;
      }
      // Target no moves
      else {
        TakeHit(target->GetPhysDmg(), target->GetMagicDmg(), defense);
        AttackSelect();
        return false;
      }
    }
  } else if (health <= 0) {
    return true;  // Lost to rival
  } else {
    return true;  // Beat the rival
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
  ////if (IsExhausted() == false) {
  if (stamina != 0) {
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
    case MOVING_TO_ARENA: {
      std::cout << "heading to Battle Arena " << current_arena->GetId()
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
    case IN_ARENA: {
      std::cout << "inside Battle Arena " << current_arena->GetId() << '\n';
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
    case BATTLE: {
      std::cout << "in a battle with " << target->GetName() << '\n';
      break;
    }
    case FAINTED: {
      std::cout << "fainted\n";
      break;
    }
    case EXHAUSTED: {
      std::cout << "exhausted\n";
      break;
    }
    default: {
      break;
    }
  }
  std::cout << "\tStamina: " << stamina << '\n'
            << "\tPokemon Dollars: " << pokemon_dollars << '\n'
            << "\tExperience Points: " << experience_points << '\n'
            << "\tHealth: " << health << '\n'
            << "\tPhysical Damage: " << physical_damage << '\n'
            << "\tMagical Damage: " << magical_damage << '\n'
            << "\tDefense: " << defense << '\n';
}
// Updates depending on state.
bool Pokemon::Update() {
  switch (state) {
    case STOPPED: {
      return false;
    }
    case MOVING: {
      if (IsExhausted() == false) {
        if (UpdateLocation()) {
          state = STOPPED;
          return true;
        } else {
          if (is_in_gym == true) {
            is_in_gym = false;
            current_gym->RemoveOnePokemon();
          }
          if (is_in_center == true) {
            is_in_center = false;
            current_center->RemoveOnePokemon();
          }
          if (is_in_arena == true) {
            is_in_arena = false;
            current_arena->RemoveOnePokemon();
          }
          return false;
        }
      } else {
        std::cout << GetName() << " is out of stamina and can't move.\n";
        state = EXHAUSTED;
        return true;
      }
    }
    case MOVING_TO_CENTER: {
      if (IsExhausted() == false) {
        if (UpdateLocation()) {
          current_center->AddOnePokemon();
          state = IN_CENTER;
          is_in_center = true;
          return true;
        } else {
          if (is_in_gym == true) {
            is_in_gym = false;
            current_gym->RemoveOnePokemon();
          }
          if (is_in_arena == true) {
            is_in_arena = false;
            current_arena->RemoveOnePokemon();
          }
          return false;
        }
      } else {
        std::cout << GetName() << " is out of stamina and can't move.\n";
        state = EXHAUSTED;
        return true;
      }
    }
    case MOVING_TO_GYM: {
      if (IsExhausted() == false) {
        if (UpdateLocation()) {
          current_gym->AddOnePokemon();
          state = IN_GYM;
          is_in_gym = true;
          return true;
        } else {
          if (is_in_center == true) {
            is_in_center = false;
            current_center->RemoveOnePokemon();
          }
          if (is_in_arena == true) {
            is_in_arena = false;
            current_arena->RemoveOnePokemon();
          }
          return false;
        }
      } else {
        std::cout << GetName() << " is out of stamina and can't move.\n";
        state = EXHAUSTED;
        return true;
      }
    }
    case MOVING_TO_ARENA: {
      if (IsExhausted() == false) {
        if (UpdateLocation()) {
          current_arena->AddOnePokemon();
          state = IN_ARENA;
          is_in_arena = true;
          return true;
        } else {
          if (is_in_center == true) {
            is_in_center = false;
            current_center->RemoveOnePokemon();
          }
          if (is_in_gym == true) {
            is_in_gym = false;
            current_gym->RemoveOnePokemon();
          }
          return false;
        }
      } else {
        std::cout << GetName() << " is out of stamina and can't move.\n";
        state = EXHAUSTED;
        return true;
      }
    }
    case IN_CENTER: {
      return false;
    }
    case IN_GYM: {
      return false;
    }
    case TRAINING_IN_GYM: {
      if (current_gym->IsAbleToTrain(training_units_to_buy, pokemon_dollars,
                                     stamina)) {
        if (IsExhausted() == false) {
          unsigned int stam_lost =
              current_gym->GetStaminaCost(training_units_to_buy);
          if (stam_lost <= stamina) {
            stamina -= stam_lost;
            pokemon_dollars -=
                current_gym->GetDollarCost(training_units_to_buy);
          } else {
            pokemon_dollars -=
                current_gym->GetDollarCost(stamina);  // deplete stamina
            stamina = 0;  // Trained as much as possible
          }
          unsigned int exp_gained =
              current_gym->TrainPokemon(training_units_to_buy);
          experience_points += exp_gained;
          std::cout << "** " << name << " completed " << training_units_to_buy
                    << " training unit(s)! **\n";
          std::cout << "** " << name << " gained " << exp_gained
                    << " experienced point(s)! **\n";
          state = IN_GYM;
          return true;
        } else {
          state = EXHAUSTED;
          return true;
        }
      } else {
        return false;
      }
    }
    case RECOVERING_STAMINA: {
      if (current_center->CanAffordStaminaPoints(stamina_points_to_buy,
                                                 pokemon_dollars)) {
        unsigned int stamina_gained =
            current_center->DistributeStamina(stamina_points_to_buy);
        stamina += stamina_gained;
        pokemon_dollars -= current_center->GetDollarCost(stamina_points_to_buy);
        std::cout << "** " << name << " recovered " << stamina_gained
                  << " stamina point(s)! **\n";
        state = IN_CENTER;
        return true;
      } else {
        return false;
      }
    }
    // PA4 Step 1
    case FAINTED: {
      return false;
    }
    case BATTLE: {
      // TODO Check piazza whether Pokemon should lose stamina before or during
      /*
      if (stamina >= current_arena->GetStaminaCost()) {
        stamina -= current_arena->GetStaminaCost();
      }
      else{
        stamina = 0;
      }
      */
      StartBattle();
      if (health > 0 && target->GetHealth() <= 0) {
        std::cout << "Congrats Master, you defeated one rival!\n";
        health = store_health;
        state = IN_ARENA;
        target->IsAlive();
        return true;
      } else if (health <= 0) {
        std::cout << "No! You lost the battle!\n";
        health = 0;
        state = FAINTED;
        current_arena->RemoveOnePokemon();
        target->IsAlive();
        return true;
      } else {
        return false;
      }
    }
    default: {
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
    stamina -= 1;
    pokemon_dollars += GetRandomAmountOfPokemonDollars();
    location = location + delta;
    return false;
  }
}
// Sets up the object to start moving to dest.
void Pokemon::SetupDestination(Point2D dest) {
  destination = dest;
  delta = (destination - location) *
          (speed / GetDistanceBetween(destination, location));
  if (GetDistanceBetween(destination, location) == 0) {
    delta = Vector2D();
  }
}

// Non-members

// Returns a random number between 0.0 and 2.0 inclusive.
double GetRandomAmountOfPokemonDollars() {
  double output =
      static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX / 2.0));
  return output;
}