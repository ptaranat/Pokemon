#include "Rival.h"
#include <sstream>

// TODO How can I create a Rival without it belonging to an arena??
Rival::Rival(BattleArena* arena, Point2D in_loc, int in_id)
    : GameObject(in_loc, in_id, 'R') {
  // Create a Rival named "Rival ID" where ID=in_id
  std::ostringstream oss;
  oss << "Rival " << in_id;
  name = oss.str();
  state = ALIVE_RIVAL;
  is_in_arena = true;
  current_arena = arena;
  arena->AddOneRival();
}

Rival::Rival(std::string in_name, double in_speed, double hp, double phys_dmg, double magic_dmg,
             double def, BattleArena* arena, int in_id, Point2D in_loc)
    : GameObject(in_loc, in_id, 'R') {
  name = in_name;
  speed = in_speed;
  health = hp;
  physical_damage = phys_dmg;
  magical_damage = magic_dmg;
  defense = def;
  state = ALIVE_RIVAL;
  is_in_arena = true;
  current_arena = arena;
}

void Rival::TakeHit(std::string type, double dmg) {
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
            << "Health: " << std::string(int(health), '@') << '\n'
            << "*******\n";
}

void Rival::TakeHit(double phys_dmg, double magic_dmg, double def) {
  double attack;
  std::cout << GetName() << ": ";
  if (rand() % 2 == 0) {
    attack = phys_dmg;
    std::cout << "Aaagh, no physical pain no gain!\n";
  } else {
    attack = magic_dmg;
    std::cout << "Ouch, I don't believe in magic!\n";
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
bool Rival::ShouldBeVisible() {
  if (IsAlive()) {
    return true;
  } else {
    return false;
  }
}

bool Rival::Update() {
  switch (state) {
    case ALIVE_RIVAL: {
      if (IsAlive()) {
        return false;
      } else {
        state = FAINTED_RIVAL;
        health = 0;
        current_arena->RemoveOneRival();
        return true;
      }
    }
    case FAINTED_RIVAL: {
      if (IsAlive() == false) {
        health = 0;
        return false;
      }
    }
    default: { return false; }
  }
}

void Rival::ShowStatus() {
  std::cout << name << " status: ";
  GameObject::ShowStatus();
  std::cout << ' ';
  switch (state) {
    case ALIVE_RIVAL: {
      std::cout << "alive\n";
      break;
    }
    case FAINTED_RIVAL: {
      std::cout << "fainted\n";
      break;
    }
    default: { break; }
  }
  std::cout << "\tHealth: " << health << '\n'
            << "\tPhysical Damage: " << physical_damage << '\n'
            << "\tMagical Damage: " << magical_damage << '\n'
            << "\tDefense: " << defense << '\n';
}