#include "AudioEngine.h"
#include "DebugLog.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MUSIC
bool Music::Init() {

	return true;
}

void Music::Destroy() {

}

bool Music::Load(const STRING& path) {
	return true;
}

void Music::Play() const {

}

void Music::Stop() const {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SOUNDFX
bool SoundFX::Init() {
	return true;
}

void SoundFX::Destroy() {

}

bool SoundFX::Load(const STRING& path) {
	return true;
}

void SoundFX::Play() const {

}

void SoundFX::Stop() const {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AUDIO ENGINE
UNIQUE_PTR(AudioEngine) AudioEngine::_audioEngine(nullptr);

AudioEngine* AudioEngine::GetAudioEngine() {
	if (_audioEngine.get() == nullptr) {
		_audioEngine.reset(new AudioEngine());
	}
	return _audioEngine.get();
}


AudioEngine::AudioEngine() {
}


AudioEngine::~AudioEngine() {
}

void AudioEngine::Init() {
}

void AudioEngine::Destroy()
{
}

Music AudioEngine::LoadMusic(const STRING & path)
{
	return Music();
}

SoundFX AudioEngine::LoadSoundFX(const STRING & path)
{
	return SoundFX();
}

void AudioEngine::SetSFXVolume(const hFLOAT _vol)
{
}

void AudioEngine::SetMusicVolume(const hFLOAT _vol)
{
}

void AudioEngine::SetMaterVolume(const hFLOAT _vol)
{
}
