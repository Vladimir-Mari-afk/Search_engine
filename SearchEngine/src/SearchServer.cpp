#include "SearchServer.h"


std::vector<std::vector<std::pair<size_t, float>>> SearchServer::search(std::vector<std::string>& queriesInput, int maxResponses)
{
    std::map<std::string, std::vector<Entry>> dict;

    if (!queriesInput.empty())
	{
        for (int i = 0; i < _index.getDocs().size(); i++)
        {
            std::string word;
            _index.getWordCount(word);
            _index.e.doc_id = i;
        }
        dict = _index.getFreqDict();
	}

    std::vector<std::vector<std::pair<size_t, float>>> answers(queriesInput.size());
    
    for (int i = 0; i < queriesInput.size(); i++)
    {
        std::string query = queriesInput[i];

        std::transform(query.begin(), query.end(), query.begin(), tolower);
        query.erase(std::remove_if(query.begin(), query.end(), [](auto ch) {
            return ch == ',' || ch == '.' || ch == '!' || ch == ';' || ch == ':' || ch == '?' || ch == '(' || ch == ')' || ch == '-';
        }), query.end());

        std::stringstream stream(query);
        std::map<std::string, int> uniqueList;
        std::string word;

        while (stream >> word)
        {
            uniqueList[word]++;
        }

        float absFrequency = 0;
        std::map<size_t, size_t> temp;

        for (const auto& it : uniqueList)
        {
            for (const auto& x : dict[it.first])
            {
                temp[x.doc_id] += x.count;

                if (absFrequency < temp[x.doc_id])
                {
                    absFrequency = temp[x.doc_id];
                }
            }
        }
 
        if (absFrequency > 0)
        {
            for (auto& it : temp)
            {
                ri.doc_id = it.first;
                answers[i].push_back({ ri.doc_id, it.second / absFrequency });
            }
        }

        temp.clear();
    }
    
    answers = sort(answers, maxResponses);

    return answers;
}

std::vector<std::vector<std::pair<size_t, float>>> SearchServer::sort(std::vector<std::vector<std::pair<size_t, float>>> answers, int maxResponses)
{
    for (int i = 0; i < answers.size(); i++)
    {
        std::sort(answers[i].begin(), answers[i].end(), [](auto& left, auto& right) {
            return left.second > right.second;
            });

        if (answers[i].size() > maxResponses)
        {
            answers[i].resize(maxResponses);
        }
    }

    return answers;
}