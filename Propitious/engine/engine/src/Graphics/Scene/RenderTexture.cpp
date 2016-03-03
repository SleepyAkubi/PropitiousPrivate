#include <Propitious/Graphics/Scene/RenderTexture.hpp>
#include <vector>

namespace Propitious
{
	void create(RenderTexture& texture, u32 w, u32 h, RenderTexture::TextureType t)
	{
		if (!texture.fbo)
			OpenGL::GenFramebuffers(1, &texture.fbo);

		if (w == texture.width && h == texture.height && t == texture.type)
			return;

		texture.type = t;
		texture.width = w;
		texture.height = h;

		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, texture.fbo);

		u32 depthRenderBuffer;
		OpenGL::GenRenderbuffers(1, &depthRenderBuffer);
		OpenGL::BindRenderbuffer(OpenGL::RENDERBUFFER, depthRenderBuffer);
		OpenGL::RenderbufferStorage(OpenGL::RENDERBUFFER, OpenGL::DEPTH_COMPONENT, texture.width, texture.height);
		OpenGL::FramebufferRenderbuffer(OpenGL::FRAMEBUFFER, OpenGL::DEPTH_ATTACHMENT, OpenGL::RENDERBUFFER, depthRenderBuffer);

		if (texture.type & RenderTexture::Colour)
		{
			if (!texture.colourTexture.object)
				OpenGL::GenTextures(1, &texture.colourTexture.object);

			OpenGL::BindTexture(OpenGL::TEXTURE_2D, (u32)texture.colourTexture.object);

			if (texture.type == RenderTexture::Lighting)
			{
				OpenGL::TexImage2D(OpenGL::TEXTURE_2D, 0, OpenGL::RGB10_A2, (u32)texture.width, (u32)texture.height, 0, OpenGL::RGB, OpenGL::FLOAT, 0);
			}
			else
			{
				OpenGL::TexImage2D(OpenGL::TEXTURE_2D, 0, OpenGL::RGB8, (u32)texture.width, (u32)texture.height, 0, OpenGL::RGB, OpenGL::UNSIGNED_BYTE, 0);
			}

			texture.colourTexture.width = texture.width;
			texture.colourTexture.height = texture.height;

			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MAG_FILTER, OpenGL::NEAREST);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MIN_FILTER, OpenGL::NEAREST);

			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_S, OpenGL::CLAMP_TO_EDGE);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_T, OpenGL::CLAMP_TO_EDGE);

			OpenGL::FramebufferTexture(OpenGL::FRAMEBUFFER, OpenGL::COLOR_ATTACHMENT0, texture.colourTexture.object, 0);
		}
		else {
			if (!texture.depthTexture.object)
				OpenGL::GenTextures(1, &texture.depthTexture.object);

			OpenGL::BindTexture(OpenGL::TEXTURE_2D, (u32)texture.depthTexture.object);

			OpenGL::TexImage2D(OpenGL::TEXTURE_2D, 0, OpenGL::DEPTH_COMPONENT24, (u32)texture.width, (u32)texture.height, 0, OpenGL::DEPTH_COMPONENT, OpenGL::FLOAT, 0);

			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MAG_FILTER, OpenGL::NEAREST);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MIN_FILTER, OpenGL::NEAREST);

			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_S, OpenGL::CLAMP_TO_EDGE);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_T, OpenGL::CLAMP_TO_EDGE);

			OpenGL::FramebufferTexture(OpenGL::FRAMEBUFFER, OpenGL::DEPTH_ATTACHMENT, texture.depthTexture.object, 0);
		}

		std::vector<u32> drawBuffers;
		if (texture.type & RenderTexture::Colour || texture.type & RenderTexture::Lighting)
		{
			drawBuffers.push_back(OpenGL::COLOR_ATTACHMENT0);
		}
		else
		{
			drawBuffers.push_back(OpenGL::DEPTH_ATTACHMENT);
		}
		OpenGL::DrawBuffers((i32)drawBuffers.size(), &drawBuffers[0]);
	}

	void bind(const RenderTexture& renderTexture)
	{
		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, renderTexture.fbo);
	}

	template <>
	inline void flush<RenderTexture>()
	{
		OpenGL::Flush();
	}

	template <>
	inline void unbind<RenderTexture>()
	{
		OpenGL::Flush();
		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, 0);
	}
}
