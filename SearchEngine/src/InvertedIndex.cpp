#include "InvertedIndex.h"


void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs)
{
	docs = inputDocs;
}

std::vector<std::string> InvertedIndex::getDocs()
{
	return docs;
}
std::mutex mtx;

std::vector<Entry> InvertedIndex::getWordCount(const std::string& word)
{
	std::vector<Entry> wordCount = {};

	if (word.size() == 0)
	{
		mtx.lock();

		std::stringstream stream1(docs[e.doc_id]);

		size_t doc_id = e.doc_id;

		mtx.unlock();

		while (!stream1.eof())
		{
			size_t count = 0;
			std::string word;
			stream1 >> word;

			std::stringstream stream2(docs[e.doc_id]);

			while (!stream2.eof())
			{
				std::string temp;
				stream2 >> temp;

				if (temp == word)
				{
					count++;
				}
			}

			mtx.lock();

			e.count = count;
			e.doc_id = doc_id;

			if ((*freqDict)[word].empty())
			{
				(*freqDict)[word].push_back({ e.doc_id, e.count });
			}
			else
			{
				bool find = false;

				for (auto& i : (*freqDict)[word])
				{
					if (i.doc_id == e.doc_id)
					{
						find = true;
					}
				}

				if (!find)
				{
					(*freqDict)[word].push_back({ e.doc_id, e.count });
				}
			}
			mtx.unlock();
		}
	}
	else
	{
		for (int i = 0; i < docs.size(); i++)
		{
			std::stringstream stream(docs[i]);

			while (!stream.eof())
			{
				std::string temp;
				stream >> temp;

				if (temp == word)
				{
					e.count++;
				}
			}

			e.doc_id = i;

			if (e.count > 0)
			{
				wordCount.push_back({ e.doc_id, e.count });
			}

			e.count = 0;
		}
	}

	return wordCount;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::getFreqDict()
{
	return *freqDict;
}