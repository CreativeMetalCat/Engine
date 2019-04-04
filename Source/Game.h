#pragma once
#include "Actor.h"




//class that manages all of the operations in game
class Game
{
	//Draws everything on screen
	void Render();

	//Handles events
	void ProccessEvents();

	//Updates every object
	void Update(sf::Time dt);

	
	std::string path;
public:
	//Init widnow etc.
	void Init();


	void Run();

	//No Get/Set due to SFML restrictions
	sf::RenderWindow window;

	/*
	Path to all files relative to bin
	e.g. . / .. / is relative path to the main folder
	. / .. / scripts is path to folder with lua files
	*/
	Game(std::string WindowName, sf::VideoMode videoMode,std::string path);
	~Game();
};

