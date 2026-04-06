#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Models.hpp"

namespace core {
class IDatabase {
public:
  virtual ~IDatabase() = default;

  virtual void addPlayerScore(std::string playerName, std::string gameName,
                              std::uint32_t score) = 0;
  virtual std::uint32_t getPlayerGameScore(std::string playerName,
                                           std::string gameName) const = 0;
  virtual std::vector<Score> getPlayerScores(std::string playerName) const = 0;
  virtual std::vector<Score> getGameScores(std::string gameName) const = 0;
};
} // namespace core
