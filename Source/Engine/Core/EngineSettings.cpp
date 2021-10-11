#include "EngineSettings.h"

#include "Logger.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

#include <sstream>
#include <fstream>

EngineSettings::EngineSettings()
{
	myFilepath = "Settings.json";
	myVersion = "0.1";
	myDefaultViewportHeight = 1280;
	myDefaultViewportWidth = 720;
}

EngineSettings::~EngineSettings()
{
}

void EngineSettings::Serialize()
{
	rapidjson::StringBuffer stringBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> stringWriter(stringBuffer);
	
	stringWriter.StartObject();

	stringWriter.String("Version");
#if RAPIDJSON_HAS_STDSTRING
	stringWriter.String(myVersion);
#else
	stringWriter.String(myVersion.c_str(), static_cast<rapidjson::SizeType>(myVersion.length()));
#endif

	stringWriter.String("DefaultViewportHeight");
	stringWriter.Int(myDefaultViewportHeight);

	stringWriter.String("DefaultViewportWidth");
	stringWriter.Int(myDefaultViewportWidth);

	stringWriter.EndObject();

	std::ofstream outstream(myFilepath.c_str(), std::ios_base::out);
	std::string payload = stringBuffer.GetString();
	outstream << payload;
	outstream.close();
}

void EngineSettings::Deserialize()
{
	std::string sourceResult;
	std::ifstream sourceStream(myFilepath, std::ios::in);

	if (!sourceStream.is_open())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "File can't be read: %s", myFilepath.c_str());
		return;
	}

	std::stringstream sourceStringStream;
	sourceStringStream << sourceStream.rdbuf();
	sourceResult = sourceStringStream.str();
	sourceStream.close();

	rapidjson::Document document;
	document.Parse(sourceResult.c_str());

	if (document.HasMember("Version") && document["Version"].IsString())
	{
		myVersion = document["Version"].GetString();
	}

	if (document.HasMember("DefaultViewportHeight") && document["DefaultViewportHeight"].IsInt())
	{
		myDefaultViewportHeight = document["DefaultViewportHeight"].GetInt();
	}

	if (document.HasMember("DefaultViewportWidth") && document["DefaultViewportWidth"].IsInt())
	{
		myDefaultViewportWidth = document["DefaultViewportWidth"].GetInt();
	}
}
