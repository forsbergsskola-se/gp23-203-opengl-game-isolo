#include "Game.h"

Game::Game()
     
    : m_increment(4, 4)
    , m_clock()
    , m_elapsed(m_clock.restart())
{}

Game::~Game() {}

void Game::HandleInput() {}

void Game::Update() {
    m_window.Update();
}

void Game::Render() {
    m_window.BeginDraw();
    m_window.EndDraw();
}

sf::Time Game::GetElapsed() {
    return m_elapsed;
}

void Game::RestartClock() {
    m_elapsed = m_clock.restart();
}

Window* Game::GetWindow()
{
    return &m_window;
}

