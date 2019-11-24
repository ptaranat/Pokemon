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
      grid[i][j][1] = ' ';
    }
  }
}

void View::Plot(GameObject *ptr) {
  int x, y;
  if (GetSubscripts(x, y, ptr->GetLocation()) == true) {
    // Empty
    if (grid[y][x][0] == '.') {
      ptr->DrawSelf(grid[y][x]);
    } else {
      grid[y][x][0] = '*';
      grid[y][x][1] = ' ';
    }
  }
}
void View::Draw() {
  int max = view_maxsize;
  for (int i = size - 1; i >= 0; i--) {
    if (i % int(scale) == 0) {
      std::cout << std::left << std::setw(2) << max;
      max -= scale * 2;
    } else {
      std::cout << "  ";
    }
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < 2; k++) {
        std::cout << std::right << grid[i][j][k];
      }
    }
    std::cout << '\n';
  }
  std::cout << "  ";
  int temp = 0;
  for (int i = 0; temp <= view_maxsize; i++) {
    if (i % int(scale) == 0) {
      std::cout << std::setw(2) << temp;
      temp += scale * 2;
    } else {
      std::cout << "  ";
    }
  }
  std::cout << '\n';
}