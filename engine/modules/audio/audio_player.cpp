#include "audio_player.h"

namespace Echo
{
	AudioPlayer::AudioPlayer()
	{
	}

	AudioPlayer::~AudioPlayer()
	{
		alDeleteSources(1, &m_source);
		alDeleteBuffers(1, &m_buffer);
	}

	void AudioPlayer::bindMethods()
	{
        CLASS_BIND_METHOD(AudioPlayer, getAudio, DEF_METHOD("getAudio"));
        CLASS_BIND_METHOD(AudioPlayer, setAudio, DEF_METHOD("setAudio"));

        CLASS_REGISTER_PROPERTY(AudioPlayer, "Audio", Variant::Type::ResourcePath, "getAudio", "setAudio");
	}

	void AudioPlayer::setPitch(float pitch)
	{
		m_pitch = pitch;

		alSourcef(m_source, AL_PITCH, 1);
	}

	void AudioPlayer::setGain(float gain)
	{
		m_gain = gain;

		alSourcef(m_source, AL_GAIN, 1);
	}

	void AudioPlayer::setLoop(bool loop)
	{
		m_isLoop = loop;

		alSourcei( m_source, AL_LOOPING, m_isLoop);
	}

	void AudioPlayer::update_self()
	{
		const Vector3& position = getWorldPosition();

		alSource3f(m_source, AL_POSITION, position.x, position.y, position.z);
		alSource3f(m_source, AL_VELOCITY, 0.f, 0.f, 0.f);
	}

	void AudioPlayer::play()
	{
		alGenSources(1, &m_source);
		alGenBuffers(1, &m_buffer);
        
        //put the data into our sampleset buffer
        loadBuff();
        
        //assign the buffer to this source
        alSourcei(m_source, AL_BUFFER, m_buffer);
        
        // play
        alSourcePlay( m_source);
	}
    
    void AudioPlayer::pause()
    {
        
    }
    
    void AudioPlayer::stop()
    {
        
    }
    
    bool AudioPlayer::loadBuff()
    {
        ALenum  audioFormat = 0;
        ALchar* audioBuffer = nullptr;
        ALint   audioBufferLen = 0;
        ALint   audioFrequency = 0;
        
        alBufferData(m_buffer, audioFormat, audioBuffer, audioBufferLen, audioFrequency);
        
        return true;
    }
    
    bool AudioPlayer::loadWav()
    {
         return false;
    }
    
    bool AudioPlayer::loadFlac()
    {
        return false;
    }
    
    bool AudioPlayer::loadMp3()
    {
        return false;
    }
}
