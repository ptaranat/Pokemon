#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"

class GameObject {
 protected:
  Point2D location;   // The location of the object.
  int id_num;         // This object's ID.
  char display_code;  // How the object is represented in the View.
  char state;  // State of the object; more information in each derived class.

 public:
  GameObject(char in_code);
  GameObject(Point2D in_loc, int in_id, char in_code);
  virtual ~GameObject() {
    std::cout << "GameObject destructed.\n";
  };
  Point2D GetLocation();
  int GetId();
  char GetState();
  virtual bool Update() = 0;
  virtual void ShowStatus();
  virtual bool ShouldBeVisible() = 0;
  void DrawSelf(char * ptr); // Added by View
};

#endif