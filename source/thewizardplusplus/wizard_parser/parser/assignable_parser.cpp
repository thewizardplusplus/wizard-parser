#include "assignable_parser.hpp"
#include <utility>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

rule_parser::pointer assignable_parser::operator=(rule_parser::pointer parser) {
	this->parser = std::move(parser);
	return shared_from_this();
}

parsing_result assignable_parser::process_result(parsing_result result) const {
	return result.is_parsed ? process_parsed_result(std::move(result)) : result;
}

}
}
}
