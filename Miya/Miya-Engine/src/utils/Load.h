#pragma once
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glad/glad.h>

namespace Miya {
	class Load {
	public:
		static unsigned int loadTexture(const char*);
		static unsigned int loadCubemap(std::vector<std::string>);
	};
}