#ifndef RESULT_H
#define RESULT_H

#include "Node.h"
#include <tuple>

using Result = std::tuple<bool, Node, size_t>;

extern const Result INVALID;
#endif
