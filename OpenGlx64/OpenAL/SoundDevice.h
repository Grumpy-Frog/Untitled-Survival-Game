#pragma once
#include <AL\alc.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/// <summary>
/// Singleton class that initilizes our sound hardware device and allows
/// us to change our listener values.
/// </summary>

#define SD_INIT SoundDevice::Init();
#define LISTENER SoundDevice::Get()

class SoundDevice
{
private:
	SoundDevice();
	~SoundDevice();

	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;


public:
	static SoundDevice* Get();
	static void Init();

	void GetLocation(float &x, float& y, float& z);
	void GetOrientation(float &ori);
	float GetGain();

	void SetAttunation(int key);
	void SetLocation(const float& x, const float& y, const float& z);
	void SetLocation(glm::vec3 newPos);
	void SetOrientation(
		const float& atx, const float& aty, const float& atz,
		const float& upx, const float& upy, const float& upz);
	void SetGain(const float& val);

};

