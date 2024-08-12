#include "ConverterJSON.h"
#include <map>
#include <thread>
#include <mutex>

struct Entry {
	size_t doc_id= 0, count = 0;

	bool operator ==(const Entry& other) const {
		return (doc_id == other.doc_id &&
			count == other.count);
	}
};

class InvertedIndex
{
	std::vector<std::string> docs;
	std::map<std::string, std::vector<Entry>>* freqDict;

public:

	InvertedIndex() { freqDict = new std::map<std::string, std::vector<Entry>>(); };

	Entry e;
	void updateDocumentBase(std::vector<std::string> docs);
	std::vector<Entry> getWordCount(const std::string& word);
	std::vector<std::string> getDocs();
	std::map<std::string, std::vector<Entry>> getFreqDict();

	~InvertedIndex() { freqDict->clear(); };
};