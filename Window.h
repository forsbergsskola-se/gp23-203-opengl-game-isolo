#pragma once
#include <SFML/Graphics.hpp>

class Window {
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    ~Window() = default;

    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void BeginDraw();
    void EndDraw();
    bool IsDone();
    bool IsFullscreen();
    sf::Vector2u GetWindowSize();
    void Update();
    void ToggleFullscreen();
    void Draw(sf::Drawable& l_drawable);
    void Clear(const sf::Color& color = sf::Color::Black);

private:
    void Create();
    void Destroy();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen; 
};
