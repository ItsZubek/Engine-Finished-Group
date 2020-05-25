#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "fmod_studio.hpp"
#include "fmod.hpp""
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>

namespace Engine {
	class AudioManager {
	public:
		void Start();
		void Update();
		void Stop();
		void LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
		void LoadEvent(const std::string& strEventName);
		void LoadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false, float minDist = 0.25f, float maxDist = 10000.f);
		void UnLoadSound(const std::string& strSoundName);
		void Set3dListenerAndOrientation(const glm::vec3& vPosition, const glm::vec3& vLook, const glm::vec3& vUp);
		int PlaySound(const std::string& strSoundName, const glm::vec3& vPos = glm::vec3{ 0, 0, 0 }, float fVolumedB = 0.0f);
		void PlayEvent(const std::string& strEventName);
		void PauseChannel(int nChannelId);
		void StopEvent(const std::string& strEventName, bool bImmediate = false);
		void GetEventParameter(const std::string& strEventName, const std::string& strEventParameter, float* value);
		void SetEventParameter(const std::string& strEventName, const std::string& strParameterName, float value);
		void PauseAllChannels();
		void SetChannel3dPosition(int nChannelId, const glm::vec3& vPosition);
		void SetChannelVolume(int nChannelId, float fVolumedB);
		bool IsPlaying(int nChannelId) const;
		bool IsEventPlaying(const std::string& strEventName) const;
		float dbToVolume(float dB);
		float VolumeTodB(float volume);
		FMOD_VECTOR VectorToFmod(const glm::vec3& vPosition);
	private:
		FMOD::Studio::System* m_studioSystem;
		FMOD::System* m_lowLevelSystem;

		static const int m_maxChannels = 32;
		int m_nextChannelId = 0;

		std::map<std::string, FMOD::Sound*> m_sounds;
		std::map<int, FMOD::Channel*> m_channels;
		std::map<std::string, FMOD::Studio::EventInstance*> m_events;
		std::map<std::string, FMOD::Studio::Bank*> m_banks;
		int errorCheck(FMOD_RESULT result) const;
		FMOD_VECTOR GLMVectoFmod(const glm::vec3& vec);

	};

#endif
}