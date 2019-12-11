#include "GameObject.h"

// Initializes all fields to 0.
GameObject::GameObject(char in_code) {
  display_code = in_code;
  id_num = 1;
  state = 0;
  std::cout << "GameObject constructed.\n";
}
// Initializes specified fields. State is 0.
GameObject::GameObject(Point2D in_loc, int in_id, char in_code) {
  display_code = in_code;
  id_num = in_id;
  location = in_loc;
  state = 0;
  std::cout << "GameObject constructed.\n";
}
// Returns the location for this object.
Point2D GameObject::GetLocation() { return location; }
// Returns the ID for this object.
int GameObject::GetId() { return id_num; }
// Returns the state for this object.
char GameObject::GetState() { return state; }
// Outputs "(display_code)(id_num) at (location)"
void GameObject::ShowStatus() {
  std::cout << display_code << id_num << " at " << location;
}

// Puts the display_code at character pointed to by ptr, then id_num
void GameObject::DrawSelf(char* ptr) {
  ptr[0] = display_code;
  ptr[1] = (char)(id_num + '0'); // Needs to be ascii
  //std::cout << ptr[0] << ptr[1];
}

void GameObject::Save(std::ofstream& file) {
  std::stringstream s;
  std::string x = std::to_string(location.x);
  std::string y = std::to_string(location.y);
  s << x << ' ' << y;
  file << s.str();
}