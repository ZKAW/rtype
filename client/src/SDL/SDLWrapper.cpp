/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** SDLWrapper
*/

#include "SDLWrapper.hpp"

sdl::SDLWrapper::SDLWrapper() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw SDLWrapperError("SDL initialization error: " + std::string(SDL_GetError()));
    if (TTF_Init() != 0)
        throw SDLWrapperError("TTF_Init Error: " + std::string(TTF_GetError()));
}

sdl::SDLWrapper::~SDLWrapper() {
    _renderer.reset();
    _window.reset();
    TTF_Quit();
    SDL_Quit();
}

void sdl::SDLWrapper::createWindow(const std::string& title, int width, int height) {
    SDL_Window *window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAGS);
    if (!window)
        throw SDLWrapperError("Window creation error: " + std::string(SDL_GetError()));
    _window = std::shared_ptr<SDL_Window>(window, [](SDL_Window* w) { SDL_DestroyWindow(w); });

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw SDLWrapperError("Renderer creation error: " + std::string(SDL_GetError()));
    _renderer = std::shared_ptr<SDL_Renderer>(renderer, [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    _textureLoader = TextureLoader(_renderer);
};

// std::any = std::shared_ptr<SDL_Renderer>
std::any sdl::SDLWrapper::getWindow() const {
    return _renderer;
}

// std::any = std::shared_ptr<SDL_Texture>
std::any sdl::SDLWrapper::createTexture(const std::string& path) {
    auto texture = _textureLoader.getTexture(path);
    if (!texture) {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
    return texture;
}

// std::any = std::shared_ptr<TTF_Font>
std::any sdl::SDLWrapper::createFont(const std::string& path, int size) {
    return _fontLoader.getFont(path, size);
}

const std::map<SDL_Keycode, InputKey> sdl::SDLWrapper::_keymap = {
    {SDLK_a, InputKey::A},
    {SDLK_b, InputKey::B},
    {SDLK_c, InputKey::C},
    {SDLK_d, InputKey::D},
    {SDLK_e, InputKey::E},
    {SDLK_f, InputKey::F},
    {SDLK_g, InputKey::G},
    {SDLK_h, InputKey::H},
    {SDLK_i, InputKey::I},
    {SDLK_j, InputKey::J},
    {SDLK_k, InputKey::K},
    {SDLK_l, InputKey::L},
    {SDLK_m, InputKey::M},
    {SDLK_n, InputKey::N},
    {SDLK_o, InputKey::O},
    {SDLK_p, InputKey::P},
    {SDLK_q, InputKey::Q},
    {SDLK_r, InputKey::R},
    {SDLK_s, InputKey::S},
    {SDLK_t, InputKey::T},
    {SDLK_u, InputKey::U},
    {SDLK_v, InputKey::V},
    {SDLK_w, InputKey::W},
    {SDLK_x, InputKey::X},
    {SDLK_y, InputKey::Y},
    {SDLK_z, InputKey::Z},
    {SDLK_0, InputKey::NUM0},
    {SDLK_1, InputKey::NUM1},
    {SDLK_2, InputKey::NUM2},
    {SDLK_3, InputKey::NUM3},
    {SDLK_4, InputKey::NUM4},
    {SDLK_5, InputKey::NUM5},
    {SDLK_6, InputKey::NUM6},
    {SDLK_7, InputKey::NUM7},
    {SDLK_8, InputKey::NUM8},
    {SDLK_9, InputKey::NUM9},
    {SDLK_F1, InputKey::F1},
    {SDLK_F2, InputKey::F2},
    {SDLK_F3, InputKey::F3},
    {SDLK_F4, InputKey::F4},
    {SDLK_F5, InputKey::F5},
    {SDLK_F6, InputKey::F6},
    {SDLK_F7, InputKey::F7},
    {SDLK_F8, InputKey::F8},
    {SDLK_F9, InputKey::F9},
    {SDLK_F10, InputKey::F10},
    {SDLK_F11, InputKey::F11},
    {SDLK_F12, InputKey::F12},
    {SDLK_UP, InputKey::UP},
    {SDLK_DOWN, InputKey::DOWN},
    {SDLK_LEFT, InputKey::LEFT},
    {SDLK_RIGHT, InputKey::RIGHT},
    {SDLK_SPACE, InputKey::SPACE},
    {SDLK_TAB, InputKey::TAB},
    {SDLK_RETURN, InputKey::ENTER},
    {SDLK_ESCAPE, InputKey::ESCAPE},
    {SDLK_BACKSPACE, InputKey::BACKSPACE},
    {SDLK_DELETE, InputKey::DELETE},
    {SDLK_UNKNOWN, InputKey::NONE}
};

// std::any = SDL_Keycode
InputKey sdl::SDLWrapper::keyToInputKey(std::any keycode) {
    auto key = std::any_cast<SDL_Keycode>(keycode);
    auto it = _keymap.find(key);
    if (it == _keymap.end())
        return InputKey::NONE;
    return it->second;
}

WindowSize sdl::SDLWrapper::getWindowSize() {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_window.get(), &w, &h);
    return WindowSize{
        .width = w,
        .height = h
    };
}

std::list<InputEvent> sdl::SDLWrapper::getInputEvents() {
    SDL_Event event;
    std::list<InputEvent> events;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            InputEvent input_event;
            input_event.key = InputKey::CLOSE;
            events.push_back(input_event);
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            InputEvent input_event;
            input_event.type = (event.type == SDL_KEYDOWN) ? KeyType::KEYDOWN : KeyType::KEYUP;
            input_event.state = (event.key.state == SDL_PRESSED) ? KeyState::PRESSED : KeyState::RELEASED;
            input_event.timestampSec = event.key.timestamp / kMillisecondsToSeconds;
            input_event.repeat = event.key.repeat != 0;
            input_event.key = keyToInputKey(event.key.keysym.sym);

            events.push_back(input_event);
        }
    }
    return events;
}
