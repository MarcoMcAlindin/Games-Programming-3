#include "pch.h"
#include "Log.h"

void Log::Debug(const std::string & msg, const char * file, int line)
{
	std::cout << "LOG DEBUG(" << file << ", " << line << "): " << msg << std::endl;
}

bool Log::CheckGLError(const char *file, int line)
{
	GLenum err;
	bool errorFound = false;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "GL ERROR(" << file << ", " << line << "): " << glewGetErrorString(err) << std::endl;
		errorFound = true;
	}

	return errorFound;
}

void Log::ConsoleLog(const std::string& msg, int colour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);

	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hConsole, 7);
}


void Log::PrintVec3(const std::string& msg,const float x, const float y , const float z, int colour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);

	std::cout << msg +  "Vector3 = (" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")" << std::endl;

	SetConsoleTextAttribute(hConsole, 7);
}



