#include "Sound.h"
using namespace std;
Sound::Sound()
{
	this->theSoundType = soundType::sfx;
}
Sound::Sound(soundType sndType)
{
	this->theSoundType = sndType;
}
Sound::~Sound()
{
}
bool Sound::load(const string filename)
{
	switch (this->theSoundType)
	{
	case soundType::sfx:
	{
		this->SoundFX = Mix_LoadWAV(filename.c_str());
		if (this->SoundFX == NULL)
		{
			cout << "Sound FX '" << filename << "' could not be loaded. " << SDL_GetError() << endl;
			return false;
		}
		cout << "Sound FX '" << filename << "' loaded successfully!. " << endl;
		return true;
	}
	break;
	case soundType::music:
	{
		this->sMusic = Mix_LoadMUS(filename.c_str());
		if (this->sMusic == NULL)
		{
			cout << "Music '" << filename << "' could not be loaded. " << SDL_GetError() << endl;
			return false;
		}
		cout << "Music '" << filename << "' loaded successfully!. " << endl;
		return true;
	}
	break;
	default:
		return false;
	}
}
void Sound::play(int loop)
{
	switch (this->theSoundType)
	{
	case soundType::sfx:
	{
		Mix_PlayChannel(-1, this->SoundFX, loop);
	}
	break;
	case soundType::music:
	{
		if (Mix_FadeInMusic(this->sMusic, loop, 2000) == -1) {
			printf("Mix_FadeInMusic: %s\n", Mix_GetError());
		}
	}
	break;
	default:
		Log::LOG_DEBUG("File of this type not found!!!");
		break;
	}
}

void Sound::Stop() {

		Mix_HaltChannel(-1);


}
