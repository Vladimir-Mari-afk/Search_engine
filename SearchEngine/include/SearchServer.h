#include "InvertedIndex.h"

struct RelativeIndex {
	size_t doc_id = 0; 
	float rank = 0;
	bool operator ==(const RelativeIndex& other) const {
		return (doc_id == other.doc_id && rank == other.rank);
	}
};

class SearchServer {
public:
	SearchServer(InvertedIndex& idx) : _index(idx) {  };
	std::vector<std::vector<std::pair<size_t, float>>> search(std::vector<std::string>& queriesInput, int maxResponses);
	std::vector<std::vector<std::pair<size_t, float>>> sort(std::vector<std::vector<std::pair<size_t, float>>>, int maxResponses);

private:
	InvertedIndex _index;
	RelativeIndex ri;
};