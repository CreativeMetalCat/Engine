#include "Game.h"
#include "PhysicalObject.h"
#include "Character.h"
#include "SolidBlock.h"
#include "TestPlayer.h"

using namespace std;


void Game::Render()
{
	sf::Sprite LSprite;
	window.clear(sf::Color::White);
	
	
	sf::Shader unshadowShader;
	sf::Shader lightOverShapeShader;



	unshadowShader.loadFromFile("C:/Users/catgu/source/repos/Engine/x64/Debug/ltbl/resources/unshadowShader.vert", "C:/Users/catgu/source/repos/Engine/x64/Debug/ltbl/resources/unshadowShader.frag");
	lightOverShapeShader.loadFromFile("C:/Users/catgu/source/repos/Engine/x64/Debug/ltbl/resources/lightOverShapeShader.vert", "C:/Users/catgu/source/repos/Engine/x64/Debug/ltbl/resources/lightOverShapeShader.frag");


	sf::Texture penumbraTexture;
	penumbraTexture.loadFromFile("C:/Users/catgu/source/repos/Engine/x64/Debug/ltbl/resources/penumbraTexture.png");
	penumbraTexture.setSmooth(true);

	sf::Texture pointLightTexture;
	pointLightTexture.loadFromFile("C:/Users/catgu/source/repos/Engine/x64/Debug/ltbl/resources/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	ltbl::LightSystem ls;

	ls.create(sf::FloatRect(-1000.0f, -1000.0f, 1000.0f, 1000.0f), window.getSize(), penumbraTexture, unshadowShader, lightOverShapeShader);

	sf::Font calibri;
	if (calibri.loadFromFile(path + "fonts/calibri.ttf"))
	{
		sf::Text t = sf::Text("Hello", calibri);
		if (!SceneActors.empty())
		{
			t.setPosition(SceneActors.at(0)->As<PhysicalObject*>()->GetActorLocation());
		}
		window.draw(t);


	}
	else
	{
		std::cout << "Failed to load font" << std::endl;
	}


	if (!SceneActors.empty())
	{
		for (size_t i = 0; i < SceneActors.size(); i++)
		{


			if (SceneActors.at(i)->As<CSolidBlock*>())
			{

				SceneActors.at(i)->Draw(this->window);
				std::shared_ptr<ltbl::LightShape> lightShape = std::make_shared<ltbl::LightShape>();

				lightShape->_shape = SceneActors.at(i)->As<CSolidBlock*>()->CollisionShape;

				lightShape->_renderLightOverShape = true;
				lightShape->_shape.setPosition(SceneActors.at(i)->GetActorLocation());
				ls.addShape(lightShape);


			}

			if (SceneActors.at(i)->GetBody() != NULL)
			{


				sf::VertexArray va = sf::VertexArray
				(
					sf::PrimitiveType::LineStrip,
					static_cast<b2PolygonShape*>(SceneActors.at(i)->GetBody()->GetFixtureList()->GetShape())->m_count
				);


				for (int j = 0; j < static_cast<b2PolygonShape*>(SceneActors.at(i)->GetBody()->GetFixtureList()->GetShape())->m_count; j++)
				{
					//set point of shape

					va[j] = sf::Vertex
					(
						{
							//{...} is used as constructor of sf::Vector<float>
							static_cast<b2PolygonShape*>(SceneActors.at(i)->GetBody()->GetFixtureList()->GetShape())->m_vertices[j].x + SceneActors.at(i)->GetActorLocation().x,//x of point
							static_cast<b2PolygonShape*>(SceneActors.at(i)->GetBody()->GetFixtureList()->GetShape())->m_vertices[j].y + SceneActors.at(i)->GetActorLocation().y //y of point
						},
						sf::Color::Red
					);



				}




				window.draw(va);
			}
		}
	}

	sf::ConvexShape shape1;

	shape1.setPointCount(4);
	shape1.setPoint(0, sf::Vector2f(0, 0));
	shape1.setPoint(1, sf::Vector2f(80, 0));
	shape1.setPoint(2, sf::Vector2f(80, 80));
	shape1.setPoint(3, sf::Vector2f(0, 80));
	shape1.setPosition(100, 100);
	shape1.setFillColor(sf::Color::Green);
	window.draw(shape1);

	sf::ConvexShape shape2;
	shape2.setPointCount(4);
	shape2.setPoint(0, sf::Vector2f(0, 0));
	shape2.setPoint(1, sf::Vector2f(80, 0));
	shape2.setPoint(2, sf::Vector2f(80, 80));
	shape2.setPoint(3, sf::Vector2f(0, 80));
	shape2.setPosition(100, 100);
	shape2.setFillColor(sf::Color::Green);
	window.draw(shape2);

	sf::RenderStates lightRenderStates;

	std::shared_ptr<ltbl::LightPointEmission> light = std::make_shared<ltbl::LightPointEmission>();

	

	light->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));//Устанавливаем источник света в середину текстуры свечения.
	light->_emissionSprite.setTexture(pointLightTexture);// Сама текстура свечения.
	light->_emissionSprite.setScale(sf::Vector2f(10, 10));// Размер области свечения.
	light->_emissionSprite.setColor(sf::Color::White);// Цвет света.
	light->_emissionSprite.setPosition(SceneActors.at(0)->As<PhysicalObject*>()->GetActorLocation());//Позиция света.
	light->_sourceRadius = 10;//Радиус источника света.По умолчанию 1.
	light->_shadowOverExtendMultiplier = 1;// Умножитель отбрасываемой тени(в столько раз увеличиться тень). 
	
	ls.addLight(light);


	std::shared_ptr<ltbl::LightPointEmission> light1 = std::make_shared<ltbl::LightPointEmission>();



	light1->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));//Устанавливаем источник света в середину текстуры свечения.
	light1->_emissionSprite.setTexture(pointLightTexture);// Сама текстура свечения.
	light1->_emissionSprite.setScale(sf::Vector2f(10, 10));// Размер области свечения.
	light1->_emissionSprite.setColor(sf::Color::White);// Цвет света.
	light1->_emissionSprite.setPosition(SceneActors.at(1)->GetActorLocation());//Позиция света.
	light1->_sourceRadius = 10;//Радиус источника света.По умолчанию 1.
	light1->_shadowOverExtendMultiplier = 1;// Умножитель отбрасываемой тени(в столько раз увеличиться тень). 

	ls.addLight(light1);

	std::shared_ptr<ltbl::LightShape> lightShape = std::make_shared<ltbl::LightShape>();
	lightShape->_shape.setPointCount(4);
	lightShape->_shape.setPoint(0, sf::Vector2f(0, 0));
	lightShape->_shape.setPoint(1, sf::Vector2f(80, 0));
	lightShape->_shape.setPoint(2, sf::Vector2f(80, 80));
	lightShape->_shape.setPoint(3, sf::Vector2f(0, 80));
	lightShape->_renderLightOverShape = false;
	lightShape->_shape.setPosition(100, 100);
	ls.addShape(lightShape);

	std::shared_ptr<ltbl::LightShape> lightShape2 = std::make_shared<ltbl::LightShape>();
	lightShape2->_shape.setPointCount(4);
	lightShape2->_shape.setPoint(0, sf::Vector2f(0, 0));
	lightShape2->_shape.setPoint(1, sf::Vector2f(80, 0));
	lightShape2->_shape.setPoint(2, sf::Vector2f(80, 80));
	lightShape2->_shape.setPoint(3, sf::Vector2f(0, 80));
	lightShape2->_renderLightOverShape = false;
	lightShape2->_shape.setPosition(100, 300);
	ls.addShape(lightShape2);

	sf::View view = window.getDefaultView();

	view.setCenter(sf::Vector2f(1024 * 0.5f, 720 * 0.5f));

	ls.render(view, unshadowShader, lightOverShapeShader);

	
	LSprite.setTexture(ls.getLightingTexture());
	lightRenderStates.blendMode = sf::BlendMultiply;
	//window.setView(window.getDefaultView());
	window.setView(view);
	window.draw(LSprite, lightRenderStates);
	

	

	window.display();

	
}

void Game::ProccessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.key.code == sf::Keyboard::A&&event.type == sf::Event::EventType::KeyPressed)
		{
			using namespace luabridge;
			if (!SceneActors.empty())
			{
				
				lua_State* L = luaL_newstate();


				std::string d = (path + "scripts/actor.lua");
				try
				{

					luaL_dofile(L, d.c_str());
					luaL_openlibs(L);

					lua_pcall(L, 0, 0, 0);

					//Register CActor in lua
					CActor::RegisterClassLUA(L);

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



					LuaMoveX(&(*SceneActors.at(0)), -1);
				}
				catch (LuaException e)
				{
					std::cout << e.what() << std::endl;
				}

				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			SceneActors.at(1)->As<Character*>()->MoveX(-1);
			
		}
		if (event.key.code == sf::Keyboard::D&&event.type == sf::Event::EventType::KeyPressed)
		{
			using namespace luabridge;
			if (!SceneActors.empty())
			{

				lua_State* L = luaL_newstate();


				std::string d = (path + "scripts/actor.lua");
				try
				{

					luaL_dofile(L, d.c_str());
					luaL_openlibs(L);

					lua_pcall(L, 0, 0, 0);

					//Register CActor in lua
					CActor::RegisterClassLUA(L);

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



					LuaMoveX(&(*SceneActors.at(0)), 1);
				}
				catch (LuaException e)
				{
					std::cout << e.what() << std::endl;
				}

				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			SceneActors.at(1)->As<Character*>()->MoveX(1);		
		}
		if(event.key.code == sf::Keyboard::W&&event.type == sf::Event::EventType::KeyPressed)
		{
			SceneActors.at(1)->As<Character*>()->MoveY(-1);

			using namespace luabridge;
			if (!SceneActors.empty())
			{

				lua_State* L = luaL_newstate();


				std::string d = (path + "scripts/actor.lua");
				try
				{

					luaL_dofile(L, d.c_str());
					luaL_openlibs(L);

					lua_pcall(L, 0, 0, 0);

					//Register CActor in lua
					CActor::RegisterClassLUA(L);

					//Register Vector2 in lua
					getGlobalNamespace(L)
						.beginClass<sf::Vector2f>("Vector2")
						//add x,y and some functions possibly
						.addData<float>("x", &sf::Vector2<float>::x)
						.addData<float>("y", &sf::Vector2<float>::y)
						.addConstructor<void(*) (void)>()
						.endClass();


					LuaRef LuaSetActorLocation = getGlobal(L, "SetActorLocation");
					LuaRef LuaMoveX = getGlobal(L, "MoveY");
					LuaRef LuaAddChild = getGlobal(L, "AddChild");
					LuaRef LuaGetChild = getGlobal(L, "GetChild");



					LuaMoveX(&(*SceneActors.at(0)), -1);
				}
				catch (LuaException e)
				{
					std::cout << e.what() << std::endl;
				}

				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;
				}
			}

		}
		if (event.key.code == sf::Keyboard::S&&event.type == sf::Event::EventType::KeyPressed)
		{
			SceneActors.at(1)->As<Character*>()->MoveY(1);
			using namespace luabridge;
			if (!SceneActors.empty())
			{

				lua_State* L = luaL_newstate();


				std::string d = (path + "scripts/actor.lua");
				try
				{

					luaL_dofile(L, d.c_str());
					luaL_openlibs(L);

					lua_pcall(L, 0, 0, 0);

					//Register CActor in lua
					CActor::RegisterClassLUA(L);

					//Register Vector2 in lua
					getGlobalNamespace(L)
						.beginClass<sf::Vector2f>("Vector2")
						//add x,y and some functions possibly
						.addData<float>("x", &sf::Vector2<float>::x)
						.addData<float>("y", &sf::Vector2<float>::y)
						.addConstructor<void(*) (void)>()
						.endClass();


					LuaRef LuaSetActorLocation = getGlobal(L, "SetActorLocation");
					LuaRef LuaMoveX = getGlobal(L, "MoveY");
					LuaRef LuaAddChild = getGlobal(L, "AddChild");
					LuaRef LuaGetChild = getGlobal(L, "GetChild");



					LuaMoveX(&(*SceneActors.at(0)), 1);
				}
				catch (LuaException e)
				{
					std::cout << e.what() << std::endl;
				}

				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;
				}
			}
		}
		
	}
}

void Game::Update(sf::Time dt)
{
	//create lua state  for Game's own scripts
	lua_State* L = luaL_newstate();	

	world.Step(1 / dt.asSeconds(), 5, 5);

	

	SceneActors.at(1)->Update(dt);

	

	
}

void Game::Init()
{
	this->window.setFramerateLimit(60.f);
	world.Step(0, 0, 0);
	contactListener.path = path;
	

	std::shared_ptr<PhysicalObject> po = std::make_shared<PhysicalObject>(sf::Vector2f(0, 0),path, "Wooden_Crate");
	po->Init(path);
	SceneActors.push_back(po);
	sf::ConvexShape s;
	s.setPointCount(4);
	s.setPoint(0, { 0,0 });
	s.setPoint(1, { 50,0 });
	s.setPoint(2, { 50,50 });
	s.setPoint(3, { 0,50 });

	std::shared_ptr<Character> c = std::make_shared<Character>(s, sf::Vector2f(50,50 ), sf::Vector2f(300, 300), path);
	
	c->InitPhysBody(path,world);
	SceneActors.push_back(c);

	
	if (!devOrange64_64.loadFromFile(path + "textures/dev/dev_orange_64x64.png"))
	{
		std::cout << "Failed to load texture\n";
	}
	sf::ConvexShape dev64_64;
	dev64_64.setPointCount(4);
	dev64_64.setPoint(0, { 0,0 });
	dev64_64.setPoint(1, { 64,0 });
	dev64_64.setPoint(2, { 64,64 });
	dev64_64.setPoint(3, { 0,64 });

	for (int i = 0; i < 17; i++)
	{
		std::shared_ptr<CSolidBlock> sd = std::make_shared<CSolidBlock>(devOrange64_64, dev64_64, sf::Vector2f(64, 64), sf::Vector2f(i * 64, 500), path);
		sd->Init(path);
		sd->InitPhysBody(path, this->world);

		SceneActors.push_back(sd);
	}
	

	
	int i = 0;
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



Game::Game(std::string WindowName, sf::VideoMode videoMode,std::string path) :window(videoMode, WindowName),path(path), world(b2Vec2(0.f, 9.8f))
{
	world.SetContactListener(&contactListener);
}


Game::~Game()
{
}
