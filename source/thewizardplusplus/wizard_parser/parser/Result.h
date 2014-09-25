#ifndef RESULT_H
#define RESULT_H

#include "../node/Node.h"
#include <tuple>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

using Result = std::tuple<bool, node::Node, size_t>;

}
}
}
#endif
