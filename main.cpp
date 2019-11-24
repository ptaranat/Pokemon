#include "GameCommand.h"

using namespace std;

int main() {
  std::cout << "EC327: Introduction to Software Engineering\nFall "
            << "2019\nProgramming Assignment 3\n";
  std::cout << R"(
                                  ,'\
    _.----.        ____         ,'  _\   ___    ___     ____
_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
                                `'                            '-._|
                                )"
            << '\n';
  Model* m = new Model();
  View* v = new View();
  char command = ' ';
  m->ShowStatus();
  m->Display(*v);
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