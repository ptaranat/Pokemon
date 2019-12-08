#include "Rival.h"

Rival::Rival(std::string in_name, double in_speed, double hp, double phys_dmg,
             double magic_dmg, double def, int in_id, Point2D in_loc)
    : GameObject(in_loc, in_id, 'R') {
  name = in_name;
  speed = in_speed;
  health = hp;
  physical_damage = phys_dmg;
  magical_damage = magic_dmg;
  defense = def;
  state = ALIVE_RIVAL;
}

void Rival::TakeHit(double phys_dmg, double magic_dmg, double def) {
  double attack;
  if (rand() % 2 == 0)
    attack = phys_dmg;
  else
    attack = magic_dmg;
  double damage = (100.0 - defense) / 100 * attack;
  health -= damage;
}

bool Rival::Update() {
  switch (state) {
    case ALIVE_RIVAL: {
      if (isAlive()) {
        return false;
      } else {
        state = FAINTED_RIVAL;
        return true;
      }
    }
    case FAINTED_RIVAL: {
      if (isAlive() == false) {
        return false;
      }
    }
    default: {
      return false;
    }
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
    default: {
      break;
    }
  }
  std::cout << "\tHealth: " << health << '\n'
            << "\tPhysical Damage: " << physical_damage << '\n'
            << "\tMagical Damage: " << magical_damage << '\n'
            << "\tDefense: " << defense << '\n';