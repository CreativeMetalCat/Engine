#include "Game.h"


int SCREENWIDTH = 1024;
int SCREENHEIGHT = 720;

using namespace luabridge;


std::string PATH = "C:/Users/catgu/source/repos/Engine/x64/Debug/";

//a = &(*actor);
int main()
{
	std::shared_ptr<Actor> actor = std::make_shared<Actor>(sf::Vector2f(120, 675));



	lua_State* L = luaL_newstate();

	Actor *a = new Actor(sf::Vector2f(23, 23));
	std::string d = (PATH + "scripts/actor.lua");
	try
	{

		luaL_dofile(L, d.c_str());
		luaL_openlibs(L);

		lua_pcall(L, 0, 0, 0);

		//Register Actor in lua
		Actor::RegisterClassLUA(L);

		//Register Vector2 in lua
		getGlobalNamespace(L)
			.beginClass<sf::Vector2f>("Vector2")
			//add x,y and some functions possibly
			.addData<float>("x", &sf::Vector2<float>::x)
			.addData<float>("y", &sf::Vector2<float>::y)
			.addConstructor<void(*) (void)>()
			.endClass();


		LuaRef LuaSetActorLocation = getGlobal(L, "SetActorLocation");
		LuaRef LuaMoveX = getGlobal(L, "MoveX");
		LuaRef LuaAddChild = getGlobal(L, "AddChild");
		LuaRef LuaGetChild = getGlobal(L, "GetChild");


		if (LuaSetActorLocation.isFunction())
		{
			LuaSetActorLocation(&(*actor), &sf::Vector2f(450, 0));
		}
		if (LuaAddChild.isFunction())
		{
			LuaAddChild(&(*actor), a);
		}
		LuaMoveX(&(*actor), -1000);
		LuaRef c = LuaGetChild(&(*actor), 0);
		Actor*k = c.cast<Actor*>();


		d = (PATH + "scripts/window.lua");
		luaL_dofile(L, d.c_str());
		luaL_openlibs(L);

		lua_pcall(L, 0, 0, 0);

		//Get table with window data
		LuaRef wTable = getGlobal(L, "window");
		//Get table with window size that is inside of window data table
		LuaRef wSize = wTable["size"];

		SCREENWIDTH = wSize["width"].cast<int>();
		SCREENHEIGHT = wSize["height"].cast<int>();
		
		PATH = wTable["mainPath"].cast<std::string>();
		

		std::string title = wTable["title"].cast<std::string>();



		Game game(title, sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), PATH);
		game.Init();

		game.Run();
	}
	catch (LuaException e)
	{
		std::cout << e.what() << std::endl;
	}

	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cin.get();
}