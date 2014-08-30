#ifndef RESULT_H
#define RESULT_H

#include "Node.h"
#include <tuple>

namespace parser {

using Result = std::tuple<bool, Node, size_t>;

}
#endif
