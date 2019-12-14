#include "GameCommand.h"

using namespace std;

int main() {
  std::cout << "EC327: Introduction to Software Engineering\nFall "
            << "2019\nProgramming Assignment 4\n";
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
  std::cout << R"(
::::::::::. :::.   :::.    :::.  :::. ::::::::::::
`;;;```.;;;;;`;;  `;;;;,  `;;;  ;;`;;;;;;;;;;''''
`]]nnn]]',[[ '[[,  [[[[[. '[[ ,[[ '[[,   [[     
  $$$""  c$$$cc$$$c $$$ "Y$c$$c$$$cc$$$c  $$     
  888o    888   888,888    Y88 888   888, 88,    
  YMMMb   YMM   ""` MMM     YM YMM   ""`  MMM    

Copyright (c) 2019 Panat Taranat. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT>.
  )" << endl;
  return 0;
}