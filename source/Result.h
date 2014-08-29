#ifndef RESULT_H
#define RESULT_H

#include <string>
#include <vector>
#include <ostream>

struct Result {
	bool valid;
	std::string value;
	std::vector<Result> children;
	size_t position;
};

extern const Result INVALID;

std::ostream& operator<<(std::ostream& stream, const Result& result);
#endif
