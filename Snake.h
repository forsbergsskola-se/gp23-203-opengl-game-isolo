#pragma once
#include <iostream>
#include <vector> 
#include <SFML/Graphics.hpp>

class Snake
{
public:
    enum class Direction { None, Up, Down, Left, Right };

    struct SnakeSegment {
        SnakeSegment(int x, int y) : position(x, y) {}
        sf::Vector2i position;
    };

    Snake(int l_blockSize);
    ~Snake();

    void SetDirection(Direction l_dir);
    Direction GetDirection();
    int GetSpeed();
    sf::Vector2i GetPosition();
    int GetLives();
    int GetScore();
    void IncreaseScore();
    bool HasLost();
    void Lose(); 
    void ToggleLost();
    void Extend(); 
    void Reset(); 
    void Move(); 
    void Tick(); 
    void Cut(int l_segments); 
    void Render(sf::RenderWindow& l_window);

private:
    void CheckCollision(); 

    using SnakeContainer = std::vector<SnakeSegment>; 
    SnakeContainer m_snakeBody; 

    int m_size; 
    Direction m_dir; 
    int m_speed; 
    int m_lives;
    int m_score; 
    bool m_lost; 
    sf::RectangleShape m_bodyRect;
    Snake();
};
