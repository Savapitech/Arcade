#pragma once

#include "Game/Game.hpp"
#include "Game/IMenu.hpp"
#include <string>
#include <vector>

namespace game {

class Menu : public AGame, public IMenu {
private:
  std::vector<std::string> _graphicNames;
  std::vector<std::string> _gameNames;
  int _selectedGraphic;
  int _selectedGame;

  void buildTexts();

public:
  Menu();
  void initGame(std::shared_ptr<core::IDatabase> database) override;
  void simulateGame(Event &ev) override;

  std::string getSelectedGame() const override;
  std::string getSelectedGraphic() const override;
  void setGraphicIdx(int idx) override;
  void setGameIdx(int idx) override;
  void setGraphicNames(const std::vector<std::string> &names) override;
  void setGameNames(const std::vector<std::string> &names) override;
};

} // namespace game

extern "C" game::IGame *gameEntryPoint();