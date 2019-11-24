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
  origin = (Point2D(0.0, 0.0));
}

void View::Clear() {
  for (int i = 0; i < view_maxsize; ++i) {
    for (int j = 0; j < view_maxsize; ++j) {
      grid[i][j][1] = '.';
    }
  }
}

void View::Plot(GameObject *ptr) {
  int x, y;
  if (GetSubscripts(x, y, ptr->GetLocation) == true) {
    // Empty
    if (grid[x][y][0] == '.') {
      ptr->DrawSelf(grid[x][y]);
    } else {
      // Not empty
      ptr->DrawSelf(grid[x][y]);
      grid[x][y][0] = '*';
    }
  }
}

void View::Draw() {
  int max = view_maxsize;
  std::cout << std::left << std::setw(2) << max << std::right
            << std::setw(size * 2);
  for (int i = view_maxsize - 1; i >= size; --i) {
    for (int j = view_maxsize - 1; j >= size; --j) {
      for (int k = 0; k < 2; ++k) {
        std::cout << grid[i][j][k] << " ";
      }
    }
    std::cout << '\n';
  }
}