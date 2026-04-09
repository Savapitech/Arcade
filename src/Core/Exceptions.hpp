#pragma once

#include <exception>
#include <string>

namespace core {
class ArcadeException : public std::exception {
protected:
  std::string _msg;

public:
  ArcadeException(const std::string &msg) : _msg(msg) {}
  const char *what() const noexcept override { return _msg.c_str(); }
};

class LoadException : public ArcadeException {
public:
  LoadException(const std::string &msg)
      : ArcadeException("Load exception: " + msg) {}
};

class GameNotFoundException : public ArcadeException {
public:
  GameNotFoundException(const std::string &msg)
      : ArcadeException("Game not found: " + msg) {}
};

class LibraryNotFoundException : public ArcadeException {
public:
  LibraryNotFoundException(const std::string &msg)
      : ArcadeException("Library not found: " + msg) {}
};
} // namespace core