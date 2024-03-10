#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    const float IncrementSpeed = 0.5f;
   
    Game game; 

    while (!game.GetWindow()->IsDone()) {
        game.HandleInput();
        game.Update();
        game.Render();

        sf::sleep(sf::seconds(1.0f / 60.0f)); 
    }
    return 0;
}