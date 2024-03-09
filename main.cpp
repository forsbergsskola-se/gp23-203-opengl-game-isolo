#include <SFML/Graphics.hpp>
#include "Window.h"

int main() {
    Window window("Bouncing Mushroom", sf::Vector2u(640, 480));

    sf::Texture mushroomTexture;
    mushroomTexture.loadFromFile("Mushroom.png");
    sf::Sprite mushroom(mushroomTexture);
    sf::Vector2u size = mushroomTexture.getSize();
    mushroom.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment(0.4f, 0.4f);

    while (!window.IsDone()) {
        window.Update();

        if ((mushroom.getPosition().x + (size.x / 2) > window.GetWindowSize().x && increment.x > 0) ||
            (mushroom.getPosition().x - (size.x / 2) < 0 && increment.x < 0)) {
            increment.x = -increment.x;
        }
        if ((mushroom.getPosition().y + (size.y / 2) > window.GetWindowSize().y && increment.y > 0) ||
            (mushroom.getPosition().y - (size.y / 2) < 0 && increment.y < 0)) {
            increment.y = -increment.y;
        }
        mushroom.setPosition(mushroom.getPosition() + increment);

        window.BeginDraw();
        window.Draw(mushroom);
        window.EndDraw();
    }

    return 0;
}
