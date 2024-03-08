#include "Window.h"

// Default constructor
Window::Window()
    : m_windowSize(sf::Vector2u(640, 480)), // Default size
    m_windowTitle("SFML Window"),
    m_isDone(false),
    m_isFullscreen(false) {
    Setup(m_windowTitle, m_windowSize);
}

// Overloaded constructor
Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
    : m_windowSize(l_size),
    m_windowTitle(l_title),
    m_isDone(false),
    m_isFullscreen(false) {
    Setup(m_windowTitle, m_windowSize);
}

// Destructor
Window::~Window() {
    Destroy();
}

// Initialize window settings
void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size) {
    m_windowTitle = l_title;
    m_windowSize = l_size;
    Create();
}

// Destroy the window
void Window::Destroy() {
    m_window.close();
}

// Create the SFML window
void Window::Create() {
    auto style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    m_window.create({ m_windowSize.x, m_windowSize.y }, m_windowTitle, style);
}

// Clear the window
void Window::BeginDraw() {
    m_window.clear();
}

// Display the changes
void Window::EndDraw() {
    m_window.display();
}

// Update the window
void Window::Update() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_isDone = true;
        }
    }
}

// Check if the window should be closed
bool Window::IsDone() {
    return m_isDone;
}

// Check if the window is in fullscreen mode
bool Window::IsFullscreen() {
    return m_isFullscreen;
}

// Get the size of the window
sf::Vector2u Window::GetWindowSize() {
    return m_windowSize;
}

// Toggle fullscreen mode
void Window::ToggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

// Draw an SFML drawable object to the window
void Window::Draw(sf::Drawable& l_drawable) {
    m_window.draw(l_drawable);
}
