#define _CRT_SECURE_NO_WARNINGS
#include <Propitious/Propitious.hpp>
#include <thread>

using namespace Propitious;

//static bool canF1Again = true;
GameClient* client;
GameServer* server;

/*
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
*/

static void loadMaterials()
{
	client->renderContext.textureHolder->insertFromFile("default_diffuse", "diffuse/default.bmp", TextureFilter::Nearest);
	client->renderContext.textureHolder->insertFromFile("default_normal", "normal/default.bmp", TextureFilter::Nearest);
	client->renderContext.textureHolder->insertFromFile("cat_diffuse", "diffuse/cat.bmp");
	client->renderContext.textureHolder->insertFromFile("grate_diffuse", "diffuse/thing.bmp");
	client->renderContext.textureHolder->insertFromFile("grate_normal", "normal/thing.bmp");
	client->renderContext.textureHolder->insertFromFile("brick_diffuse", "diffuse/brick.bmp");
	client->renderContext.textureHolder->insertFromFile("brick_normal", "normal/brick.bmp");
	client->renderContext.textureHolder->insertFromFile("stone_diffuse", "diffuse/rock.bmp");
	client->renderContext.textureHolder->insertFromFile("stone_normal", "normal/rock.bmp");
	//context.textureHolder->insertFromFile("terrain", "terrain.bmp", TextureFilter::Nearest);

	client->renderContext.meshHolder->insertFromFile("foo", "foo.obj");


	client->renderContext.materialHolder->addFromComponents("default", &client->renderContext.textureHolder->get("default_diffuse"), &client->renderContext.textureHolder->get("default_normal"));
	client->renderContext.materialHolder->addFromComponents("stone", &client->renderContext.textureHolder->get("stone_diffuse"), &client->renderContext.textureHolder->get("stone_normal"));
	client->renderContext.materialHolder->addFromComponents("cat", &client->renderContext.textureHolder->get("cat_diffuse"), &client->renderContext.textureHolder->get("default_normal"));
	client->renderContext.materialHolder->addFromComponents("grate", &client->renderContext.textureHolder->get("grate_diffuse"), &client->renderContext.textureHolder->get("grate_normal"));
	client->renderContext.materialHolder->addFromComponents("brick", &client->renderContext.textureHolder->get("brick_diffuse"), &client->renderContext.textureHolder->get("brick_normal"));
	//context.materialHolder->addFromComponents("terrain", &context.textureHolder->get("terrain"));
}

static void throwShaderCompileError()
{
	__debugbreak();
}

static void loadShaders()
{
	if (!client->renderContext.shaderHolder->insertFromFiles("deferredGeometryPass", "deferredGeometryPass.vs", "deferredGeometryPass.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("deferredPointLight", "deferredLightPass.vs", "deferredPointLight.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("deferredDirectionalLight", "deferredLightPass.vs", "deferredDirectionalLight.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("deferredAmbientLight", "deferredLightPass.vs", "deferredAmbientLight.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("deferredSpotLight", "deferredLightPass.vs", "deferredSpotLight.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("deferredOutput", "deferredLightPass.vs", "deferredOutput.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("flat", "flat.vs", "flat.fs"))
		throwShaderCompileError();
	if (!client->renderContext.shaderHolder->insertFromFiles("target", "deferredLightPass.vs", "target.fs"))
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
	client->renderContext.meshHolder->insert("sprite", std::move(sprite));

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

	client->renderContext.meshHolder->insert("quad", std::move(screenMesh));
}

void TestGame()
{
	BaseLight ambLight;
	ambLight.colour = { 25, 25, 25 };
	ambLight.brightness = 1.0f;
	client->renderSystem->ambientLight = ambLight;

	PointLight light;
	light.position = Vector3{ 0, 0, 0 };
	light.colour = Colour{ 255, 214, 170 };
	light.brightness = 5.0f;

	append(client->renderSystem->pointLights, light);

	EntityId crate = server->entityWorld.createEntity();
	server->entityWorld.components[crate] = ComponentName;
	EntityId player = server->entityWorld.createEntity();
	server->entityWorld.components[player] = ComponentName;
	EntityId cat = server->entityWorld.createEntity();
	server->entityWorld.components[cat] = ComponentName;

	server->entityWorld.names[player] = NameComponent{ "Cat" };
	server->entityWorld.names[crate] = NameComponent{ "crate" };
	server->entityWorld.names[cat] = NameComponent{ "cat" };

	Transform t{};
	t.position = { 0, 0, -1 };
	client->renderSystem->camera = new Camera();
	client->renderSystem->camera->transform.position = { -2, 0, 2 };
	client->renderSystem->camera->projectionType = ProjectionType::Perspective;

	Transform t2{};
	t2.position = { -2, 0, -2 };

	Transform t3{};
	t2.position = { 3, 0, -2 };

	NodeId p = server->entityWorld.sceneGraph.create(player, t2);
	NodeId c = server->entityWorld.sceneGraph.create(crate, t);
	NodeId catNode = server->entityWorld.sceneGraph.create(cat, t3);

	client->renderSystem->create(p, { client->renderContext.meshHolder->get("sprite"),	client->renderContext.materialHolder->get("stone") });
	client->renderSystem->create(c, { client->renderContext.meshHolder->get("sprite"),	client->renderContext.materialHolder->get("brick") });
	client->renderSystem->create(catNode, { client->renderContext.meshHolder->get("sprite"),	client->renderContext.materialHolder->get("cat") });
}

bool inited = false;

void initServer(const char* path)
{
	server = new GameServer(std::string(path));

	inited = true;

	server->run();
}

void initClient(const char* path)
{
	client = new GameClient(std::string(path));

	client->renderSystem->sceneGraph = &server->entityWorld.sceneGraph;

	loadShaders();
	loadMaterials();
	loadSpriteAsset();

	TestGame();

	client->run();
}

void init(const char* path)
{
	std::thread serverThread(initServer, path);
	serverThread.detach();
	while (!inited)
	{
	}
	std::thread clientThread(initClient, path);
	clientThread.detach();
	while (1)
	{

	}
}

EXPORT void gameInitialise(const char* gamePath)
{
	init(gamePath);
}