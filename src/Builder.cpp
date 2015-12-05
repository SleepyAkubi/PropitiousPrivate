#define _CRT_SECURE_NO_WARNINGS
#include <Propitious/Propitious.hpp>

#include "../src/Containers/Helpers/String.cpp"
#include "../src/Extras/Logger.cpp"
#include "../src/Graphics/Camera.cpp"
#include "../src/Graphics/GeometryBuffer.cpp"
#include "../src/Graphics/Image.cpp"
#include "../src/Graphics/Mesh.cpp"
#include "../src/Graphics/OpenGL.cpp"
#include "../src/Graphics/OpenGLImp.cpp"
#include "../src/Graphics/Scene/EntityWorld.cpp"
#include "../src/Graphics/Scene/RenderSystem.cpp"
#include "../src/Graphics/Scene/RenderTexture.cpp"
#include "../src/Graphics/Scene/SceneGraph.cpp"
#include "../src/Graphics/ShaderProgram.cpp"
#include "../src/Graphics/Texture.cpp"
#include "../src/Math/Functions/Matrix.cpp"
#include "../src/Math/Functions/Trivial.cpp"
#include "../src/Math/Hash.cpp"
#include "../src/Math/Matrix4.cpp"
#include "../src/Math/Quaternion.cpp"
#include "../src/Math/Vector2.cpp"
#include "../src/Math/Vector3.cpp"
#include "../src/Math/Vector4.cpp"
#include "../src/Memory/Memory.cpp"
#include "../src/System/SystemInfo.cpp"


#ifdef PROPITIOUS_SYSTEM_WINDOWS
#include "../src/USB/Device_Windows.cpp"
#include "../src/Graphics/Window_Windows.cpp"
#endif