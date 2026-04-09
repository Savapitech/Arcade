#include <cstring>
#include <fstream>
#include <iostream>

#include "Database.hpp"
#include "Logger/Logger.hpp"

namespace core {

template <typename T>
static void saveVector(std::ofstream &ofs, const std::vector<T> &vec) {
  uint64_t size = vec.size();
  ofs.write(reinterpret_cast<const char *>(&size), sizeof(size));
  if (size > 0)
    ofs.write(reinterpret_cast<const char *>(vec.data()), size * sizeof(T));
}

template <typename T>
static void loadVector(std::ifstream &ifs, std::vector<T> &vec) {
  uint64_t size = 0;
  if (ifs.read(reinterpret_cast<char *>(&size), sizeof(size))) {
    vec.resize(size);
    if (size > 0)
      ifs.read(reinterpret_cast<char *>(vec.data()), size * sizeof(T));
  }
}

void Database::save(const std::string &filename) const {
  std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);

  if (!ofs.is_open()) {
    LOG_ERROR("Failed to open database file for saving: " + filename);
    return;
  }

  saveVector(ofs, _scores);

  ofs.close();
  LOG_INFO("Database saved successfully to " + filename);
}

void Database::load(const std::string &filename) {
  std::ifstream ifs(filename, std::ios::binary);

  if (!ifs.is_open()) {
    LOG_INFO("Database file not found, file name [" + filename + "]");
    return;
  }

  try {
    loadVector(ifs, _scores);
  } catch (const std::exception &e) {
    LOG_ERROR(("Error loading database: " + std::string(e.what())).c_str());
    return;
  }

  ifs.close();
  LOG_INFO(("Database loaded successfully from " + filename).c_str());
  LOG_DEBUG("Database size [" + std::to_string(_scores.size()) + "]");
}

void Database::setPlayerScore(std::string gameName, std::string playerName,
                              std::uint32_t score) {

  for (Score &playerScore : _scores) {
    if (playerScore.gameName == gameName &&
        playerScore.playerName == playerName) {
      playerScore.score = score;
      return;
    }
  }

  Score newScore;

  strcpy(newScore.gameName, gameName.c_str());
  strcpy(newScore.playerName, playerName.c_str());
  newScore.score = score;

  _scores.push_back(newScore);
}

Score Database::getPlayerGameScore(std::string gameName,
                                   std::string playerName) const {
  for (Score score : _scores)
    if (score.gameName == gameName && score.playerName == playerName)
      return score;

  return {.gameName = "Error", .playerName = "Error", .score = 0};
}

std::vector<Score> Database::getPlayerScores(std::string playerName) const {
  std::vector<Score> playerScores;

  for (Score score : _scores)
    if (score.playerName == playerName)
      playerScores.push_back(score);

  return playerScores;
}

std::vector<Score> Database::getGameScores(std::string gameName) const {
  std::vector<Score> gameScores;

  for (Score score : _scores)
    if (score.gameName == gameName)
      gameScores.push_back(score);

  return gameScores;
}
} // namespace core
