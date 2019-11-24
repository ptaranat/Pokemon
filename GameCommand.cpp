#include "GameCommand.h"

void DoMoveCommand(Model& model, int pokemon_id, Point2D p1) {
  if (model.GetPokemonPtr(pokemon_id)) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    pokemon->StartMoving(p1);
    std::cout << "Moving " << pokemon->GetName() << " to " << p1 << '\n';

  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetPokemonCenterPtr(center_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    PokemonCenter* center = model.GetPokemonCenterPtr(center_id);
    pokemon->StartMovingToCenter(center);
    std::cout << "Moving " << pokemon->GetName() << " to center " << center_id
              << '\n';
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0 &&
      model.GetPokemonGymPtr(gym_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    PokemonGym* gym = model.GetPokemonGymPtr(gym_id);
    pokemon->StartMovingToGym(gym);
    std::cout << "Moving " << pokemon->GetName() << " to gym " << gym_id << '\n';
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoStopCommand(Model& model, int pokemon_id) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    pokemon->Stop();
    std::cout << "Stopping " << pokemon->GetName() << '\n';
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoTrainInGymCommand(Model& model, int pokemon_id,
                         unsigned int training_units) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    pokemon->StartTraining(training_units);
  } else {
    std::cout << "Error: Please enter a valid command!\n";
  }
}
void DoRecoverInCenterCommand(Model& model, int pokemon_id,
                              unsigned int stamina_points) {
  if (model.GetPokemonPtr(pokemon_id) != 0) {
    Pokemon* pokemon = model.GetPokemonPtr(pokemon_id);
    pokemon->StartRecoveringStamina(stamina_points);
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
  std::cout << "Advancing one tick.\n";
  while(true) {
    for (int i = 0; i < 5; ++i) {
      if (model.Update() == true) {
        break;
      }
    }
  }
  model.ShowStatus();
  model.Display(view);
}

void CommandHandling (Model& model, View& view, const char command) {
  switch(command) {
    case 'm': {
      int id;
      double x, y;
      std::cin >> id >> x >> y;
      Point2D p = Point2D(x, y);
      std::cout << "moving " << id << " to " << p << '\n';
      DoMoveCommand(model, id, p);
      break;
    }
    case 'g': {
      int id;
      int gym;
      std::cin >> id >> gym;
      std::cout << "moving " << id << " towards Pokemon Gym " << gym << '\n';
      DoMoveToGymCommand(model, id, gym);
      break;
    }
    case 'c': {
      int id;
      int center;
      std::cin >> id >> center;
      std::cout << "moving " << id << " towards Pokemon Center " << center << '\n';
      DoMoveToCenterCommand(model, id, center);
      break;
    }
    case 's': {
      int id;
      std::cin >> id;
      std::cout << "Stopping " << id << '\n';
      DoStopCommand(model, id);
      break;
    }
    case 'r': {
      int id;
      unsigned int stamina_amount;
      std::cin >> id >> stamina_amount;
      std::cout << id << " is recovering " << stamina_amount << '\n';
      DoRecoverInCenterCommand(model, id, stamina_amount);
      break;
    }
    case 't': {
      int id;
      unsigned int unit_amount;
      std::cin >> id >> unit_amount;
      std::cout << id << " is training " << unit_amount << '\n';
      DoTrainInGymCommand(model, id, unit_amount);
      break;
    }
    case 'v': {
      std::cout << "go\n";
      DoGoCommand(model, view);
    }
    case 'x': {
      std::cout << "run\n";
      DoRunCommand(model, view);
    }
    case 'q': {
      std::cout << "quit\n";
      model.~Model();  // TODO Probably shouldn't do this
      break;
    }
    default: {
      std::cout << "Error: Please enter a valid command!\n";
      break;
    }
  }
  model.Display(view);
}