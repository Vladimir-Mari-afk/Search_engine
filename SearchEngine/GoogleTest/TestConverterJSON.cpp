#include "gtest/gtest.h"
#include "ConverterJSON.h"

TEST(ConverterJSON, readConfig)
{
	std::ifstream config("..\\config.json");
	nlohmann::json text;
	if (config.is_open())
	{
		config >> text;
	}
	config.close();
	ASSERT_TRUE(!text.empty());
}

TEST(ConverterJSON, readRequests)
{
	std::ifstream request("..\\requests.json");
	nlohmann::json text;
	if (request.is_open())
	{
		request >> text;
	}
	request.close();
	ASSERT_TRUE(!text.empty());
}

TEST(ConverterJSON, getResponsesLimit)
{
	std::ifstream config("..\\config.json");
	nlohmann::json text;
	if (config.is_open())
	{
		config >> text;
	}
	
	config.close();
	ASSERT_TRUE(!text["config"]["max_responses"].empty());
}

TEST(ConverterJSON, getRequests)
{
	std::ifstream request("..\\requests.json");
	nlohmann::json text;
	if (request.is_open())
	{
		request >> text;
	}
	request.close();
	ASSERT_TRUE(!text["requests"].empty());
}

TEST(ConverterJSON, getFiles)
{
	std::ifstream config("..\\config.json");
	nlohmann::json text;
	if (config.is_open())
	{
		config >> text;
	}
	config.close();

	ASSERT_TRUE(!text["files"].empty());
}