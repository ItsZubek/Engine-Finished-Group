#pragma once

#include "windows/Texture.h"
#include <glad/glad.h>
#include <string>
#include <stb_image.h>

namespace Engine
{
	class OpenGLTexture : public Texture
	{
	private:
		unsigned int m_numberTexture; //!< Texture ID
		int m_width; //!< width of the texture
		int m_height; //!< height of the texture
		int m_channels; //!< number of channels of the texture (1 = Grayscale, 3 = RGB, 4 = RGBA) 
		int m_slots = 0; //!< number of slots avalible for the texture
		static unsigned int s_slots;
	public:
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* textData); //!< constructor that reads raw data 
		OpenGLTexture(const std::string& filepath); //!< Constructor that reads from file

		unsigned int getWidth() override { return m_width; } //!< get the width of the texture
		unsigned int getHeight() override { return m_height; } //!< get the height of the exe
		unsigned int getChannels() override { return m_channels; } //!< get the number of channels for the texture ( 1 = grayscale, 3 = RGB, 4 = RGBA) 
		unsigned int getSlot() override { return m_slots; } //!< get the memoy slot in the GPU where the memory resides
		unsigned int setSlot(unsigned int slot) override { return slot = m_slots; } // Sets the Texture Slot
	};
}