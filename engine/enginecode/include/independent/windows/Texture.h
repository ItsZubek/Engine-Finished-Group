#pragma once

#include <string>

namespace Engine
{
	class Texture
	{
	private:

	public:
		virtual unsigned int getWidth() = 0; //!< get the width of the texture
		virtual unsigned int getHeight() = 0; //!< get the height of the exe
		virtual unsigned int getChannels() = 0; //!< get the number of channels for the texture ( 1 = grayscale, 3 = RGB, 4 = RGBA) 
		virtual unsigned int getSlot() = 0; //!< get the memoy slot in the GPU where the memory resides
		virtual unsigned int setSlot(unsigned int slot) = 0; // Sets the texture slot

		static Texture* createFromFile(const std::string& filepath); //!< Create an API specific texture
		static Texture* createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* textData); //!< Create an API specific texture

	};
}