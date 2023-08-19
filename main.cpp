#include "Driver.h"
#include "Config.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void setupConfig();
void setWindowIcon(sf::RenderWindow &window);

int main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	const sf::Color clearColor(64, 64, 64);

	setupConfig();

	sf::RenderWindow window(
		sf::VideoMode(
			Config::Window::width,
			Config::Window::height,
			Config::Window::bitsPerPixel),
		"Boom Box",
		sf::Style::Fullscreen);

	sf::Image windowIcon;

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	setWindowIcon(window);

	sf::Clock frameClock;
	float deltaTime = 0.0f;

	Driver driver;

	while (window.isOpen()
		&& driver.isLive())
	{
		sf::Event ev;

		deltaTime = frameClock.restart().asSeconds();
		
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::MouseMoved:
					driver.updateOnMouseMove(ev.mouseMove.x, ev.mouseMove.y);
					break;
				case sf::Event::MouseButtonPressed:
					driver.updateOnMouseButtonPress(ev.mouseButton.button);
					break;
				case sf::Event::KeyPressed:
					driver.updateOnKeyPress(ev.key.code);
					break;
				case sf::Event::KeyReleased:
					driver.updateOnKeyRelease(ev.key.code);
					break;
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		driver.update(deltaTime);

		window.clear(clearColor);
		window.draw(driver);
		window.display();
	}

	return 0;
}

void setupConfig()
{
	const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	Config::Window::width = desktopMode.width;
	Config::Window::height = desktopMode.height;

	Config::Window::bitsPerPixel = desktopMode.bitsPerPixel;

	Config::Game::scale = std::floorf(
		(Config::Window::width + Config::Window::height) * 0.0048f);

	Config::Font::scale = Config::Game::scale * 0.0415f;
}

void setWindowIcon(sf::RenderWindow &window)
{
	sf::Image windowIcon;

	windowIcon.loadFromFile("./assets/icon/icon.png");

	window.setIcon(32, 32, windowIcon.getPixelsPtr());
}