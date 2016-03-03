#include <Propitious/Game/Game.hpp>

#include <Propitious/Common.hpp>
#include <Propitious/Initialise.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Utility/TickCounter.hpp>
#include <Propitious/Containers/Array.hpp>
#include <Propitious/Containers/Hashmap.hpp>
#include <Propitious/Containers/String.hpp>

namespace Propitious
{
	GameClient::GameClient(const std::string& gamePath)
	{
		//HashMap<String> configFile;
		//load(configFile, (gamePath + "/gameinfo.pkv").c_str());

		//gameinfo.name = cString(get(configFile, hash("name")));
		gameinfo.path = gamePath;

		window.create("GameClient", { 1280, 720 }, WindowStyle::Windowed);
		
		OpenGL::init();
		OpenGL::Enable(OpenGL::CULL_FACE);
		OpenGL::CullFace(OpenGL::BACK);
		OpenGL::Enable(OpenGL::DEPTH_TEST);
		OpenGL::DepthFunc(OpenGL::LESS);

		OpenGL::ClearColor(0, 0, 0, 1);

		OpenGL::EnableVertexAttribArray((u32)AttribLocation::Position);
		OpenGL::EnableVertexAttribArray((u32)AttribLocation::TexCoord);
		OpenGL::EnableVertexAttribArray((u32)AttribLocation::Colour);
		OpenGL::EnableVertexAttribArray((u32)AttribLocation::Normal);
		OpenGL::EnableVertexAttribArray((u32)AttribLocation::Tangent);

		OpenGL::BlendFunc(OpenGL::ONE, OpenGL::ONE);

		renderContext =
		{
			&window,
			new ShaderManager,
			new MeshManager,
			new MaterialManager,
			new TextureManager,
			1.0f / 2.2f
		};

		renderContext.textureHolder->setPath(gamePath.c_str());
		renderContext.meshHolder->setPath(gamePath.c_str());
		renderContext.shaderHolder->setPath(gamePath.c_str());

		frameCap = true;
		frameTime = 60.0f;

		renderSystem = new DeferredRenderSystem(defaultAllocator(), &renderContext);
		renderSystem->camera = &camera;
		renderSystem->renderMode = DeferredRenderSystem::RenderMode::Final;
	}

	void GameClient::run()
	{
		TickCounter tc = { 0 };

		Time prevTime = Time::now();

		usize frames = 0;

		while (1)
		{
			Time currentTime = Time::now();
			Time dt = currentTime - prevTime;
			prevTime = currentTime;

			//update(dt);

#ifdef _DEBUG
			if (update(tc, milliseconds(500)))
			{
				window.setTitle(
					String(gameinfo.name.c_str()) + " | Debug - " + std::to_string((i32)tc.tickRate).c_str() + "fps | " + std::to_string(1000.0f / tc.tickRate).c_str() + (" ms"));
			}
#endif

			render();
		}
	}

	void GameClient::render()
	{
		world->render(renderSystem);

		window.display();
	}

	GameServer::GameServer(const std::string& gamePath)
		: entityWorld()
	{
		frameCap = false;
		frameTime = 1.0f / (60.0f + 0.5f);

		if (timeScale > 0.0f)
		{
			timeStep = frameTime / timeScale;
		}
		else
		{
			timeStep = 0;
		}
	}

	void GameServer::run()
	{
		while (1)
		{
			
		}
	}
}