#include "Model.h"

Model::Model() {
  time = 0;
  Pokemon* p1 = new Pokemon("Pikachu", 2, 23, 3, 6, 12, 1, 'P', Point2D(5, 1));
  PokemonCenter* c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
  PokemonGym* g1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
  BattleArena* a1 = new BattleArena(3, 3, 2.5, 1, Point2D(15, 12));
  Rival* r1 = new Rival("burhack", 16, 15, 3, 7.2, 20, a1, 1, Point2D(15, 12));
  Rival* r2 = new Rival("Volcarona", 20, 3, 3, 6, 5, a1, 2, Point2D(12,12));

  std::vector<Attack> p1moves;
  Attack att = Attack("Quick Attack", "physical", 4);
  p1moves.push_back(att);
  att = Attack("Thunder Shock", "magical", 4);
  p1moves.push_back(att);
  att = Attack("Spark", "magical", 6);
  p1moves.push_back(att);
  att = Attack("Slam", "physical", 8);
  p1moves.push_back(att);
  p1->SetMoves(p1moves);

  std::vector<Attack> r1moves;
  att = Attack("Homework", "physical", 2);
  r1moves.push_back(att);
  att = Attack("GPA", "magical", 4);
  r1moves.push_back(att);
  att = Attack("Debug Lab", "magical", 6);
  r1moves.push_back(att);
  att = Attack("Exam", "physical", 8);
  r1moves.push_back(att);
  r1->SetMoves(r1moves);
  
  pokemon_ptrs.push_back(p1);
  center_ptrs.push_back(c1);
  gym_ptrs.push_back(g1);
  arena_ptrs.push_back(a1);
  rival_ptrs.push_back(r1);
  rival_ptrs.push_back(r2);

  object_ptrs.push_back(p1);
  object_ptrs.push_back(c1);
  object_ptrs.push_back(g1);
  object_ptrs.push_back(a1);
  object_ptrs.push_back(r1);

  // Use the copy constructor for list
  std::list<GameObject*> temp_list(object_ptrs);
  active_ptrs = temp_list;

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
  for (auto& center : center_ptrs) {
    if (center->GetId() == id) {
      return center;
    }
  }
  return 0;
}
PokemonGym* Model::GetPokemonGymPtr(int id) {
  for (auto& gym : gym_ptrs) {
    if (gym->GetId() == id) {
      return gym;
    }
  }
  return 0;
}
Rival* Model::GetRivalPtr(int id) {
  for (auto& rival : rival_ptrs) {
    if (rival->GetId() == id) {
      return rival;
    }
  }
  return 0;
}
BattleArena* Model::GetBattleArenaPtr(int id) {
  for (auto& arena : arena_ptrs) {
    if (arena->GetId() == id) {
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
    if (tired_pokemon + fainted_pokemon >= pokemon_ptrs.size()) {
      std::cout
          << "GAME OVER: You lose! All of your Pokemon are tired or fainted!\n";
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
  for (auto& obj : active_ptrs) {
    view.Plot(obj);
  }
  view.Draw();
}
void Model::ShowStatus() {
  std::cout << "Time: " << time << '\n';
  for (auto& obj : object_ptrs) {
    obj->ShowStatus();
  }
}
void Model::NewCommand(char type, int id, Point2D loc) {
  try {
    switch (type) {
      case 'p': {
        if (GetPokemonPtr(id) != 0) {
          throw Invalid_Input("Pokemon already exists!");
        }
        Pokemon* p = new Pokemon(loc, id);
        pokemon_ptrs.push_back(p);
        object_ptrs.push_back(p);
        active_ptrs.push_back(p);
        return;
      }
      case 'c': {
        if (GetPokemonCenterPtr(id) != 0) {
          throw Invalid_Input("Center already exists!");
        }
        PokemonCenter* c = new PokemonCenter(loc, id);
        center_ptrs.push_back(c);
        object_ptrs.push_back(c);
        active_ptrs.push_back(c);
        return;
      }
      case 'g': {
        if (GetPokemonGymPtr(id) != 0) {
          throw Invalid_Input("Gym already exists!");
        }
        PokemonGym* g = new PokemonGym(loc, id);
        gym_ptrs.push_back(g);
        object_ptrs.push_back(g);
        active_ptrs.push_back(g);
        return;
      }
      // ! Not Implemented
      /*
      case 'a': {
        if (GetBattleArenaPtr(id) != 0) {
          throw Invalid_Input("Arena already exists!");
        }
        BattleArena* a = new BattleArena(loc, id);
        arena_ptrs.push_back(a);
        return;
      }
      */
      // TODO We cannot create a rival outside an existing arena
      case 'r': {
        if (GetRivalPtr(id) != 0) {
          throw Invalid_Input("Rival already exists!");
        }
        BattleArena* arena = GetBattleArenaPtr(1);  // ! THIS IS HARDCODED
        Rival* r = new Rival(arena, loc, id);
        rival_ptrs.push_back(r);
        object_ptrs.push_back(r);
        active_ptrs.push_back(r);
        return;
      }
      // Should never happen
      default: { throw Invalid_Input("Valid types are p, c, g, r"); }
    }
  } catch (Invalid_Input& except) {
    std::cout << "Invalid ID - " << except.msg_ptr << std::endl;
  }
}