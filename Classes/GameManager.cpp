#include "GameManager.h"
#include "Definitions.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <fstream>
#include <sstream>
#include <string>

GameManager* GameManager::instance;

bool GameManager::Init() {
	loadSettings();
	return true;
}

void GameManager::loadSettings()
{
	std::ifstream ifs("Resources/properties/data.json");
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);
	assert(doc.IsObject());

	assert(doc.HasMember("sfx"));
	assert(doc["sfx"].IsFloat());
	sfx = doc["sfx"].GetFloat();

	assert(doc.HasMember("music"));
	assert(doc["music"].IsFloat());
	music = doc["music"].GetFloat();
}