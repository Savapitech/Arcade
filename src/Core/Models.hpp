#pragma once

#include <cstddef>
#include <cstdint>

constexpr std::size_t MAX_PLAYER_NAME_LENGTH = 32;
constexpr std::size_t MAX_GAME_NAME_LENGTH = 32;

struct Score {
  char gameName[MAX_GAME_NAME_LENGTH];
  char playerName[MAX_PLAYER_NAME_LENGTH];
  std::uint32_t score;
};
