#ifndef GAME_BASE_UTIL_H
#define GAME_BASE_UTIL_H

#include <vector>
#include <fstream>
#include <string>
#include <chrono>

namespace gameBase{
	typedef char s8;
	typedef short s16;
	typedef int s32;
	typedef long long s64;

	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef unsigned int u32;
	typedef unsigned long long u64;

	inline s64 getTime(){return (s64)(std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1));}
	void readFile(std::string, std::vector<std::string>&, int = 0, int = -1); 
	void writeFile(std::string, std::vector<std::string>&);
	std::string convert(std::string);
	int* fromStringToInt(std::string);
	std::string fromIntToString(int[3]);
	std::wstring stringToWstring(std::string);
	std::string wstringToString(std::wstring);
}

#endif
