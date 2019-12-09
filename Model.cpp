#include "Model.h"

Model::Model() {
  time = 0;
  //Pokemon* p1 = new Pokemon("Pikachu", 1, 'P', 2, Point2D(5, 1));
  Pokemon* p1 = new Pokemon("Pikachu", 2, 23, 3, 6, 12, 1, 'P', Point2D(5, 1));
  object_ptrs[0] = p1;
  pokemon_ptrs[0] = p1;
  //Pokemon* p2 = new Pokemon("Bulbasaur", 2, 'P', 1, Point2D(10, 1));
  Pokemon* p2 = new Pokemon("Bulbasaur", 1, 26, 4, 3.7, 5, 2, 'P', Point2D(10, 1));
  object_ptrs[1] = p2;
  pokemon_ptrs[1] = p2;
  PokemonCenter* c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
  object_ptrs[2] = c1;
  center_ptrs[0] = c1;
  PokemonCenter* c2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
  object_ptrs[3] = c2;
  center_ptrs[1] = c2;
  PokemonGym* g1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
  object_ptrs[4] = g1;
  gym_ptrs[0] = g1;
  PokemonGym* g2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));
  object_ptrs[5] = g2;
  gym_ptrs[1] = g2;
  BattleArena* a1 = new BattleArena(3, 3, 2.5, 1, Point2D(15,12));
  object_ptrs[6] = a1;
  arena_ptrs[0] = a1;
  Rival* r1 = new Rival("burhack", 16, 3, 7.2, 20, a1, 1, Point2D(15,12));
  object_ptrs[7] = r1;
  rival_ptrs[0] = r1;
  Rival* r2 = new Rival("mmark9", 29, 4, 5.2, 12, a1, 2, Point2D(15,12));
  object_ptrs[8] = r2;
  rival_ptrs[1] = r2;
  Rival* r3 = new Rival("Densmore(aka BigBoss)", 41, 6, 8.2, 18, a1, 3, Point2D(15,12));
  object_ptrs[9] = r3;
  rival_ptrs[2] = r3;

  num_objects = 10;
  num_pokemon = 2;
  num_centers = 2;
  num_gyms = 2;
  num_rivals = 3;
  num_arenas = 1;
  std::cout << "Model default constructed.\n";
}
Model::~Model() {
  for (int i = 0; i < num_objects; ++i) delete object_ptrs[i];
  std::cout << "Model destructed.\n";
}
Pokemon* Model::GetPokemonPtr(int id) {
  for (int i = 0; i < num_pokemon; ++i) {
    if (pokemon_ptrs[i]->GetId() == id) {
      return pokemon_ptrs[i];
    }
  }
  return 0;
}
PokemonCenter* Model::GetPokemonCenterPtr(int id) {
  for (int i = 0; i < num_centers; ++i) {
    if (center_ptrs[i]->GetId() == id) {
      return center_ptrs[i];
    }
  }
  return 0;
}
PokemonGym* Model::GetPokemonGymPtr(int id) {
  for (int i = 0; i < num_gyms; ++i) {
    if (gym_ptrs[i]->GetId() == id) {
      return gym_ptrs[i];
    }
  }
  return 0;
}
Rival* Model::GetRivalPtr(int id) {
  for (int i = 0; i < num_rivals; ++i) {
    if (rival_ptrs[i]->GetId() == id) {
      return rival_ptrs[i];
    }
  }
  return 0;
}
BattleArena* Model::GetBattleArenaPtr(int id) {
  for (int i = 0; i < num_arenas; ++i) {
    if (arena_ptrs[i]->GetId() == id) {
      return arena_ptrs[i];
    }
  }
  return 0;
}
bool Model::Update() {
  time++;
  bool updated = false;
  for (int i = 0; i < num_objects; ++i) {
    if (object_ptrs[i]->Update()) {
      updated = true;
    }
  }
  int total_gyms = 0;
  for (int i = 0; i < num_gyms; ++i) {
    if (gym_ptrs[i]->IsBeaten() == true) {
      total_gyms++;
      if (total_gyms == num_gyms) {
        std::cout << "GAME OVER: You win! All Pokemon Gyms beaten!\n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  int arenas_beaten = 0;
  for (int i = 0; i < num_arenas; ++i) {
    if (arena_ptrs[i]->IsBeaten() == true) {
      arenas_beaten ++;
      if (arenas_beaten == num_arenas) {
        std::cout << "GAME OVER: You win! All Battle Arenas beaten!\n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  int tired_pokemon = 0;
  for (int i = 0; i < num_pokemon; ++i) {
    if (pokemon_ptrs[i]->IsExhausted() == true) {
      tired_pokemon++;
      if (tired_pokemon == num_pokemon) {
        std::cout << "GAME OVER: You lose! All of your Pokemon are tired!\n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  int fainted_pokemon = 0;
  for (int i = 0; i < num_pokemon; ++i) {
    if (pokemon_ptrs[i]->isAlive() == false) {
      fainted_pokemon++;
      if (fainted_pokemon == num_pokemon) {
        std::cout << "GAME OVER: You lose! All of your Pokemon fainted!\n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  return updated;
}
void Model::Display(View& view) {
  view.Clear();
  for (int i = 0; i < num_objects; ++i) {
    view.Plot(object_ptrs[i]);
  }
  view.Draw();
}
void Model::ShowStatus() {
  std::cout << "Time: " << time << '\n';
  for (int i = 0; i < num_objects; ++i) object_ptrs[i]->ShowStatus();
}