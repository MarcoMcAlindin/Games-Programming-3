#pragma once
#include <string>
#ifdef _DEBUG
#define LOG_DEBUG(msg) Log::Debug(msg, __FILE__, __LINE__)
#define GL_ATTEMPT(func) func; \
	if(Log::CheckGLError(__FILE__, __LINE__)) __debugbreak()
#define CHECK_GL_ERROR() Log::CheckGLError(__FILE__, __LINE__)
#define CONSOLE_LOG_DEBUG(msg, colour) Log::ConsoleLog(msg, colour)
#define PRINT_VEC3(msg,x,y,z,colour) Log::PrintVec3(msg,x,y,z,colour);
#else //shouldn't really be outputting to console if this is a release build
#define LOG_DEBUG(msg)
#define GL_ATTEMPT(func) func
#define CHECK_GL_ERROR()
#endif

//TODO: implement different log levels
class Log
{
private:
	Log();
public:
	static void Debug(const std::string & msg, const char* file, int line);
	static bool CheckGLError(const char* file, int line);
	static void ConsoleLog(const std::string& msg, int colour);
	static void PrintVec3(const std::string& msg, const float x, const float y , const float z, int colour);
};



