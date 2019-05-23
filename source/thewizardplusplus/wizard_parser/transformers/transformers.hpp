#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_TRANSFORMERS_TRANSFORMERS_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_TRANSFORMERS_TRANSFORMERS_HEADER

#include "../parser/ast_node.hpp"

namespace thewizardplusplus::wizard_parser::transformers {

parser::ast_node remove_nothings(const parser::ast_node& ast);

}
#endif
