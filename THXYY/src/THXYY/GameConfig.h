#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <THEngine.h>

using namespace THEngine;

namespace rapidjson
{
	template <typename BaseAllocator>
	class MemoryPoolAllocator;

	class CrtAllocator;

	template <typename Encoding, typename Allocator, typename StackAllocator>
	class GenericDocument;

	template<typename CharType>
	struct UTF8;

	typedef GenericDocument<UTF8<char>, MemoryPoolAllocator<CrtAllocator>, CrtAllocator> Document;
}

class GameConfig
{
public:
	enum LightLevel
	{
		NONE = 0,
		NORMAL = 1,
		HIGH = 2
	};

	enum DrawInterval
	{
		ONE = 0,
		HALF = 1,
		ONE_THIRD = 2
	};

	enum StartupType
	{
		FULL_SCREEN_640_480 = 0,
		WINDOW_640_480 = 1
	};

public:
	//render settings
	bool useMultiSample = true;
	bool useVerticalAsync = true;
	LightLevel lightLevel = LightLevel::HIGH;
	DrawInterval drawInterval = DrawInterval::ONE;

	//startup settings
	StartupType startupType = StartupType::WINDOW_640_480;
	bool askEveryTime = true;

private:
	bool ParseJson(const std::string& json);
	bool LoadRenderConfig(const rapidjson::Document& document);
	bool LoadStartupConfig(const rapidjson::Document& document);
	void SaveRenderConfig(rapidjson::Document& document);
	void SaveStartupConfig(rapidjson::Document& document);

	bool ReadBool(const rapidjson::Document& document, const char* member, bool* valueToSet);
	bool ReadInt(const rapidjson::Document& document, const char* member, int* valueToSet);
	void AddBool(rapidjson::Document& document, const char* member, bool value);
	void AddInt(rapidjson::Document& document, const char* member, int value);
public:
	bool Load();
	void Save();
	void SetToDefault();
	void GetConfig(Config* config) const;
};

#endif
