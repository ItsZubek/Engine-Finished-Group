#include "engine_pch.h"

#include "platform/OpenGL/OpenGLTexture.h"

namespace Engine
{
	unsigned int OpenGLTexture::s_slots = 0;

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* textData)
	{


		// Set the location of the texture and specify width height and number of channels
		textData = stbi_load("assets/textures/letterCube.png", (int*)width, (int*)height, (int*)channels, 0);

		// generates a texture
		glGenTextures(1, &m_numberTexture);

		// sets the texture slot to be static as to not overwrite the previous slot
		m_slots = s_slots;
		s_slots++;

		// activates the texture slot and binds the texture 
		glActiveTexture(GL_TEXTURE0 + m_slots);
		glBindTexture(GL_TEXTURE_2D, m_numberTexture);

		// Sets the behaviour of the texture
		glTexParameteri(m_numberTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_numberTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(m_numberTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_numberTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set the location of the texture and specify width height and number of channels
		textData = stbi_load("assets/textures/numberCube.png", (int*)width, (int*)height, (int*)channels, 0);

		// Load the texture by identifying the number of chaneels
		if (textData)
		{


			if (channels == 3)
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
				glTexImage2D(m_numberTexture, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}

			else if (channels == 4) glTexImage2D(m_numberTexture, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);

			else if (channels == 1)
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(m_numberTexture, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, textData);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}
			else return;
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			return;
		}
		stbi_image_free(textData);
	}

	OpenGLTexture::OpenGLTexture(const std::string& filepath)
	{
		unsigned char* textData = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channels, 0);

		// generates a texture
		glGenTextures(1, &m_numberTexture);
		// sets the texture slot to be static as to not overwrite the previous slot
		m_slots = s_slots;
		s_slots++;

		// activates the texture slot and binds the texture 
		glActiveTexture(GL_TEXTURE0 + m_slots);
		glBindTexture(GL_TEXTURE_2D, m_numberTexture);

		// Sets the behaviour of the texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load the texture by identifying the number of channels
		if (textData)
		{
			if (m_channels == 3)
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}

			else if (m_channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);

			else if (m_channels == 1)
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, textData);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}
			else return;
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			return;
		}
		stbi_image_free(textData);
	}
}