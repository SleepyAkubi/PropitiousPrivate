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
			glGenFramebuffersEXT(1, &gbuffer.fbo);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gbuffer.fbo);

		u32 depthRenderBuffer;
		// The depth buffer
		glGenRenderbuffersEXT(1, &depthRenderBuffer);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthRenderBuffer);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,
			GL_DEPTH_COMPONENT,
			(usize)gbuffer.width,
			(usize)gbuffer.height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
			GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER_EXT,
			depthRenderBuffer);

		std::vector<u32> drawBuffers;

		auto addRT = [&drawBuffers, w, h](Texture& tex,
			u32 attachment,
			i32 internalFormat,
			u32 format,
			u32 type)
		{
			if (!tex.object)
				glGenTextures(1, &tex.object);

			glBindTexture(GL_TEXTURE_2D, (u32)tex.object);
			glTexImage2D(GL_TEXTURE_2D,
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

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT,
				attachment,
				tex.object,
				0);

			if (attachment != GL_DEPTH_ATTACHMENT_EXT)
				drawBuffers.push_back(attachment);
		};

		addRT(gbuffer.diffuse, GL_COLOR_ATTACHMENT0_EXT, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);
		addRT(gbuffer.specular, GL_COLOR_ATTACHMENT1_EXT, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
		addRT(gbuffer.normal, GL_COLOR_ATTACHMENT2_EXT, GL_RGB10_A2, GL_RGBA, GL_FLOAT);
		addRT(gbuffer.depth, GL_DEPTH_ATTACHMENT_EXT, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);

		glDrawBuffers((i32)drawBuffers.size(), &drawBuffers[0]);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

		if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) !=
			GL_FRAMEBUFFER_COMPLETE_EXT)
		{
			return false;
		}

		return true;
	}

	template <>
	void unbind<GeometryBuffer>()
	{
		glFlush();

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
}
