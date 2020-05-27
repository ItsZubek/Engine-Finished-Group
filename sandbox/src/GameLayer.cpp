
#include "GameLayer.h"
#include "Profiler/profiler.h"

#include <glm/gtc/matrix_transform.hpp>

GameLayer::GameLayer(const std::string& name) : Layer(name), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
{


	//  Temporary set up code to be abstracted

	


	/*m_audiosystem.Start();
	m_audiosystem.LoadSound("assets/audio/movie_1.mp3");
	m_audiosystem.PlaySounds("assets/audio/movie_1.mp3", glm::vec3(0, 0, 0), m_audiosystem.VolumeTodB(1.0f));*/

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////Flat Colour Cube//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*float FCvertices[6 * 24] = {
		-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
		 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
		 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
		-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
		-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
		 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
		 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
		-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
		-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
		 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
		 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
		-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
		-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square
		 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
		 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
		-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
		-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square
		-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
		-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
		-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
		0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square
		0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
		0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
		0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
	};

	// Intiating the Vertex Array
	m_VertexArrayFC.reset(Engine::VertexArray::create());

	// Initiating the Vertex Buffer
	m_VertexBufferFC.reset(Engine::VertexBuffer::Create(FCvertices, sizeof(FCvertices)));


	// Initiating the Buffer Layout
	Engine::BufferLayout FCBufferLayout = { { ShaderDataType::Float3 }, { ShaderDataType::Float3 } };

	// Adds the Buffer Layout to the Vertex Buffer
	m_VertexBufferFC->setBufferLayout(FCBufferLayout);

	//Sets the Buffer Layout
	m_VertexArrayFC->setVertexBuffer(m_VertexBufferFC);

	unsigned int indices[3 * 12] = {
		2, 1, 0,
		0, 3, 2,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		14, 13, 12,
		12, 15, 14,
		18, 17, 16,
		16, 19, 18,
		20, 21, 22,
		22, 23, 20
	};



	// Initiating the Index Buffer
	m_IndexBufferFC.reset(Engine::IndexBuffer::Create(indices, 3 * 12));
	m_IndexBufferFC->Bind();
	m_VertexArrayFC->setIndexBuffer(m_IndexBufferFC);

	// Initiating the Shader
	m_ShaderFC.reset(Engine::Shader::create("assets/shaders/flatColour.glsl"));
	m_ShaderFC->Bind();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////Textured Phong Cube////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float TPvertices[8 * 24] = {
		-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
		 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
		 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
		-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
		-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
		 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
		 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
		-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
		-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
		 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
		 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
		-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
		-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
		 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
		 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
		-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
		-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
		-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
		-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
		-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
		0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
		0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
	};

	// Initiating the Vertex Array
	m_VertexArrayTP.reset(Engine::VertexArray::create());

	// Initiating the Vertex Buffer
	m_VertexBufferTP.reset(Engine::VertexBuffer::Create(TPvertices, sizeof(TPvertices)));

	// Initiating the Buffer Layout
	Engine::BufferLayout TPBufferLayout = { { ShaderDataType::Float3 }, { ShaderDataType::Float3 }, {ShaderDataType::Float2} };

	// Adds the Buffer Layout to the Vertex Buffer
	m_VertexBufferTP->setBufferLayout(TPBufferLayout);

	//Sets the Buffer Layout
	m_VertexArrayTP->setVertexBuffer(m_VertexBufferTP);

	// Initiating the Index Buffer
	m_IndexBufferTP.reset(Engine::IndexBuffer::Create(indices, 3 * 12));
	m_IndexBufferTP->Bind();
	m_VertexArrayTP->setIndexBuffer(m_IndexBufferTP);

	// Initiating the Shader
	m_ShaderTP.reset(Engine::Shader::create("assets/shaders/texturedPhong.glsl"));
	m_ShaderTP->Bind();

	// Initiating the Textures
	m_TextureTP.reset(Engine::Texture::createFromFile("assets/textures/letterCube.png"));
	m_TextureTP.reset(Engine::Texture::createFromFile("assets/textures/numberCube.png"));

	*/
}

void GameLayer::OnAttach()
{
	

	
}

void GameLayer::OnDetach()
{
	//m_audiosystem.Stop();
	/*delete boxWorld;
	boxWorld = nullptr;*/
}

void GameLayer::OnUpdate(float timestep)
{
	Engine::Profiler profiler("GameLayer::OnUpdate");
	 
	m_audiosystem.Update();

	// Code to make the cube move, you can ignore this more or less.
	/*glm::mat4 FCtranslation, TPtranslation;

	if (m_goingUp)
	{
		//FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
		TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f));
	}
	else
	{
		//FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
		TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f));
	}

	FCtranslation = FCmodel;
	if (m_FCdirection[1]) { FCtranslation = glm::translate(FCmodel, glm::vec3(-0.25f * timestep, 0.0f, 0.0f)); }
	if (m_FCdirection[3]) { FCtranslation = glm::translate(FCmodel, glm::vec3(0.25f * timestep, 0.0f, 0.0f)); }
	if (m_FCdirection[0]) { FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.25f * timestep, 0.0f)); }
	if (m_FCdirection[2]) { FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.25f * timestep, 0.0f)); }

	m_timeSummed += timestep;
	if (m_timeSummed > 20.0f) {
		m_timeSummed = 0.f;
		m_goingUp = !m_goingUp;
	}

	/*m_audiosystem.Start();
	m_audiosystem.LoadSound("assets/audio/movie_1.mp3");
	m_audiosystem.PlaySounds("assets/audio/movie_1.mp3", glm::vec3(0, 0, 0), m_audiosystem.VolumeTodB(1.0f));

	FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
	TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

	// End of code to make the cube move.

	glm::mat4 fcMVP = projection * view * FCmodel;

	{
		Engine::Profiler profiler("Flat Colour Cube");

	//Binds the Shader and Vertex Array for Flat Colour
	m_ShaderFC->Bind();
	m_VertexArrayFC->bind();

	// Uploads the Flat Colour Uniform to the Shader
	m_ShaderFC->UploadUniformMat4("u_MVP", &fcMVP[0][0]);
		
		
		glDrawElements(GL_TRIANGLES, m_IndexBufferFC->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	glm::mat4 tpMVP = projection * view * TPmodel;
	//m_TextureTP->getSlot();
	unsigned int textureSlot;
	if (m_goingUp) m_TextureTP->setSlot(0);
	else  m_TextureTP->setSlot(1);
	
	{
		Engine::Profiler profiler("Textured Phong Cube");
		//Binds the Shader and Vertex Array for Textured Phong
		m_ShaderTP->Bind();
		m_VertexArrayTP->bind();


		// Uploads the Textured Phong Uniforms to the Shader

		m_ShaderTP->UploadUniformMat4("u_MVP", &tpMVP[0][0]);

		m_ShaderTP->UploadUniformMat4("u_model", &TPmodel[0][0]);

		m_ShaderTP->uploadFloat3("u_objectColour", 0.2f, 0.8f, 0.5f);

		m_ShaderTP->uploadFloat3("u_lightColour", 1.0f, 1.0f, 1.0f);

		m_ShaderTP->uploadFloat3("u_lightPos", 1.0f, 4.0f, -6.0f);

		m_ShaderTP->uploadFloat3("u_viewPos", 0.0f, 0.0f, -4.5f);

		m_ShaderTP->uploadInt("u_texData", m_TextureTP->getSlot() /*textureSlot);

		glDrawElements(GL_TRIANGLES, m_IndexBufferTP->GetCount(), GL_UNSIGNED_INT, nullptr);

	}*/
}

void GameLayer::OnEvent(Engine::EventBaseClass& e)
{
	
}
