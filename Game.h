#pragma once
#include "Window.h"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    sf::Time GetElapsed();
    void RestartClock();
    Window* GetWindow();

public:
   Window m_window;
    sf::Vector2i m_increment;
    sf::Clock m_clock;
    sf::Time m_elapsed;
};
