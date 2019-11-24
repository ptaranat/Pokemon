#include "Building.h"

// Default constructor, display_code is 'B'
Building::Building() : GameObject('B') {
  std::cout << "Building default constructed.\n";
}
// Initializes the id number to in_id, and the location to in_loc, display_code
// to in_code, and remainder of the member variables to their default initial
// values.
Building::Building(char in_code, int in_id, Point2D in_loc)
    : GameObject(in_code) {
  id_num = in_id;
  location = in_loc;
  display_code = in_code;
  std::cout << "Building constructed\n";
}
void Building::AddOnePokemon() { pokemon_count += 1; }
void Building::RemoveOnePokemon() { pokemon_count -= 1; }
// Prints “(pokemon_count) pokemon is/are in this building”
void Building::ShowStatus() {
  GameObject::ShowStatus();
  std::cout << '\n';
  if (pokemon_count == 1) {
    std::cout << '\t' << pokemon_count << " Pokemon is in this building\n";
  } else {
    std::cout << '\t' <<  pokemon_count << " Pokemon are in this building\n";
  }
}
// Returns true because buildings are always visible
bool Building::ShouldBeVisible() { return true; }