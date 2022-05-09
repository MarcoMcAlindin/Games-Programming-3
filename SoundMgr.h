#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H
// OpenGL Headers
#include "pch.h"
#include "Common.h"
#include "Sound.h"
#include <map>
using namespace std;
class SoundMgr
{
private:
	static SoundMgr* pInstance;
protected:
	SoundMgr();
	~SoundMgr();
	map<const string, Sound*> gameSnds;
public:
	void add(const string sndName, const string fileName, soundType sndType);
	Sound* getSnd(const string sndName);
	void deleteSnd();
	bool initMixer();
	static SoundMgr* getInstance();
};
#endif