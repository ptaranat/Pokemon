#include "Building.h"

Building::Building() : GameObject('B') {
  std::cout << "Building default constructed.\n";
}
Building::Building(char in_code, int in_id, Point2D in_loc) : GameObject(in_code) {
  id_num = in_id;
  location = in_loc;
  display_code = in_code;
  std::cout << "Building constructed\n";
}
void Building::AddOnePokemon() {
  pokemon_count += 1;
}
void Building::RemoveOnePokemon() {
  pokemon_count -= 1;
}
void Building::ShowStatus() {
  if (pokemon_count == 1) {
    std::cout << pokemon_count << " Pokemon is in this building\n";
  }
  else {
    std::cout << pokemon_count << " Pokemon are in this building\n";
  }
}
bool Building::ShouldBeVisible() {
  return true;
}