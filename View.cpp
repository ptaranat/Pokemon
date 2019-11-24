#include "View.h"
#include <iomanip>

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location) {
  int x = (location.x - origin.x) / scale;
  int y = (location.y - origin.y) / scale;
  if (x <= view_maxsize && y <= view_maxsize) {
    out_x = x;
    out_y = y;
    return true;
  } else {
    std::cout << "An object is outside the display\n";
    return false;
  }
}

View::View() {
  size = 11;
  scale = 2;
  origin = Point2D();
}

void View::Clear() {
  for (int i = 0; i < view_maxsize; ++i) {
    for (int j = 0; j < view_maxsize; ++j) {
      grid[i][j][0] = '.';
    }
  }
}

void View::Plot(GameObject *ptr) {
  int x, y;
  if (GetSubscripts(x, y, ptr->GetLocation()) == true) {
    // Empty
      ptr->DrawSelf(grid[x][y]);
      //std::cout << grid[x][y][0];
      //std::cout << grid[x][y][1];
      // Not empty
      //ptr->DrawSelf(grid[x][y]);
      //grid[x][y][0] = '*';
  }
}
// TODO add axes
void View::Draw() {
  int max = view_maxsize;
  for (int i = size-1; i >= 0; i--) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < 2; k++) {
        std::cout << grid[j][i][k];
      }
    }
    std::cout << '\n';
  }
  
}