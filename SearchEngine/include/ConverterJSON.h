#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <nlohmann/json.hpp>

class ConfigFieldIsEmptyException : public std::exception 
{
	const char* what() const noexcept override 
	{
		return "config file is empty";
	};
};

class СonfigFileIsNotOpenException : public std::exception
{
	const char* what() const noexcept override
	{
		return "config file is missing";
	}
};

class ConverterJSON
{
	std::string reqStr, docStr;
	nlohmann::json text;
	std::vector<std::string> textDocuments;
	std::vector<std::string> requestList;

public:

	std::vector<std::string> getTextDocuments();
	int getResponsesLimit();
	std::vector<std::string> getRequests();
	void putAnswers(std::vector<std::vector<std::pair<size_t, float>>> answers);
};
