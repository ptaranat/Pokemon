#include "Model.h"

Model::Model() {
  time = 0;
  Pokemon* p1 = new Pokemon("Pikachu", 2, 23, 3, 6, 12, 1, 'P', Point2D(5, 1));
  Pokemon* p2 =
      new Pokemon("Bulbasaur", 1, 26, 4, 3.7, 5, 2, 'P', Point2D(10, 1));
  PokemonCenter* c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
  PokemonCenter* c2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
  PokemonGym* g1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
  PokemonGym* g2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));
  BattleArena* a1 = new BattleArena(3, 3, 2.5, 1, Point2D(15, 12));
  Rival* r1 = new Rival("burhack", 16, 3, 7.2, 20, a1, 1, Point2D(15, 12));
  Rival* r2 = new Rival("mmark9", 29, 4, 5.2, 12, a1, 2, Point2D(15, 12));
  Rival* r3 = new Rival("Densmore(aka BigBoss)", 41, 6, 8.2, 18, a1, 3,
                        Point2D(15, 12));

  pokemon_ptrs.push_back(p1);
  pokemon_ptrs.push_back(p2);
  center_ptrs.push_back(c1);
  center_ptrs.push_back(c2);
  gym_ptrs.push_back(g1);
  gym_ptrs.push_back(g2);
  arena_ptrs.push_back(a1);
  rival_ptrs.push_back(r1);
  rival_ptrs.push_back(r2);
  rival_ptrs.push_back(r3);

  object_ptrs.push_back(p1);
  object_ptrs.push_back(p2);
  object_ptrs.push_back(c1);
  object_ptrs.push_back(c2);
  object_ptrs.push_back(g1);
  object_ptrs.push_back(g2);
  object_ptrs.push_back(a1);
  object_ptrs.push_back(r1);
  object_ptrs.push_back(r2);
  object_ptrs.push_back(r3);

  active_ptrs.push_back(p1);
  active_ptrs.push_back(p2);
  active_ptrs.push_back(c1);
  active_ptrs.push_back(c2);
  active_ptrs.push_back(g1);
  active_ptrs.push_back(g2);
  active_ptrs.push_back(a1);
  active_ptrs.push_back(r1);
  active_ptrs.push_back(r2);
  active_ptrs.push_back(r3);

  std::cout << "Model default constructed.\n";
}
Model::~Model() {
  for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter) {
    delete *iter;
  }
  std::cout << "Model destructed.\n";
}
Pokemon* Model::GetPokemonPtr(int id) {
  for (auto& pokemon : pokemon_ptrs) {
    if (pokemon->GetId() == id) {
      return pokemon;
    }
  }
  return 0;
}
PokemonCenter* Model::GetPokemonCenterPtr(int id) {
  for (auto& center: center_ptrs) {
    if ( center->GetId() == id) {
      return center;
    }
  }
  return 0;
}
PokemonGym* Model::GetPokemonGymPtr(int id) {
  for (auto& gym: gym_ptrs) {
    if ( gym->GetId() == id) {
      return gym;
    }
  }
  return 0;
}
Rival* Model::GetRivalPtr(int id) {
  for (auto& rival: rival_ptrs) {
    if ( rival->GetId() == id) {
      return rival;
    }
  }
  return 0;
}
BattleArena* Model::GetBattleArenaPtr(int id) {
  for (auto& arena: arena_ptrs) {
    if ( arena->GetId() == id) {
      return arena;
    }
  }
  return 0;
}
bool Model::Update() {
  time++;
  bool updated = false;
  for (auto& obj : object_ptrs) {
    if (obj->Update()) {
      updated = true;
    }
  }
  int gyms_beaten = 0;
  for (auto& gym : gym_ptrs) {
    if (gym->IsBeaten() == true) {
      gyms_beaten++;
      if (gyms_beaten == gym_ptrs.size()) {
        std::cout << "GAME OVER: You win! All Pokemon Gyms beaten!\n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  int arenas_beaten = 0;
  for (auto& arena : arena_ptrs) {
    if (arena->IsBeaten() == true) {
      arenas_beaten++;
      if (arenas_beaten == arena_ptrs.size()) {
        std::cout << "GAME OVER: You win! All Battle Arenas beaten!\n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  int tired_pokemon = 0;
  int fainted_pokemon = 0;
  for (auto& pokemon : pokemon_ptrs) {
    if (pokemon->IsExhausted() == true) {
      tired_pokemon++;
    }
    if (pokemon->IsAlive() == false) {
      fainted_pokemon++;
    }
    if (tired_pokemon+fainted_pokemon >= pokemon_ptrs.size()) {
        std::cout << "GAME OVER: You lose! All of your Pokemon are tired or fainted!\n";
        std::exit(EXIT_SUCCESS);
    }
  }
  for (auto iter = active_ptrs.begin(); iter != active_ptrs.end(); ++iter) {
    GameObject* obj = *iter;
    if (obj->ShouldBeVisible() == false) {
      iter = active_ptrs.erase(iter);
      std::cout << "Inactive object removed\n";
    }
  }
  return updated;
}
void Model::Display(View& view) {
  view.Clear();
  for (auto obj : active_ptrs) {
    view.Plot(obj);
  }
  view.Draw();
}
void Model::ShowStatus() {
  std::cout << "Time: " << time << '\n';
  for (auto obj : object_ptrs) {
    obj->ShowStatus();
  }
}