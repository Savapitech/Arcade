#include <stdexcept>

#include "SDL2GraphicalLib.hpp"

core::Keys SDL2::convertSDLKey(SDL_Keycode keycode) const {
  if (keycode >= SDLK_a && keycode <= SDLK_z)
    return static_cast<core::Keys>(keycode - SDLK_a);
  if (keycode >= SDLK_0 && keycode <= SDLK_9)
    return static_cast<core::Keys>(core::Keys::Num0 + (keycode - SDLK_0));
  if (keycode == SDLK_SPACE)
    return core::Keys::Space;
  if (keycode == SDLK_RETURN || keycode == SDLK_KP_ENTER)
    return core::Keys::Enter;
  return core::Keys::P;
}

void SDL2::openWindow(size_t heigth, size_t width,
                      const std::string &windowName, Event &event) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw std::runtime_error(SDL_GetError());

  int imgFlags = IMG_INIT_PNG;
  if ((IMG_Init(imgFlags) & imgFlags) == 0) {
    SDL_Quit();
    throw std::runtime_error(IMG_GetError());
  }

  this->_window = SDL_CreateWindow(
      windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      static_cast<int>(heigth), static_cast<int>(width), SDL_WINDOW_SHOWN);

  if (this->_window == nullptr) {
    IMG_Quit();
    SDL_Quit();
    throw std::runtime_error(SDL_GetError());
  }

  this->_renderer = SDL_CreateRenderer(
      this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (this->_renderer == nullptr) {
    SDL_DestroyWindow(this->_window);
    this->_window = nullptr;
    IMG_Quit();
    SDL_Quit();
    throw std::runtime_error(SDL_GetError());
  }

  event.setCloseState(true);
  _isOpened = true;
}

void SDL2::closeWindow() {
  this->destroyGraphic();

  if (this->_renderer != nullptr) {
    SDL_DestroyRenderer(this->_renderer);
    this->_renderer = nullptr;
  }
  if (this->_window != nullptr) {
    SDL_DestroyWindow(this->_window);
    this->_window = nullptr;
  }

  IMG_Quit();
  SDL_Quit();
}

bool SDL2::isOpen() { return this->_window != nullptr; }

void SDL2::initGraphic(const std::vector<game::Entity> &entities) {
  this->destroyGraphic();

  this->_textureTab.reserve(entities.size());
  this->_rectTab.reserve(entities.size());

  for (const auto &entity : entities) {
    SDL_Surface *surface = IMG_Load(entity.getPath().c_str());
    if (surface == nullptr)
      throw std::runtime_error(IMG_GetError());

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(this->_renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
      throw std::runtime_error(SDL_GetError());

    int texWidth = 0;
    int texHeight = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

    SDL_Rect destRect = {
        static_cast<int>(entity.getStartPos().x),
        static_cast<int>(entity.getStartPos().y),
        texWidth,
        texHeight,
    };

    this->_textureTab.push_back(texture);
    this->_rectTab.push_back(destRect);
  }
}

void SDL2::destroyGraphic() {
  for (SDL_Texture *texture : this->_textureTab)
    SDL_DestroyTexture(texture);
  this->_textureTab.clear();
  this->_rectTab.clear();
}

void SDL2::drawEntities(const std::vector<game::Entity> &entities) {
  SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
  SDL_RenderClear(this->_renderer);

  for (size_t i = 0; i < this->_textureTab.size() &&
                     i < this->_rectTab.size() && i < entities.size();
       i++) {
    this->_rectTab[i].x = static_cast<int>(entities[i].getPos().x);
    this->_rectTab[i].y = static_cast<int>(entities[i].getPos().y);

    core::Rect src = entities[i].getSrcRect();
    SDL_Rect *srcPtr = nullptr;
    SDL_Rect srcRectSDL;
    if (src.width > 0 && src.height > 0) {
      srcRectSDL = {static_cast<int>(src.x), static_cast<int>(src.y),
                    static_cast<int>(src.width), static_cast<int>(src.height)};
      srcPtr = &srcRectSDL;
      this->_rectTab[i].w = static_cast<int>(src.width);
      this->_rectTab[i].h = static_cast<int>(src.height);
    }

    SDL_RenderCopy(this->_renderer, this->_textureTab[i], srcPtr,
                   &this->_rectTab[i]);
  }

  SDL_RenderPresent(this->_renderer);
}

void SDL2::fillEvent(Event &event) {
  SDL_Event sdlEvent;

  while (SDL_PollEvent(&sdlEvent)) {
    if (sdlEvent.type == SDL_QUIT) {
      event.setCloseState(false);
      this->closeWindow();
      _isOpened = false;
      return;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  for (SDL_Keycode i = SDLK_a; i <= SDLK_z; ++i) {
    if (state[SDL_GetScancodeFromKey(i)])
      event.addKey(this->convertSDLKey(i));
  }
  for (SDL_Keycode i = SDLK_0; i <= SDLK_9; ++i) {
    if (state[SDL_GetScancodeFromKey(i)])
      event.addKey(this->convertSDLKey(i));
  }
  if (state[SDL_SCANCODE_SPACE])
    event.addKey(core::Keys::Space);
  if (state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_KP_ENTER])
    event.addKey(core::Keys::Enter);
}

SDL2::~SDL2() { this->closeWindow(); }

extern "C" graphic::IGraphic *graphicEntryPoint() { return new SDL2(); }
