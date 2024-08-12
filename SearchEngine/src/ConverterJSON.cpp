#include "ConverterJSON.h"

std::vector<std::string>ConverterJSON::getTextDocuments()
{
	std::ifstream config("..\\SearchEngine\\config.json");
	if (!config.is_open())
	{
		throw СonfigFileIsNotOpenException();
	}

	config >> text;

	config.close();

	if (text["config"].empty())
	{
		throw ConfigFieldIsEmptyException();
	}

	for (int i = 0; i < text["files"].size(); i++)
	{
		std::string path = text["files"][i];
		std::string textt, line;
		std::ifstream file(path);
		while (!file.eof())
		{
			std::getline(file, line);
			textt += line + "\n";
		}
		textDocuments.push_back(textt);
	}

	for (int i = 0; i < textDocuments.size(); i++)
	{
		std::transform(textDocuments[i].begin(), textDocuments[i].end(), textDocuments[i].begin(), tolower);

		textDocuments[i].erase(std::remove_if(textDocuments[i].begin(), textDocuments[i].end(), [](auto ch) {
			if (ch == ',' || ch == '.' || ch == '!' || ch == ';' || ch == ':' || ch == '?' || ch == '(' || ch == ')' || ch == '-')
				return true;
			return false;
			}), textDocuments[i].end()
				);
	}

	return textDocuments;
}

int ConverterJSON::getResponsesLimit()
{
	int maxResponses = text["config"]["max_responses"];
	return maxResponses;
}

std::vector<std::string> ConverterJSON::getRequests()
{
	nlohmann::json requestsJSON;
	std::ifstream requests("..\\SearchEngine\\requests.json");
	requests >> requestsJSON;

	requests.close();

	for (int i = 0; i < requestsJSON["requests"].size(); i++)
	{
		requestList.push_back(requestsJSON["requests"][i]);
	}

	return requestList;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<size_t, float>>> answers)
{
	std::ofstream fileWithAnswers("..\\SearchEngine\\answers.json");
	fileWithAnswers.clear();
	text.clear();

	text["answers"];
	int i = 0;
	for (const auto& l : answers)
	{
		if (l.size() > 1)
		{
			text["answers"].push_back({ {"Request", i + 1} });
			text["answers"]["Request", i]["Result"] = "true";
			text["answers"]["Request", i]["relevance"];
		}
		else if (l.size() == 1)
		{
			text["answers"].push_back({ {"Request", i + 1} });
			text["answers"]["Request", i]["Result"] = "true";
		}
		else
		{
			text["answers"].push_back({ {"Request", i + 1}, {"Result", "false"} });
		}

		for (const auto& p : l)
		{
			if (l.size() > 1)
			{
				text["answers"]["Request", i]["relevance"].push_back({ "docid", p.first, "rank", p.second });
			}
			else if (l.size() == 1)
			{
				text["answers"]["Request", i]["docid"] = p.first;
				text["answers"]["Request", i]["rank"] = p.second;
			}
		}
		i++;
	}
	fileWithAnswers << text;
}
