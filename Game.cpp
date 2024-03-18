#include "Game.h"
#include "Snake.h"
#include "Snake.cpp"
Window* Game::GetWindow() {
    return &m_window;
}
Game::Game()
    : m_window("Chapter 2", sf::Vector2u(800, 600))
    , 
     m_increment(4, 4)
    , m_clock()
    , m_elapsed(m_clock.restart())
{
    
}

Snake::Snake() {}
Game::~Game() {}
void Game::HandleInput()
{
}

void Game::Update()
{
    m_window.Update(); 
}

void Game::Render() {
    m_window.BeginDraw();
    m_window.Draw(m_mushroom);
    m_window.EndDraw();
}

sf::Time Game::GetElapsed() { return m_elapsed; }
void Game::RestartClock() { m_elapsed = m_clock.restart(); }