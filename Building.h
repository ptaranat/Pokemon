#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"

class Building : public GameObject {
 private:
  // Number of Pokemon currently in this Building.
  unsigned int pokemon_count = 0;

 public:
  Building();
  Building(char in_code, int in_id, Point2D in_loc);
  void AddOnePokemon();
  void RemoveOnePokemon();
  void ShowStatus();
  bool ShouldBeVisible();
};

#endif