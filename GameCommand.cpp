#include "GameCommand.h"

#include <limits>

void DoMoveCommand(Model& model, int pokemon_id, Point2D p1) {
  if (model.GetPokemonPtr(pokemon_id)) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Moving " << pokemon->GetName() << " to " << p1 << '\n';
    pokemon->StartMoving(p1);
  } else {
    std::cout << "Error: Please enter a valid command!\n";
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
    std::cout << "Error: Please enter a valid command!\n";
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
    std::cout << "Error: Please enter a valid command!\n";
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
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoStopCommand(Model& model, int pokemon_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Stopping " << pokemon->GetName() << '\n';
    pokemon->Stop();
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoTrainInGymCommand(Model& model, int pokemon_id,
                         unsigned int training_units) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Training " << pokemon->GetName() << '\n';
    pokemon->StartTraining(training_units);
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoRecoverInCenterCommand(Model& model, int pokemon_id,
                              unsigned int stamina_points) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    std::cout << "Recovering " << pokemon->GetName() << "'s stamina\n";
    pokemon->StartRecoveringStamina(stamina_points);
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoBattleCommand(Model& model, int pokemon_id, int rival_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetRivalPtr(rival_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    Rival* rival = model.GetRivalPtr(rival_id);
    //std::cout << pokemon->GetName() << " is battling " << rival->GetName() << "!\n";
    pokemon->ReadyBattle(rival);
  } else {
    std::cout << "Error: Please enter a valid command!\n";
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
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Error: Please enter a valid command!\n";
    return;
  }
  switch (command) {
    case 'm': {
      int id;
      double x, y;
      std::cin >> id >> x >> y;
      Point2D p = Point2D(x, y);
      DoMoveCommand(model, id, p);
      model.Display(view);
      break;
    }
    case 'g': {
      int id;
      int gym;
      std::cin >> id >> gym;
      DoMoveToGymCommand(model, id, gym);
      model.Display(view);
      break;
    }
    case 'c': {
      int id;
      int center;
      std::cin >> id >> center;
      DoMoveToCenterCommand(model, id, center);
      model.Display(view);
      break;
    }
    case 'a': {
      int id;
      int arena;
      std::cin >> id >> arena;
      DoMoveToArenaCommand(model, id, arena);
      model.Display(view);
      break;
    }
    case 's': {
      int id;
      std::cin >> id;
      DoStopCommand(model, id);
      model.Display(view);
      break;
    }
    case 'r': {
      int id;
      unsigned int stamina_amount;
      std::cin >> id >> stamina_amount;
      DoRecoverInCenterCommand(model, id, stamina_amount);
      model.Display(view);
      break;
    }
    case 't': {
      int id;
      unsigned int unit_amount;
      std::cin >> id >> unit_amount;
      DoTrainInGymCommand(model, id, unit_amount);
      model.Display(view);
      break;
    }
    case 'b': {
      int id;
      int rival_id;
      std::cin >> id >> rival_id;
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
      std::cout << "Error: Please enter a valid command!\n";
      break;
    }
  }
}