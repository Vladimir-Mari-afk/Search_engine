#include "SearchServer.h"

void threads(InvertedIndex& ii, std::vector<std::string>& docs)
{
	int maxThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;

	int size = docs.size();
	size_t count = 0;
	
	while (size > 0)
	{
		int threadsToCreate = std::min(size, maxThreads);
		size -= threadsToCreate;
		
		for (int x = 0; x < threadsToCreate; x++, count++)
		{
			ii.e.doc_id = count;
			std::string word;
			threads.emplace_back(&InvertedIndex::getWordCount, std::ref(ii), word);
		}
		for (auto& t : threads)
		{
			t.join();
		}

		threads.clear();
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
	ConverterJSON j;
	InvertedIndex i;
	
	std::vector<std::string> docs;

	try
	{
		docs = j.getTextDocuments();
	}
	catch (const ConfigFieldIsEmptyException& x)
	{
		std::cerr << "config file is empty" << std::endl;
	}
	catch (const ÑonfigFileIsNotOpenException& x)
	{
		std::cerr << "config file is missing" << std::endl;
	}
	
	std::vector<std::string> queriesInput = j.getRequests();
	
	i.updateDocumentBase(docs);

	threads(i, docs);
	
	SearchServer s(i);
	
	int responsesInput = j.getResponsesLimit();
	
	auto answersInput = s.search(queriesInput, responsesInput);
	
	j.putAnswers(answersInput);
}