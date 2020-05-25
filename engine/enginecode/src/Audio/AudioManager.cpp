#include "engine_pch.h"
#include "Audio/AudioManager.h"


namespace Engine 
{

	void AudioManager::Start() {
		errorCheck(FMOD::Studio::System::create(&m_studioSystem));
		errorCheck(m_studioSystem->initialize(m_maxChannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));

		unsigned int version;
		errorCheck(FMOD::System_Create(&m_lowLevelSystem));
		errorCheck(m_lowLevelSystem->getVersion(&version));

		if (version < FMOD_VERSION)
		{
			ENGINE_CORE_CRITICAL("FMOD lib version {0} doesn't match header version {1}", version, FMOD_VERSION);

		}
		errorCheck(m_lowLevelSystem->init(m_maxChannels, FMOD_INIT_NORMAL, NULL));
	}

	void AudioManager::Update() 
	{
		std::vector<std::map<int, FMOD::Channel*>::iterator> l_stoppedChannels;
		for (auto it = m_channels.begin(); it != m_channels.end(); it++)
		{
			bool isPlaying = false;
			it->second->isPlaying(&isPlaying);

			if (!isPlaying)
			{
				l_stoppedChannels.push_back(it);
			}
		}
		for (auto& it : l_stoppedChannels)
		{
			m_channels.erase(it);
		}

		errorCheck(m_lowLevelSystem->update());
		errorCheck(m_studioSystem->update());
	}

	void AudioManager::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream, float minDist, float maxDist)
	{
		auto it = m_sounds.find(strSoundName);
		if (it != m_sounds.end())
			return;
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D : FMOD_2D;
		eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
		FMOD::Sound* sound = nullptr;
		errorCheck(m_lowLevelSystem->createSound(strSoundName.c_str(), eMode, 0, &sound));
		if (b3d)
		{
			sound->set3DMinMaxDistance(minDist, maxDist);
		}
		if (sound != nullptr) {
			m_sounds[strSoundName] = sound;
		}
	}

	void AudioManager::UnLoadSound(const std::string& strSoundName)
	{
		auto it = m_sounds.find(strSoundName);
		if (it == m_sounds.end())
			return;
		errorCheck(it->second->release());
		m_sounds.erase(it);
	}

	int AudioManager::PlaySounds(const std::string& strSoundName, const glm::vec3& vPos, float fVolumedB)
	{
		int channelId = m_nextChannelId++;
		auto it = m_sounds.find(strSoundName);
		if (it == m_sounds.end())
		{
			LoadSound(strSoundName);
			it = m_sounds.find(strSoundName);
			if (it == m_sounds.end())
			{
				return channelId;
			}
		}
		FMOD::Channel* channel = nullptr;
		errorCheck(m_lowLevelSystem->playSound(it->second, 0, true, &channel));

		if (channel)
		{
			FMOD_MODE currMode;
			it->second->getMode(&currMode);
			if (currMode & FMOD_3D)
			{
				FMOD_VECTOR FVposition = VectorToFmod(vPos);
				errorCheck(channel->set3DAttributes(&FVposition, nullptr));
			}

			errorCheck(channel->setVolume(dbToVolume(fVolumedB)));
			errorCheck(channel->setPaused(false));
			m_channels[channelId] = channel;
		}
		return channelId;
	}

	void AudioManager::SetChannel3dPosition(int channelId, const glm::vec3& vPosition)
	{
		auto it = m_channels.find(channelId);
		if (it == m_channels.end())
			return;

		FMOD_VECTOR position = VectorToFmod(vPosition);
		errorCheck(it->second->set3DAttributes(&position, NULL));
	}

	void AudioManager::SetChannelVolume(int channelId, float fVolumedB)
	{
		auto it = m_channels.find(channelId);
		if (it == m_channels.end())
			return;

		errorCheck(it->second->setVolume(dbToVolume(fVolumedB)));
	}

	void AudioManager::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
		auto it = m_banks.find(strBankName);
		if (it != m_banks.end())
			return;
		FMOD::Studio::Bank* bank;
		errorCheck(m_studioSystem->loadBankFile(strBankName.c_str(), flags, &bank));
		if (bank) {
			m_banks[strBankName] = bank;
		}
	}

	void AudioManager::LoadEvent(const std::string& strEventName) {
		auto it = m_events.find(strEventName);
		if (it != m_events.end())
			return;
		FMOD::Studio::EventDescription* eventDescription = NULL;
		errorCheck(m_studioSystem->getEvent(strEventName.c_str(), &eventDescription));
		if (eventDescription) {
			FMOD::Studio::EventInstance* eventInstance = NULL;
			errorCheck(eventDescription->createInstance(&eventInstance));
			if (eventInstance) {
				m_events[strEventName] = eventInstance;
			}
		}
	}

	void AudioManager::PlayEvent(const std::string& strEventName) {
		auto it = m_events.find(strEventName);
		if (it == m_events.end()) {
			LoadEvent(strEventName);
			it = m_events.find(strEventName);
			if (it == m_events.end())
				return;
		}
		it->second->start();
	}

	void AudioManager::StopEvent(const std::string& strEventName, bool bImmediate) 
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;
		FMOD_STUDIO_STOP_MODE eMode;
		eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
		errorCheck(it->second->stop(eMode));
	}

	bool AudioManager::IsEventPlaying(const std::string& strEventName) const 
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return false;

		FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
		if (it->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) 
		{
			return true;
		}
		return false;
	}

	void AudioManager::GetEventParameter(const std::string& strEventName, const std::string& strParameterName, float* parameter) 
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;
		//FMOD::Studio::ParameterInstance* pParameter = NULL;
		//errorCheck(it->second->getParameter(strParameterName.c_str(), &pParameter));
		//errorCheck(pParameter->getValue(parameter));
	}

	void AudioManager::SetEventParameter(const std::string& strEventName, const std::string& strParameterName, float fValue) 
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;
		errorCheck(it->second->setParameterByName(strParameterName.c_str(), fValue));
	}

	FMOD_VECTOR AudioManager::VectorToFmod(const glm::vec3& vPosition)
	{
		FMOD_VECTOR fVec;
		fVec.x = vPosition.x;
		fVec.y = vPosition.y;
		fVec.z = vPosition.z;
		return fVec;
	}

	int errorCheck(FMOD_RESULT result) 
	{
		if (result != FMOD_OK) 
		{
			std::cout << "FMOD ERROR " << result << std::endl;
			return 1;
		}
		// cout << "FMOD all good" << endl;
		return 0;
	}

	float  AudioManager::dbToVolume(float dB)
	{
		return powf(10.0f, 0.05f * dB);
	}

	float  AudioManager::VolumeTodB(float volume)
	{
		return 20.0f * log10f(volume);
	}

	void AudioManager::Stop() 
	{
		delete m_lowLevelSystem;
		delete m_studioSystem;
	}
	int AudioManager::errorCheck(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cout << "FMOD ERROR " << result << std::endl;
			return 1;
		}
		// cout << "FMOD all good" << endl;
		return 0;
	}
}