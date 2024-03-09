#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	Window* GetWindow();

private:
	void MoveMushroom();
	Window m_window;

	Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600))
	{
		//Setting up class members.
		m_mushroomTexture.loadFromFile("Mushroom.png");
		m_mushroom.setTexture(m_mushroomTexture);
		m_increment = sf::Vector2i(4, 4);

		Game::~Game() {}
	}
	void Game::Update() {
		m_window.Update(); //Update window events.
		MoveMushroom();
	}
	void Game::MoveMushroom() {
		sf::Vector2u l_windSize = m_window.GetWindowSize();
		sf::Vector2u l_textSize = m_mushroomTexture.getSize();
	}
	if (m_mushroom.getPosition().y >
		l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_mushroom.getPosition().y < 0 && m_increment.y < 0))
		{
			m_increment.y = -m_increment.y;
	}
	m_mushroom.setPosition(
		m_mushroom.getPosition().x + m_increment.x,
		m_mushroom.getPosition().y + -m_increment.y;
	)

		m_mushroom.setPosition(
			m_mushroom.getPosition().x + m_increment.x,
			m_mushroom.getPosition().y + m_increment.y);
};
void Game::Render() {
	m_window.BeginDraw(); //Clear

	m_window.Draw(m_mushroom);
	m_window.EndDraw(); //Display.
}