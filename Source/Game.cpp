#include "Game.h"



void Game::Render()
{

	window.clear(sf::Color::Red);
	sf::Font calibri;
	if (calibri.loadFromFile(path + "fonts/calibri.ttf"))
	{
		sf::Text t = sf::Text("Hello", calibri);
		t.setPosition(30, 30);
		window.draw(t);
	}
	else
	{
		std::cout << "Failed to load font" << std::endl;
	}
	window.display();
}

void Game::ProccessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{

	}
}

void Game::Update(sf::Time dt)
{
	//create lua state  for Game's own scripts
	lua_State* L = luaL_newstate();
}

void Game::Init()
{
}

void Game::Run()
{
	sf::Clock clock;

	while (window.isOpen())
	{

		window.clear(sf::Color::Black);
		sf::Time dt = clock.restart();
		ProccessEvents();
		Update(dt);
		window.clear(sf::Color::Black);
		Render();
	}
}

Game::Game(std::string WindowName, sf::VideoMode videoMode,std::string path) :window(videoMode, WindowName),path(path)
{
}


Game::~Game()
{
}
