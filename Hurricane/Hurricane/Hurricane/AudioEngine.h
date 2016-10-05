//*******************************//
//
// Name:			AudioEngine.h
// Description:		Defines the audio manager for Hurricane.
//
// Author:			Edwin Chen
// Created:			Jul 18, 2016
// Last updated:	Sep 27, 2016
//
//*******************************//

#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "Macro.h"

// ABSTRACT AUDIO CLASS
class Audio {
public:
	virtual ~Audio() {}

	virtual bool Init() = 0;
	virtual void Destroy() = 0;

	virtual bool Load(const STRING& path) = 0;
	virtual void Play() const = 0;
	virtual void Stop() const = 0;

	friend class AudioEngine;
};

/////////////////////////////////////////////////////////////////////////////

// CONCRETE MUSIC AND SOUNDFX CLASSES DERIVING FROM AUDIO
class Music : public Audio {
protected:
	Music() {}
	~Music() {
		Destroy();
	}
public:
	friend class AudioEngine;

	bool Init();
	void Destroy();

	bool Load(const STRING& path);
	void Play() const;
	void Stop() const;
};

///////////////////////

class SoundFX : public Audio {
protected:
	SoundFX() {}
	~SoundFX() {
		Destroy();
	}
public:
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

	Music LoadMusic(const STRING& path);
	SoundFX LoadSoundFX(const STRING& path);

	void SetSFXVolume(const hFLOAT _vol);
	void SetMusicVolume(const hFLOAT _vol);
	void SetMaterVolume(const hFLOAT _vol);

private:
	static UNIQUE_PTR(AudioEngine) _audioEngine;
	friend DEFAULT_DELETE(AudioEngine);

	MAP(STRING, SoundFX*) _soundFX_List;
	MAP(STRING, Music*) _music_List;
public:
	hINT masterVol, musicVol, sfxVol;
};

#endif