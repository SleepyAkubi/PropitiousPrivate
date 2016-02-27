#ifndef PROPITIOUS_GAME_GAME_HPP
#define PROPITIOUS_GAME_GAME_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Camera.hpp>
#include <Propitious/Graphics/RenderContext.hpp>
#include <Propitious/Graphics/Scene/RenderSystem.hpp>
#include <Propitious/Graphics/Scene/EntityWorld.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT GameInfo
	{
		std::string name;
		std::string path;
	};

	class PROPITIOUS_EXPORT GameClient
	{
	public:
		GameClient(const std::string& gamePath);
		~GameClient();

		GameInfo gameinfo;

		Window window;
		Camera camera;
		RenderContext renderContext; 
		RenderSystem* renderSystem;
		EntityWorld* world;

		void render();
		void run();

		b8 frameCap;
		f32 frameTime;
	};
	
	class PROPITIOUS_EXPORT GameServer
	{
	public:
		GameServer(const std::string& gamePath);
		~GameServer();

		void run();

		GameInfo gameinfo;
		EntityWorld entityWorld;

		f32 timeScale;
		b8 frameCap;
		f32 timeStep;
		f32 frameTime;
	};

	//extern GameInfo g_GameInfo; //??
}

#endif