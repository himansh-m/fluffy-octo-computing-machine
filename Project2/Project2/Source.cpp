#include <SFML/Graphics.hpp>
#include <random>


#define speed 2

int main() {
  sf::RenderWindow window(sf::VideoMode({1200, 600}), "The Survivor",
                          sf::Style::Default);

  sf::Image icon("x.png");
  window.setIcon(icon);
  window.setPosition({13, 13});

  sf::RenderWindow start(sf::VideoMode({600, 300}), "", sf::Style::None);
  start.setPosition({26, 26});
  start.setTitle("Start Screen");
  start.setPosition({300, 150});

  sf::Font font("UbuntuMono[wght].ttf");
  sf::Text text(font, "Start", 32);
  text.setPosition({150, 75});
  sf::Text text2(font, "Exit", 32);
  text2.setPosition({150, 125});

  sf::RectangleShape box({100, 50});
  box.setPosition({150, 75});
  box.setFillColor(sf::Color::Transparent);
  box.setOutlineThickness(4);
  box.setOutlineColor(sf::Color::Black);

  sf::RectangleShape box2({100, 50});
  box2.setPosition({150, 125});
  box2.setFillColor(sf::Color::Transparent);
  box2.setOutlineColor(sf::Color::Black);
  box2.setOutlineThickness(4);

  while (start.isOpen()) {
    start.clear({210, 201, 123});
    start.draw(text);
    start.draw(box);
    start.draw(text2);
    start.draw(box2);
    start.display();
    sf::Vector2i mousePos = sf::Mouse::getPosition(start);

    if (box.getGlobalBounds().contains((sf::Vector2f)mousePos) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      start.close();

    } else if (box2.getGlobalBounds().contains((sf::Vector2f)mousePos) &&
               sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      start.close();
      window.close();
      return 0;
    }
  }

  sf::CircleShape circle(20.0F);
  circle.setOrigin({10, 10});
  circle.setPosition({600, 400});
  circle.setFillColor({123, 125, 32});

  std::random_device ran;

  while (window.isOpen()) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    
    sf::RectangleShape enemy({ 2,3 });
    enemy.setFillColor({ 100,100,100 });
    enemy.setPosition({(float)fmod(ran(),1200), (float)fmod(ran(),600)});

    if (circle.getPosition().x > window.getSize().x) {
      circle.setPosition({0, circle.getPosition().y});
    } else if (circle.getPosition().y > window.getSize().y) {
      circle.setPosition({circle.getPosition().x, 0});
    } else if (circle.getPosition().x < 0) {
      circle.setPosition({1200, circle.getPosition().y});
    } else if (circle.getPosition().y < 0) {
      circle.setPosition({circle.getPosition().x, 600});
    }

    double x = 0, y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      x -= speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      x += speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      y -= speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      y += speed;
    }

    sf::Vector2f vel((float)x, (float)y);
    circle.move(vel);

    window.clear({126, 223, 210});

    window.draw(circle);

    window.draw(enemy);

    window.display();
  }

  return 0;
}