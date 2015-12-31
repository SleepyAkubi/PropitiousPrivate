#define _CRT_SECURE_NO_WARNINGS
#include <Propitious/Propitious.hpp>

#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <utility>
#include <memory>

using namespace Propitious;

std::string title = "DemoGame";

bool running = false;

//bool fullscreen = false;

f32 timeScale = 1.0f;
b8 frameCap = true;
f32 frameTime;
b8 debugCamera = false;
f32 timeStep;

std::string g_dir;

ModelAsset g_sprite;
Camera g_normalCamera;

Camera g_debugCamera;

Camera* g_camera;

//Renderer g_renderer;

RenderContext context;

EntityWorld* g_world;

/*std::vector<PointLight> g_pointLights;
std::vector<DirectionalLight> g_directionalLights;
std::vector<SpotLight> g_spotLights;*/

std::vector<void*> pointerHitList;

Window g_window;

//BaseLight g_alight;

enum RenderModes
{
	Final,
	Lighting,
	Normal,
	Diffuse,
	Specular,
	Depth,
};

static RenderModes g_renderMode = Final;

namespace GameImp
{

	static void update(Time dt)
	{
		/*
		bEngine::update();
		g_rootNode.update(dt);

		SceneNode* player = g_rootNode.findChildByName("Player");
		SceneNode* partner = g_rootNode.findChildByName("PlayerPartner");


		g_renderer.update();

		#ifdef DEBUG

		if (Input::getKey(Key::Num1))
		{
		g_renderMode = Final;
		}

		if (Input::getKey(Key::Num2))
		{
		g_renderMode = Lighting;
		}

		if (Input::getKey(Key::Num3))
		{
		g_renderMode = Normal;
		}

		if (Input::getKey(Key::Num4))
		{
		g_renderMode = Diffuse;
		}

		if (Input::getKey(Key::Num5))
		{
		g_renderMode = Specular;
		}

		if (Input::getKey(Key::Num6))
		{
		g_renderMode = Depth;
		}

		#endif


		{

		if (Input::getKey(Key::Escape))
		running = false;

		if (Input::getKey(Key::F11))
		{
		g_window.setFullscreen(FullscreenMode::Fullscreen);

		}

		#ifdef DEBUG
		if (Input::getKey(Key::R))
		{
		if (debugCamera == false)
		{
		g_renderer.currentCamera = &g_debugCamera;
		player->getComponent<PlayerControlled>().controlsActive = false;
		debugCamera = true;
		}
		else
		{
		g_renderer.currentCamera = &g_normalCamera;
		player->getComponent<PlayerControlled>().controlsActive = true;
		debugCamera = false;
		}
		}

		if (debugCamera)
		{
		float cameraspeed = dt.asSeconds();
		Vector3 g_direction = { 0, 0, 0 };

		if (Input::getKey(Key::W))
		{
		g_direction += forward(g_debugCamera);
		}

		if (Input::getKey(Key::S))
		{
		g_direction += backwards(g_debugCamera);
		}

		if (Input::getKey(Key::LeftShift))
		{
		g_direction += {0, -1, 0};
		}

		if (Input::getKey(Key::Space))
		{
		g_direction += {0, 1, 0};
		}

		if (Input::getKey(Key::A))
		{
		g_direction += left(g_debugCamera);
		}
		if (Input::getKey(Key::D))
		{
		g_direction += right(g_debugCamera);
		}

		if (length(g_direction) > 0)
		g_direction = normalize(g_direction);

		position(g_debugCamera) += cameraspeed * g_direction * 10;

		Dimensions windowSize = g_window.getSize();
		Vector2 cPos = Input::getCursorPosition();

		const f32 mouseSensitivity = 0.6f;

		offsetOrientation(g_debugCamera, mouseSensitivity * Radian(-(cPos.x - windowSize.width / 2) * dt.asSeconds()),
		mouseSensitivity * Radian(-(cPos.y - windowSize.height / 2) * dt.asSeconds()));

		#ifdef BGAME_SYSTEM_WINDOWS
		Input::setCursorPosition(Vector2{ static_cast<f32>(windowSize.width / 2), static_cast<f32>(windowSize.height / 2) });
		#endif

		}
		#endif
		}
		// (player.transform.position.x > -0.1f && player.transform.position.x < 0.1f)
		if (player)
		{
		g_normalCamera.transform.position.x = lerp(g_normalCamera.transform.position.x, player->transform.position.x, dt.asSeconds());

		g_normalCamera.transform.position.y = lerp(g_normalCamera.transform.position.y, player->transform.position.y + 2, dt.asSeconds() * 2);
		}
		*/
	}

	static void loadMaterials()
	{
		context.textureHolder->insertFromFile("default", "default.bmp", TextureFilter::Nearest);
		context.textureHolder->insertFromFile("cat", "cat.bmp");
		context.textureHolder->insertFromFile("stone", "stone.bmp", TextureFilter::Nearest);
		context.textureHolder->insertFromFile("terrain", "terrain.bmp", TextureFilter::Nearest);

		context.materialHolder->addFromComponents("default", &context.textureHolder->get("default"));
		context.materialHolder->addFromComponents("stone", &context.textureHolder->get("stone"));
		context.materialHolder->addFromComponents("cat", &context.textureHolder->get("cat"));
		context.materialHolder->addFromComponents("terrain", &context.textureHolder->get("terrain"));
	}

	static void throwShaderCompileError()
	{
		/*bEngine::throwError("Computer says 'No'...",
			"Oh noes! A shader failed to compile... \n\n"
			"Your download probably failed and the file is corrupt or you've been mucking about with our shaders...\n"
			"How do you expect us to display the amazing graphics we spent hours on without working shaders?\n"
			"If you have been mucking around with our shaders, we assure you there is no possible way to improve on our shaders... Ok, maybe that's a lie.\n\n"
			"Try revalidating your game, that usually helps out here...\n"
			"If that doesn't fix it, please post on the game forums or Google around, you might find a solution; either method works.\n\n"
			"All other error messages have a meaningless error code so here's a bunch of random numbers that will help you with nothing:\n"
			"1763512fx00c\n"
			"Oh! We added some random f's, x's and c's in there just to make it more professional like the ones you get on BSoDs to make it seem scary.\n"
			"It's not actually bad so don't be afraid... Just follow the advice, yeah... That should fix it."
			);*/
	}

	static void loadShaders()
	{
		if (!context.shaderHolder->insertFromFiles("deferredGeometryPass", "deferredGeometryPass.vs", "deferredGeometryPass.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("deferredPointLight", "deferredLightPass.vs", "deferredPointLight.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("deferredDirectionalLight", "deferredLightPass.vs", "deferredDirectionalLight.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("deferredAmbientLight", "deferredLightPass.vs", "deferredAmbientLight.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("deferredSpotLight", "deferredLightPass.vs", "deferredSpotLight.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("deferredOutput", "target.vs", "deferredOutput.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("target", "target.vs", "target.fs"))
			throwShaderCompileError();
	}

	static void loadSpriteAsset()
	{
		MeshData meshData;

		using namespace Propitious::Memory;

		append(meshData.vertices, vertex({ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }));
		append(meshData.vertices, vertex({ +0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }));
		append(meshData.vertices, vertex({ +0.5f, +0.5f, 0.0f }, { 1.0f, 1.0f }));
		append(meshData.vertices, vertex({ -0.5f, +0.5f, 0.0f }, { 0.0f, 1.0f }));


		addFace(meshData, 0, 1, 2);
		addFace(meshData, 2, 3, 0);
		generateNormals(meshData);

		std::unique_ptr<Mesh> sprite = make_unique<Mesh>();
		*sprite.get() = generate(meshData);

		context.meshHolder->insert("sprite", std::move(sprite));

		g_sprite.material = &context.materialHolder->get("cat");
		g_sprite.mesh = &context.meshHolder->get("sprite");

		// Screen
		MeshData screenMeshData;


		append(screenMeshData.vertices, vertex({ +1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f }));
		append(screenMeshData.vertices, vertex({ -1.0f, +1.0f, 0.0f }, { 1.0f, 0.0f }));
		append(screenMeshData.vertices, vertex({ -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }));
		append(screenMeshData.vertices, vertex({ +1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f }));


		addFace(screenMeshData, 0, 1, 2);
		addFace(screenMeshData, 2, 3, 0);
		generateNormals(screenMeshData);

		std::unique_ptr<Mesh> screenMesh = make_unique<Mesh>();
		*screenMesh.get() = generate(screenMeshData);

		context.meshHolder->insert("quad", std::move(screenMesh));

	}

	static void generateWorld()
	{
		//g_rootNode.onStart();
	}

	static void loadScene()
	{
		/*
		{
		auto player = make_unique<SceneNode>();

		player->name = "Player";
		player->addComponent<MeshRenderer>(g_sprite);
		player->addComponent<PlayerControlled>();
		player->transform.position = { 0,0,0 };
		player->transform.scale = { 1,1,1 };

		auto partner = make_unique<SceneNode>();

		partner->name = "PlayerPartner";
		partner->addComponent<MeshRenderer>(g_sprite);
		partner->addComponent<Sprite>(g_renderer);
		partner->addComponent<PlayerPartner>(player.get());
		partner->transform.position = { 0,0,0 };
		partner->transform.scale = { 1,0.5,1 };

		g_rootNode.attachChild(std::move(player));
		g_rootNode.attachChild(std::move(partner));
		}

		generateWorld();

		g_alight.brightness = 1.00f;
		g_alight.colour = Colour{ static_cast<u8>(0.169f * 255), static_cast<u8>(0.188f * 255), static_cast<u8>(0.231f * 255) };

		{
		DirectionalLight light;
		light.brightness = 0.5f;
		light.colour = Colour{ 255, 255, 250 };
		light.direction = Vector3{ -1.0f, -1.0f, 0.5f };

		g_directionalLights.push_back(light);
		}


		{
		PointLight light;
		light.position = Vector3{ 0, 3, 0 };
		light.colour = Colour{ 255, 214, 170 };
		light.brightness = 10.0f;

		g_pointLights.push_back(light);
		}


		{
		SpotLight light;
		light.brightness = 2.0f;
		light.colour = Colour{ 255, 255, 250 };
		light.direction = Vector3{ 0, -1, 0 };
		light.position = Vector3{ 3, 3, 3 };

		g_spotLights.push_back(light);
		}


		Vector3& camPos = g_normalCamera.transform.position;

		camPos = { 0, 2, 7 };
		g_renderer.gamma = 1.0f / 2.0f;

		lookAt(g_normalCamera, Vector3{ 0,0,0 });
		g_normalCamera.projectionType = ProjectionType::Perspective;
		g_normalCamera.fieldOfView = Degree(75.0f);
		#ifdef DEBUG
		lookAt(g_debugCamera, Vector3{ 0,0,0 });
		g_debugCamera.projectionType = ProjectionType::Perspective;
		g_debugCamera.fieldOfView = Degree(90.0f);
		#endif
		*/

		PointLight light;
		light.position = Vector3{ 0, 3, 0 };
		light.colour = Colour{ 255, 214, 170 };
		light.brightness = 10.0f;

		append(g_world->renderSystem.pointLights, light);
	}

	static void render()
	{

		/*g_renderer.clear();
		g_renderer.addDrawable(g_rootNode);

		for (const auto& light : g_pointLights)
		g_renderer.addPointLight(&light);
		for (const auto& light : g_directionalLights)
		g_renderer.addDirectionalLight(&light);
		for (const auto& light : g_spotLights)
		g_renderer.addSpotLight(&light);

		g_renderer.setAmbientLight(&g_alight);

		//Vector2 fbSize = Window::getFramebufferSize();
		Dimensions windowSize = g_window.getSize();

		create(g_renderer.gBuffer, windowSize.width, windowSize.height);

		g_renderer.geometryPass();
		g_renderer.lightPass();
		g_renderer.outPass();

		bEngine::clear(windowSize.width, windowSize.height);

		auto& shaders = context.shaderHolder->get("target");

		shaders.use();
		shaders.setUniform("u_tex", 0);

		#ifdef DEBUG
		switch (g_renderMode)
		{
		case(Final) : bind(g_renderer.outTexture.colourTexture, 0);			break;
		case(Lighting) : bind(g_renderer.lightingTexture.colourTexture, 0);	break;
		case(Normal) : bind(g_renderer.gBuffer.normal, 0);					break;
		case(Diffuse) : bind(g_renderer.gBuffer.diffuse, 0);					break;
		case(Specular) : bind(g_renderer.gBuffer.specular, 0);					break;
		case(Depth) : bind(g_renderer.gBuffer.depth, 0);					break;
		}
		#else
		Texture::bind(&g_renderer.outTexture.colourTexture, 0);
		#endif

		g_renderer.draw(&context.meshHolder->get("quad"));

		g_window.display();*/

		g_world->render();
		g_window.display();
	}

	static void initSettings()
	{
		//Settings::load();

		//frameCap = Settings::lockFrameRate;
		//frameTime = 1.0f / (Settings::framerate + 0.5f);

		frameCap = false;
		frameTime = 1.0f / (60.0f + 0.5f);

		//Window::initialWidth = Settings::width;
		//Window::initialHeight = Settings::height;
	}
}

using namespace GameImp;

void Test()
{
	g_world = new EntityWorld(context);


	auto& world = *g_world;

	world.setContext(context);

	//world.sceneGraph.allocate(16);
	//world.renderSystem.allocate(16);

	EntityId crate = world.createEntity();
	EntityId player = world.createEntity();

	world.components[player] = ComponentName;
	world.components[crate] = ComponentName;
	world.names[player] = NameComponent{ "Cat" };
	world.names[crate] = NameComponent{ "crate" };

	Transform t{};
	t.position = { 0, 0, -2 };

	Transform t2{};
	t2.position = { -1, 0, 2 };

	NodeId p = world.sceneGraph.create(player, t);
	NodeId c = world.sceneGraph.create(crate, t2);

	world.renderSystem.create(p, { world.renderSystem.context.meshHolder->get("sprite"), world.renderSystem.context.materialHolder->get("cat") });
	world.renderSystem.create(c, { world.renderSystem.context.meshHolder->get("sprite"), world.renderSystem.context.materialHolder->get("default") });
}


void init()
{
	Propitious::initialise(Propitious::InitMemory);

	//Holders::ShaderHolder = new Holders::ShaderManager();
	//Holders::TextureHolder = new Holders::TextureManager();

	g_window.create("DemoGame", { 1280, 720 }, WindowStyle::Windowed);

	Propitious::initialise(Propitious::InitOpenGL);

	context =
	{
		&g_window,
		new ShaderManager,
		new MeshManager,
		new MaterialManager,
		new TextureManager,
		1.0f / 2.2f
	};

	//world.sceneGraph.setLocalTransform(c, t);

	g_dir = Propitious::getPathToExe();
	//g_renderer.currentCamera = &g_normalCamera;

	initSettings();

	if (timeScale > 0.0f)
	{
		timeStep = frameTime / timeScale;
	}
	else
	{
		timeStep = 0;
	}

	loadShaders();
	loadMaterials();
	loadSpriteAsset();

	Test();
	loadScene();
}

void run()
{
	TickCounter tc = { 0 };

	Time prevTime = Time::now();

	usize frames = 0;

	running = true;
	while (running)
	{
		Time currentTime = Time::now();
		Time dt = currentTime - prevTime;
		prevTime = currentTime;

#if defined(DEBUG)
		if (Development::developerFunctionQueue.size() > 0)
		{
			for (auto& pair : Development::developerFunctionQueue)
			{
				while (Development::queueMutex.try_lock() == false) {}
				pair.first(pair.second);
				Development::queueMutex.unlock();
			}

			Development::developerFunctionQueue.clear();
		}
#endif
		update(dt);

		if (update(tc, milliseconds(500)))
		{
			g_window.setTitle(
				title + " | Debug - " + std::to_string((i32)tc.tickRate) + "fps | " + std::to_string(1000.0f / tc.tickRate) + (" ms"));
		}


		render();
	}

}

int main(int, char**)
{
	init();
	run();
}