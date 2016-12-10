//*******************************//
//
// Name:			AudioEngine.h
// Description:		Defines the audio manager for Hurricane.
//
// Author:			Edwin Chen
// Created:			Jul 18, 2016
// Last updated:	Dec 08, 2016
//
//*******************************//


#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <SDL_mixer.h>

#include "Macro.h"
#include "ResourceManager.h"

// ABSTRACT AUDIO CLASS
class Audio {
	friend class AudioEngine;
public:
	virtual ~Audio() {}

	virtual bool Init() = 0;
	virtual void Destroy() = 0;

	virtual bool Load(const STRING& path) = 0;
	virtual void Play() const = 0;
	virtual void Stop() const = 0;

public:
	_Mix_Music* MixMusic;

};

/////////////////////////////////////////////////////////////////////////////

// CONCRETE MUSIC AND SOUNDFX CLASSES DERIVING FROM AUDIO
class Music : public Audio {
	friend class AudioEngine;
public:
	Music() {}
	~Music() {
		Destroy();
	}

	bool Init();
	void Destroy();

	bool Load(const STRING& path);
	void Play() const;
	void Stop() const;
};

///////////////////////

class SoundFX : public Audio {
	friend class AudioEngine;
public:
	SoundFX() {}
	~SoundFX() {
		Destroy();
	}
	friend class AudioEngine;

	bool Init();
	void Destroy();

	bool Load(const STRING& path);
	void Play() const;
	void Stop() const;
};

/////////////////////////////////////////////////////////////////////////////

#define AUDIO AudioEngine::GetAudioEngine()

class AudioEngine {
protected:
	AudioEngine();
public:
	virtual ~AudioEngine();
	static AudioEngine* GetAudioEngine();

	void Init();
	void Destroy();

	void LoadMusic(const STRING& path);
	void LoadSoundFX(const STRING& path);

	void SetSFXVolume(const hFLOAT _vol);
	void SetMusicVolume(const hFLOAT _vol);
	void SetMaterVolume(const hFLOAT _vol);

private:
	static UNIQUE_PTR(AudioEngine) _audioEngine;
	friend DEFAULT_DELETE(AudioEngine);

	ResourceManager<SoundFX>	sfxList;
	ResourceManager<Music>		musicList;

public:
	hINT masterVol, musicVol, sfxVol;
};

#endif