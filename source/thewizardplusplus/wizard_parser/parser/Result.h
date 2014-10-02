#ifndef WIZARD_PARSER_RESULT_HEADER
#define WIZARD_PARSER_RESULT_HEADER

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
