#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <cstdint>
namespace Miya {
	class Image {
	public:
		Image(const char* path);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		GLint* m_Texture;
	};
}