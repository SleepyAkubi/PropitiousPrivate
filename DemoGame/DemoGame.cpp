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
RenderSystem* g_renderSystem;

EntityWorld* g_world;

/*std::vector<PointLight> g_pointLights;
std::vector<DirectionalLight> g_directionalLights;
std::vector<SpotLight> g_spotLights;*/

std::vector<void*> pointerHitList;

Window g_window;

//BaseLight g_alight;

static RenderModes g_renderMode = RenderModes::Final;

namespace GameImp
{
	static bool canF1Again = true;

	static void update(Time dt)
	{
		f32 dts = dt.asSeconds();
		auto node = g_world->sceneGraph.getNodeId(1);
		auto pos = g_world->sceneGraph.getWorldPosition(node);

		if (Input::getKey(Key::Escape))
			running = false;

		if (Input::getKey(Key::W))
		{
			pos.z -= 1.0f * dts;
		}
		if (Input::getKey(Key::S))
		{
			pos.z += 1.0f * dts;
		}
		if (Input::getKey(Key::LeftShift))
		{
			pos.y -= 1.0f * dts;
		}
		if (Input::getKey(Key::Space))
		{
			pos.y += 1.0f * dts;
		}
		if (Input::getKey(Key::A))
		{
			pos.x -= 1.0f * dts;
		}
		if (Input::getKey(Key::D))
		{
			pos.x += 1.0f * dts;
		}
		if (Input::getKey(Key::F1) && canF1Again)
		{
			u32 nextVal = (u32)g_renderMode + 1;
			if (nextVal == (u32)RenderModes::MaxRenderModes)
				nextVal = 0;
			g_renderMode = (RenderModes)(nextVal);
			//Time::snooze(seconds(1));
			canF1Again = false;
		}
		else
			canF1Again = true;

		g_world->sceneGraph.setLocalPosition(node, pos);
	}

	static void loadMaterials()
	{
		context.textureHolder->insertFromFile("default_diffuse", "diffuse/default.bmp", TextureFilter::Nearest);
		context.textureHolder->insertFromFile("default_normal", "normal/default.bmp", TextureFilter::Nearest);
		context.textureHolder->insertFromFile("cat_diffuse", "diffuse/cat.bmp");
		context.textureHolder->insertFromFile("grate_diffuse", "diffuse/thing.bmp");
		context.textureHolder->insertFromFile("grate_normal", "normal/thing.bmp");
		context.textureHolder->insertFromFile("brick_diffuse", "diffuse/brick.bmp");
		context.textureHolder->insertFromFile("brick_normal", "normal/brick.bmp");
		context.textureHolder->insertFromFile("stone_diffuse", "diffuse/rock.bmp");
		context.textureHolder->insertFromFile("stone_normal", "normal/rock.bmp");
		//context.textureHolder->insertFromFile("terrain", "terrain.bmp", TextureFilter::Nearest);

		context.meshHolder->insertFromFile("foo", "foo.obj");


		context.materialHolder->addFromComponents("default", &context.textureHolder->get("default_diffuse"), &context.textureHolder->get("default_normal"));
		context.materialHolder->addFromComponents("stone", &context.textureHolder->get("stone_diffuse"), &context.textureHolder->get("stone_normal"));
		context.materialHolder->addFromComponents("cat", &context.textureHolder->get("cat_diffuse"), &context.textureHolder->get("default_normal"));
		context.materialHolder->addFromComponents("grate", &context.textureHolder->get("grate_diffuse"), &context.textureHolder->get("grate_normal"));
		context.materialHolder->addFromComponents("brick", &context.textureHolder->get("brick_diffuse"), &context.textureHolder->get("brick_normal"));
		//context.materialHolder->addFromComponents("terrain", &context.textureHolder->get("terrain"));
	}

	static void throwShaderCompileError()
	{
		__debugbreak();
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
		if (!context.shaderHolder->insertFromFiles("deferredOutput", "deferredLightPass.vs", "deferredOutput.fs"))
			throwShaderCompileError();
		if (!context.shaderHolder->insertFromFiles("target", "deferredLightPass.vs", "target.fs"))
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

		g_sprite.material = &context.materialHolder->get("brick");
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
	}

	static void render()
	{
		g_world->render(g_renderSystem, g_renderMode);
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
	g_world = new EntityWorld();

	auto& world = *g_world;

	g_renderSystem = new RenderSystem(defaultAllocator(), g_world->sceneGraph, context);
	g_renderSystem->context = context;

	world.sceneGraph.allocate(16);
	g_renderSystem->allocate(16);
	BaseLight ambLight;
	ambLight.colour = { 25, 25, 25 };
	ambLight.brightness = 1.0f;
	g_renderSystem->ambientLight = ambLight;

	PointLight light;
	light.position = Vector3{ 0, 0, 0 };
	light.colour = Colour{ 255, 214, 170 };
	light.brightness = 5.0f;

	append(g_renderSystem->pointLights, light);

	EntityId crate = world.createEntity();
	world.components[crate] = ComponentName;
	EntityId player = world.createEntity();
	world.components[player] = ComponentName;
	EntityId cat = world.createEntity();
	world.components[cat] = ComponentName;

	world.names[player] = NameComponent{ "Cat" };
	world.names[crate] = NameComponent{ "crate" };
	world.names[cat] = NameComponent{ "cat" };

	Transform t{};
	t.position = { 0, 0, -1 };
	g_renderSystem->camera = new Camera();
	g_renderSystem->camera->transform.position = { -2, 0, 2 };
	g_renderSystem->camera->projectionType = ProjectionType::Perspective;

	Transform t2{};
	t2.position = { -2, 0, -2 };

	Transform t3{};
	t2.position = { 3, 0, -2 };

	NodeId p = world.sceneGraph.create(player, t2);
	NodeId c = world.sceneGraph.create(crate, t);
	NodeId catNode = world.sceneGraph.create(cat, t3);

	g_renderSystem->create(p, { g_renderSystem->context.meshHolder->get("foo"), g_renderSystem->context.materialHolder->get("stone") });
	g_renderSystem->create(c, { g_renderSystem->context.meshHolder->get("sprite"), g_renderSystem->context.materialHolder->get("brick") });
	g_renderSystem->create(catNode, { g_renderSystem->context.meshHolder->get("sprite"), g_renderSystem->context.materialHolder->get("cat") });
}


void init(const char* path)
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

	context.textureHolder->setPath(std::string(path));
	context.meshHolder->setPath(std::string(path));
	context.shaderHolder->setPath(std::string(path));

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

EXPORT void gameInitialise(const char* gamePath)
{
	init(gamePath);
	run();
}