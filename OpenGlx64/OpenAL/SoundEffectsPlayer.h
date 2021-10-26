#pragma once
#include <AL\al.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class SoundEffectsPlayer
{
public:
	SoundEffectsPlayer();
	~SoundEffectsPlayer();

	void Play(const ALuint& buffer_to_play);
	void Stop();
	void Pause();
	void Resume();

	void SetBufferToPlay(const ALuint& buffer_to_play);
	void SetLooping(const bool& loop);
	void SetPosition(const float& x, const float& y, const float& z);
	void SetPosition(glm::vec3);

	bool isPlaying();

private:
	ALuint p_Source;
	ALuint p_Buffer = 0;
};

