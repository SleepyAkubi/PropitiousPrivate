#include <Propitious/Graphics/GeometryBuffer.hpp>

#include <vector>

namespace Propitious
{
	bool create(GeometryBuffer& gbuffer, u32 w, u32 h)
	{
		if (w == gbuffer.width && h == gbuffer.height)
			return true;

		gbuffer.width = w;
		gbuffer.height = h;

		if (!gbuffer.fbo)
			OpenGL::GenFramebuffers(1, &gbuffer.fbo);

		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, gbuffer.fbo);

		u32 depthRenderBuffer;
		// The depth buffer
		OpenGL::GenRenderbuffers(1, &depthRenderBuffer);
		OpenGL::BindRenderbuffer(OpenGL::RENDERBUFFER, depthRenderBuffer);
		OpenGL::RenderbufferStorage(OpenGL::RENDERBUFFER,
			OpenGL::DEPTH_COMPONENT,
			(usize)gbuffer.width,
			(usize)gbuffer.height);
		OpenGL::FramebufferRenderbuffer(OpenGL::FRAMEBUFFER,
			OpenGL::DEPTH_ATTACHMENT,
			OpenGL::RENDERBUFFER,
			depthRenderBuffer);

		std::vector<u32> drawBuffers;

		auto addRT = [&drawBuffers, w, h](Texture& tex,
			u32 attachment,
			i32 internalFormat,
			u32 format,
			u32 type)
		{
			if (!tex.object)
				OpenGL::GenTextures(1, &tex.object);

			OpenGL::BindTexture(OpenGL::TEXTURE_2D, (u32)tex.object);
			OpenGL::TexImage2D(OpenGL::TEXTURE_2D,
				0,
				internalFormat,
				(usize)w,
				(usize)h,
				0,
				format,
				type,
				nullptr);
			tex.width = w;
			tex.height = h;

			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MAG_FILTER, OpenGL::LINEAR);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MIN_FILTER, OpenGL::LINEAR);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_S, OpenGL::REPEAT);
			OpenGL::TexParameteri(OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_T, OpenGL::REPEAT);

			OpenGL::FramebufferTexture(OpenGL::FRAMEBUFFER,
				attachment,
				tex.object,
				0);

			if (attachment != OpenGL::DEPTH_ATTACHMENT)
				drawBuffers.push_back(attachment);
		};

		addRT(gbuffer.diffuse, OpenGL::COLOR_ATTACHMENT0, OpenGL::RGB8, OpenGL::RGB, OpenGL::UNSIGNED_BYTE);
		addRT(gbuffer.specular, OpenGL::COLOR_ATTACHMENT1, OpenGL::RGBA8, OpenGL::RGBA, OpenGL::UNSIGNED_BYTE);
		addRT(gbuffer.normal, OpenGL::COLOR_ATTACHMENT2, OpenGL::RGB10_A2, OpenGL::RGBA, OpenGL::FLOAT);
		addRT(gbuffer.depth, OpenGL::DEPTH_ATTACHMENT, OpenGL::DEPTH_COMPONENT24, OpenGL::DEPTH_COMPONENT, OpenGL::FLOAT);

		OpenGL::DrawBuffers((i32)drawBuffers.size(), &drawBuffers[0]);

		OpenGL::BindTexture(OpenGL::TEXTURE_2D, 0);
		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, 0);

		if (OpenGL::CheckFramebufferStatus(OpenGL::FRAMEBUFFER) !=
			OpenGL::FRAMEBUFFER_COMPLETE)
		{
			return false;
		}

		return true;
	}

	template <>
	void unbind<GeometryBuffer>()
	{
		OpenGL::Flush();

		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, 0);
	}
}
