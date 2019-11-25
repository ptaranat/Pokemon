#ifndef VIEW_H
#define VIEW_H

#include "GameObject.h"
// Max size of grid array
const int view_maxsize = 20;

class View {
 private:
  // Current grid size to be displayed.
  int size;
  // Distance represented by each cell of grid.
  double scale;
  // Coordinates of lower left-hand corner of grid.
  Point2D origin;
  // Array to hold characters that make up grid
  char grid[view_maxsize][view_maxsize][2] = {};

  // Calculates the column and row subscripts of the grid array that correspond
  // to supplied location. Returns true if subscripts are valid.
  bool GetSubscripts(int &out_x, int &out_y, Point2D location);

 public:
  View();
  void Clear();
  void Plot(GameObject *ptr);
  void Draw();
};

#endif