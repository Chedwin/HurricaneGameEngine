#include <SDL_mixer.h>
#include "AudioEngine.h"
#include "Debug.h"
#include "HurricaneProperties.h"

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


AudioEngine::AudioEngine() 
{
	Init();
}


AudioEngine::~AudioEngine() {
	
}

void AudioEngine::Init() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void AudioEngine::Destroy()
{
}

void AudioEngine::LoadMusic(const STRING & path)
{
	//Music* mus = new Music();

}

void AudioEngine::LoadSoundFX(const STRING & path)
{

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

