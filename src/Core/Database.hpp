#pragma once

#include <cstdint>
#include <vector>

#include "IDatabase.hpp"
#include "Models.hpp"

namespace core {
class Database : public IDatabase {
private:
  std::vector<Score> _scores;

public:
  Database() = default;
  ~Database() = default;

  void load(const std::string &filename);
  void save(const std::string &filename) const;

  void addPlayerScore(std::string playerName, std::string gameName,
                      std::uint32_t score) override;
  std::uint32_t getPlayerGameScore(std::string playerName,
                                   std::string gameName) const override;
  std::vector<Score> getPlayerScores(std::string playerName) const override;
  std::vector<Score> getGameScores(std::string gameName) const override;
};
} // namespace core
