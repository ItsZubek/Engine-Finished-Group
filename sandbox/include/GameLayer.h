#pragma once
#include "events/WindowEvents.h"
#include "events/KeyEvents.h"
#include "events/MouseEvents.h"


#include "windows/Shader.h"
#include "windows/Buffer.h"
#include "windows/Texture.h"
#include "windows/OrthographicCamera.h"

#include "Profiler/Profiler.h"




#include "core/application.h"
#include "Layer/Layer.h"

#include"Audio/AudioManager.h"

#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <gl/GL.h>


		 


#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public Engine::Layer
{
private:
	glm::mat4 FCmodel, TPmodel;

	std::shared_ptr<Engine::Shader> m_ShaderFC; //!< Pointer to a shader class
	std::shared_ptr<Engine::Shader> m_ShaderTP; //!< Pointer to a shader class

	std::shared_ptr<Engine::VertexArray> m_VertexArrayFC; //!< Pointer to a Vertex Array Class
	std::shared_ptr<Engine::VertexArray> m_VertexArrayTP; //!< Pointer to a Vertex Array Class

	std::shared_ptr<Engine::VertexBuffer> m_VertexBufferFC; //!< Pointer to a Vertex Buffer class
	std::shared_ptr<Engine::VertexBuffer> m_VertexBufferTP; //!< Pointer to a Vertex Buffer class

	std::shared_ptr<Engine::IndexBuffer> m_IndexBufferFC; //!< Pointer to a Index Buffer class
	std::shared_ptr<Engine::IndexBuffer> m_IndexBufferTP; //!< Pointer to a Index Buffer class

	

	Engine::OrthographicCamera m_Camera; //!< Orthographic Camera

	std::shared_ptr<Engine::Texture> m_TextureTP;

	//Engine::AudioManager m_audiosystem;


	
	unsigned int m_numberTexture; // Texture ID
	unsigned int m_letterTexture; // Texture ID
	unsigned int m_textureSlots[2]; // Slot where the textures are stored
	bool m_goingUp = false; // Is the cude going up?
	float m_timeSummed = 10.f; // How much timer has elasped?

	//glm::mat4 FCtranslation = glm::mat4(1.0f);
	std::array<bool, 4> m_FCdirection = { false, false, false, false };

public:
	GameLayer(const std::string& name = "Layer");
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float timestep) override;
	void OnImGuiRender();
	void OnEvent(Engine::EventBaseClass& e) override;

	
};