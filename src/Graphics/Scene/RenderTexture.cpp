#include <Propitious/Graphics/Scene/RenderTexture.hpp>
#include <vector>

namespace Propitious
{
	void create(RenderTexture& texture, u32 w, u32 h, RenderTexture::TextureType t)
	{
		if (!texture.fbo)
			glGenFramebuffersEXT(1, &texture.fbo);

		if (w == texture.width && h == texture.height && t == texture.type)
			return;

		texture.type = t;
		texture.width = w;
		texture.height = h;

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, texture.fbo);

		u32 depthRenderBuffer;
		glGenRenderbuffersEXT(1, &depthRenderBuffer);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthRenderBuffer);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, texture.width, texture.height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER_EXT, depthRenderBuffer);

		if (texture.type & RenderTexture::Colour)
		{
			if (!texture.colourTexture.object)
				glGenTextures(1, &texture.colourTexture.object);

			glBindTexture(GL_TEXTURE_2D, (u32)texture.colourTexture.object);

			if (texture.type == RenderTexture::Lighting)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, (u32)texture.width, (u32)texture.height, 0, GL_RGB, GL_FLOAT, 0);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, (u32)texture.width, (u32)texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			}

			texture.colourTexture.width = texture.width;
			texture.colourTexture.height = texture.height;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texture.colourTexture.object, 0);
		}
		else {
			if (!texture.depthTexture.object)
				glGenTextures(1, &texture.depthTexture.object);

			glBindTexture(GL_TEXTURE_2D, (u32)texture.depthTexture.object);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, (u32)texture.width, (u32)texture.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, texture.depthTexture.object, 0);
		}

		std::vector<u32> drawBuffers;
		if (texture.type & RenderTexture::Colour || texture.type & RenderTexture::Lighting)
		{
			drawBuffers.push_back(GL_COLOR_ATTACHMENT0_EXT);
		}
		else
		{
			drawBuffers.push_back(GL_DEPTH_ATTACHMENT_EXT);
		}
		glDrawBuffers((i32)drawBuffers.size(), &drawBuffers[0]);
	}

	void bind(const RenderTexture& renderTexture)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, renderTexture.fbo);
	}

	template <>
	inline void flush<RenderTexture>()
	{
		glFlush();
	}

	template <>
	inline void unbind<RenderTexture>()
	{
		glFlush();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
}
