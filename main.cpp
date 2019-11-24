#include "GameCommand.h"

using namespace std;

int main() {
  Model* m = new Model();
  View* v = new View();
  char command = ' ';
  while (true) {
    std::cout << "Enter command: ";
    std::cin >> command;
    /*
    if (command == 'q') {
      std::cout << "quit\n";
      delete m;
      return 0;
    }
    */
    CommandHandling(*m, *v, command);
    if (command == 'q') {
      break;
    }
  }

  return 0;
}