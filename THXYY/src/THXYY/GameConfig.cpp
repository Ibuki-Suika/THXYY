//Suppress the "max" macro in Windows to avoid name confliction
#define NOMINMAX

#include "GameConfig.h"
#include "../External/rapidjson/document.h"
#include "../External/rapidjson/stringbuffer.h"
#include "../External/rapidjson/prettywriter.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace rapidjson;
using namespace THEngine;

bool GameConfig::Load()
{
	const std::string fileName = "config.json";

	std::ifstream reader;
	reader.open(fileName.c_str());
	if (reader.is_open() == false)
	{
		reader.close();
		return false;
	}

	//read json string from file
	std::stringstream ss;
	ss << reader.rdbuf();
	std::string json = ss.str();

	if (ParseJson(json) == false)
	{
		THMessageBox("警告：文件config.json中的配置非法。游戏将使用默认配置启动。请使用Config.exe修改配置。");
		return false;
	}

	return true;
}

void GameConfig::Save()
{
	const std::string fileName = "config.json";

	Document document;
	document.SetObject();
	SaveRenderConfig(document);
	SaveStartupConfig(document);

	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	writer.SetIndent(' ', 2);
	document.Accept(writer);

	std::ofstream of;
	of.open(fileName.c_str());
	if (of.is_open() == false)
	{
		of.close();
		return;
	}
	of << buffer.GetString();
	of.close();
}

bool GameConfig::ParseJson(const std::string& json)
{
	Document document;
	document.Parse(json.c_str());
	if (document.HasParseError())
	{
		return false;
	}

	if (LoadRenderConfig(document) == false)
	{
		return false;
	}

	if (LoadStartupConfig(document) == false)
	{
		return false;
	}

	return true;
}

void GameConfig::SetToDefault()
{
	//render settings
	useMultiSample = true;
	useVerticalAsync = true;
	lightLevel = LightLevel::HIGH;
	drawInterval = DrawInterval::ONE;

	//startup settings
	startupType = StartupType::WINDOW_640_480;
	askEveryTime = true;
}

void GameConfig::GetConfig(Config* config) const
{
	config->useMultiSample = this->useMultiSample;
	config->useVerticalAsync = this->useVerticalAsync;

	switch (this->lightLevel)
	{
	case LightLevel::NONE:
		config->useLighting = config->useShadow = false;
		break;
	case LightLevel::NORMAL:
		config->useLighting = true;
		config->useShadow = false;
		break;
	case LightLevel::HIGH:
		config->useLighting = config->useShadow = true;
		break;
	default:
		throw std::logic_error("Not implemented");
	}

	switch (this->startupType)
	{
	case StartupType::FULL_SCREEN_640_480:
		config->width = 640;
		config->height = 480;
		config->fullScreen = true;
		break;
	case StartupType::WINDOW_640_480:
		config->width = 640;
		config->height = 480;
		config->fullScreen = false;
		break;
	default:
		throw std::logic_error("Not implemented");
	}

	config->title = "东方星雨夜 ~ Legend of Dancing Stars";
}

bool GameConfig::LoadRenderConfig(const rapidjson::Document& document)
{
	if (ReadBool(document, "useMultiSample", &this->useMultiSample) == false)
	{
		return false;
	}

	if (ReadBool(document, "useVerticalAsync", &this->useVerticalAsync) == false)
	{
		return false;
	}

	int read;
	//Load LightShadowLevel
	if (ReadInt(document, "lightShadowLevel", &read) == false)
	{
		return false;
	}
	switch (read)
	{
	case 0:
		this->lightLevel = LightLevel::NONE;
		break;
	case 1:
		this->lightLevel = LightLevel::NORMAL;
		break;
	case 2:
		this->lightLevel = LightLevel::HIGH;
		break;
	default:
		return false;
	}

	//Load DrawInterval
	if (ReadInt(document, "drawInterval", &read) == false)
	{
		return false;
	}
	switch (read)
	{
	case 0:
		this->drawInterval = DrawInterval::ONE;
		break;
	case 1:
		this->drawInterval = DrawInterval::HALF;
		break;
	case 2:
		this->drawInterval = DrawInterval::ONE_THIRD;
		break;
	default:
		return false;
	}

	return true;
}

bool GameConfig::LoadStartupConfig(const rapidjson::Document& document)
{
	if (ReadBool(document, "askEveryTime", &this->askEveryTime) == false)
	{
		return false;
	}

	int read;
	if (ReadInt(document, "startupType", &read) == false)
	{
		return false;
	}
	switch (read)
	{
	case 0:
		this->startupType = StartupType::FULL_SCREEN_640_480;
		break;
	case 1:
		this->startupType = StartupType::WINDOW_640_480;
		break;
	default:
		return false;
	}

	return true;
}

void GameConfig::SaveRenderConfig(rapidjson::Document& document)
{
	AddBool(document, "useMultiSample", this->useMultiSample);
	AddBool(document, "useVerticalAsync", this->useVerticalAsync);
	AddInt(document, "lightShadowLevel", this->lightLevel);
	AddInt(document, "drawInterval", this->drawInterval);
}

void GameConfig::SaveStartupConfig(rapidjson::Document& document)
{
	AddInt(document, "startupType", this->startupType);
	AddBool(document, "askEveryTime", this->askEveryTime);
}

bool GameConfig::ReadBool(const rapidjson::Document& document, const char* member, bool* valueToSet)
{
	if (document.HasMember(member) == false)
	{
		return false;
	}

	if (document[member].IsBool() == false)
	{
		return false;
	}

	*valueToSet = document[member].GetBool();
	return true;
}

bool GameConfig::ReadInt(const rapidjson::Document& document, const char* member, int* valueToSet)
{
	if (document.HasMember(member) == false)
	{
		return false;
	}

	if (document[member].IsInt() == false)
	{
		return false;
	}

	*valueToSet = document[member].GetInt();
	return true;
}

void GameConfig::AddBool(rapidjson::Document& document, const char* member, bool value)
{
	Value v;
	v.SetBool(value);
	document.AddMember((Document::StringRefType)member, v, document.GetAllocator());
}

void GameConfig::AddInt(rapidjson::Document& document, const char* member, int value)
{
	Value v;
	v.SetInt(value);
	document.AddMember((Document::StringRefType)member, v, document.GetAllocator());
}