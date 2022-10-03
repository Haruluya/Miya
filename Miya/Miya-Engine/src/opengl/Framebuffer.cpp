#include "MYpch.h"
#include "Framebuffer.h"

#include "render/Renderer.h"

#include "OpenGLFramebuffer.h"

namespace Miya {

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{

		return std::make_shared<OpenGLFramebuffer>(spec);

	}

}
