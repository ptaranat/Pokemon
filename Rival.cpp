#include "Rival.h"

Rival::Rival(std::string in_name, double hp, double phys_dmg, double magic_dmg,
             double def, BattleArena* arena, int in_id, Point2D in_loc)
    : GameObject(in_loc, in_id, 'R') {
  name = in_name;
  health = hp;
  physical_damage = phys_dmg;
  magical_damage = magic_dmg;
  defense = def;
  state = ALIVE_RIVAL;
  is_in_arena = true;
  current_arena = arena;
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
  std::cout << "Damage: " << damage << '\n'
            << "Health: " << health << '\n'
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