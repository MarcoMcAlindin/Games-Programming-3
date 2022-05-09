#include "SoundMgr.h"

SoundMgr* SoundMgr::pInstance = NULL;
/*
===========================================================================
Constructor
===========================================================================
*/
SoundMgr::SoundMgr()
{
}
/*
===========================================================================
Singleton Design Pattern
===========================================================================
*/
SoundMgr* SoundMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new SoundMgr();
	}
	return SoundMgr::pInstance;
}
void SoundMgr::add(const string sndName, const string fileName, soundType
	sndType)
{
	if (!getSnd(sndName.c_str()))
	{
		Sound* newSnd = new Sound(sndType);
		newSnd->load(fileName.c_str());
		gameSnds.insert(make_pair(sndName.c_str(), newSnd));
	}
}
Sound* SoundMgr::getSnd(const string sndName)
{
	map<const string, Sound*>::iterator snd = gameSnds.find(sndName.c_str());
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}
void SoundMgr::deleteSnd()
{
	for (map<const string, Sound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}
bool SoundMgr::initMixer()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		cout << "SDL_Init_AUDIO Failed: " << SDL_GetError() << endl;
		return false;
	}
	//Initialise SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)
		!= 0)
	{
		cout << "Mix_OpenAudio Failed: " << SDL_GetError() << endl;
		return false;
	}
	return true;
}
SoundMgr::~SoundMgr()
{
	deleteSnd();
	Mix_CloseAudio();
	Mix_Quit();
}
