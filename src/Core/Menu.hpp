#pragma once

#include "Game/Game.hpp"
#include <string>
#include <vector>

namespace core {

class Menu : public game::AGame {
private:
  std::vector<std::string> _graphicNames;
  std::vector<std::string> _gameNames;
  int _selectedGraphic;
  int _selectedGame;
  std::string _userName;

  void buildTexts();

public:
  Menu(const std::vector<std::string> &graphics,
       const std::vector<std::string> &games);
  void initGame() override;
  void simulateGame(Event &ev) override;

  std::string getSelectedGame() const;
  std::string getSelectedGraphic() const;
  void setGraphicIdx(int idx);
  void setGameIdx(int idx);
};

} // namespace core
