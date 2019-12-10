#include "GameCommand.h"

#include <limits>

void DoMoveCommand(Model& model, int pokemon_id, Point2D p1) {
  if (model.GetPokemonPtr(pokemon_id)) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Moving " << pokemon->GetName() << " to " << p1 << '\n';
    pokemon->StartMoving(p1);
  } else {
    throw Invalid_Input("Pokemon doesn't exist");
  }
}
void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetPokemonCenterPtr(center_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    PokemonCenter* center = model.GetPokemonCenterPtr(center_id);
    std::cout << "Moving " << pokemon->GetName() << " to center " << center_id
              << '\n';
    pokemon->StartMovingToCenter(center);
  } else {
    throw Invalid_Input("Pokemon or Center doesn't exist");
  }
}
void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetPokemonGymPtr(gym_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    PokemonGym* gym = model.GetPokemonGymPtr(gym_id);
    std::cout << "Moving " << pokemon->GetName() << " to gym " << gym_id
              << '\n';
    pokemon->StartMovingToGym(gym);
  } else {
    throw Invalid_Input("Pokemon or Gym doesn't exist");
  }
}
void DoMoveToArenaCommand(Model& model, int pokemon_id, int arena_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetBattleArenaPtr(arena_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    BattleArena* arena = model.GetBattleArenaPtr(arena_id);
    std::cout << "Moving " << pokemon->GetName() << " to arena " << arena_id
              << '\n';
    pokemon->StartMovingToArena(arena);
  } else {
    throw Invalid_Input("Pokemon or Arena doesn't exist");
  }
}
void DoStopCommand(Model& model, int pokemon_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Stopping " << pokemon->GetName() << '\n';
    pokemon->Stop();
  } else {
    throw Invalid_Input("Pokemon doesn't exist");
  }
}
void DoTrainInGymCommand(Model& model, int pokemon_id,
                         unsigned int training_units) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Training " << pokemon->GetName() << '\n';
    pokemon->StartTraining(training_units);
  } else {
    throw Invalid_Input("Pokemon doesn't exist");
  }
}
void DoRecoverInCenterCommand(Model& model, int pokemon_id,
                              unsigned int stamina_points) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Recovering " << pokemon->GetName() << "'s stamina\n";
    pokemon->StartRecoveringStamina(stamina_points);
  } else {
    throw Invalid_Input("Pokemon doesn't exist");
  }
}
void DoBattleCommand(Model& model, int pokemon_id, int rival_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetRivalPtr(rival_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    Rival* rival = model.GetRivalPtr(rival_id);
    // std::cout << pokemon->GetName() << " is battling " << rival->GetName() <<
    // "!\n";
    pokemon->ReadyBattle(rival);
  } else {
    throw Invalid_Input("Pokemon or Rival doesn't exist");
  }
}
void DoGoCommand(Model& model, View& view) {
  std::cout << "Advancing one tick.\n";
  model.Update();
  model.ShowStatus();
  model.Display(view);
}
void DoRunCommand(Model& model, View& view) {
  std::cout << "Advancing to next event.\n";
  for (int i = 0; i < 5; ++i) {
    if (model.Update() == true) {
      break;
    }
  }
  model.ShowStatus();
  model.Display(view);
}

void CommandHandling(Model& model, View& view, const char command) {
  try {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      throw Invalid_Input("Please enter a valid command code");
      return;
    }
    switch (command) {
      case 'n': {
        char type;
        int id;
        double x, y;
        if (!(std::cin >> type >> id >> x >> y))
          throw Invalid_Input("Invalid parameters (char, int, double, double");
        // Check if type is valid
        if (!((std::string("pcgr").find(type) != std::string::npos)))
          throw Invalid_Input("Valid types are p, c, g, r");
        model.NewCommand(type, id, Point2D(x, y));
        break;
      }
      case 'm': {
        int id;
        double x, y;
        if (!(std::cin >> id >> x >> y))
          throw Invalid_Input("Not a valid coordinate");
        Point2D p = Point2D(x, y);
        DoMoveCommand(model, id, p);
        model.Display(view);
        break;
      }
      case 'g': {
        int id;
        int gym;
        if (!(std::cin >> id >> gym))
          throw Invalid_Input("Not a valid Pokemon or Gym ID (integer)");
        DoMoveToGymCommand(model, id, gym);
        model.Display(view);
        break;
      }
      case 'c': {
        int id;
        int center;
        if (!(std::cin >> id >> center))
          throw Invalid_Input("Not a valid Pokemon or Center ID (integer)");
        DoMoveToCenterCommand(model, id, center);
        model.Display(view);
        break;
      }
      case 'a': {
        int id;
        int arena;
        if (!(std::cin >> id >> arena))
          throw Invalid_Input("Not a valid Pokemon or Arena ID (integer)");
        DoMoveToArenaCommand(model, id, arena);
        model.Display(view);
        break;
      }
      case 's': {
        int id;
        if (!(std::cin >> id))
          throw Invalid_Input("Not a valid Pokemon ID (integer)");
        DoStopCommand(model, id);
        model.Display(view);
        break;
      }
      case 'r': {
        int id;
        unsigned int stamina_amount;
        if (!(std::cin >> id >> stamina_amount))
          throw Invalid_Input(
              "Not a valid Pokemon or stamina amount (integer)");
        DoRecoverInCenterCommand(model, id, stamina_amount);
        model.Display(view);
        break;
      }
      case 't': {
        int id;
        unsigned int unit_amount;
        if (!(std::cin >> id >> unit_amount))
          throw Invalid_Input(
              "Not a valid Pokemon ID or training amount (integer)");
        DoTrainInGymCommand(model, id, unit_amount);
        model.Display(view);
        break;
      }
      case 'b': {
        int id;
        int rival_id;
        if (!(std::cin >> id >> rival_id))
          throw Invalid_Input("Not a valid Pokemon or Rival ID (integer)");
        DoBattleCommand(model, id, rival_id);
        model.Display(view);
        break;
      }
      case 'v': {
        DoGoCommand(model, view);
        break;
      }
      case 'x': {
        DoRunCommand(model, view);
        break;
      }
      case 'q': {
        model.~Model();
        break;
      }
      default: {
        throw Invalid_Input("Please enter a valid command code");
        break;
      }
    }
  } catch (Invalid_Input& except) {
    std::cout << "Error: " << except.msg_ptr << std::endl;
  }
}