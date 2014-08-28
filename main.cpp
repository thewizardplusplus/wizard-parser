#include <vector>
#include <functional>
#include <iostream>

struct Result {
    bool valid;
    std::string value;
    std::vector<Result> children;
    size_t position;
};
using Parser = std::function<Result(const std::string&, const size_t&)>;

const auto invalid = Result();
const auto symbol = [] (const char& symbol) {
    return [=] (const std::string& text, const size_t& position) {
        if (text.size() > position && text[position] == symbol) {
            return Result{true, std::string(1, symbol), {}, position + 1};
        } else {
            return invalid;
        }
    };
};

std::ostream& operator<<(std::ostream& stream, const Result& result) {
    stream
        << "{"
        << "\"valid\":" << (result.valid ? "true" : "false") << ";"
        << "\"value\":\"" << result.value << "\";"
        << "\"children\":[";
    for (size_t i = 0; i < result.children.size(); ++i) {
        stream << (i ? "," : "") << result.children[i];
    }
    stream
        << "];"
        << "\"position\":" << std::to_string(result.position) << ";"
        << "}";

    return stream;
}

Parser operator!(const Parser& parser) {
    return [=] (const std::string& text, const size_t& position) {
        const auto result = parser(text, position);
        return result.valid ? result : Result{true, "", {}, position};
    };
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
    return [=] (const std::string& text, const size_t& position) {
        const auto result1 = parser1(text, position);
        return result1.valid && !parser2(text, position).valid
            ? result1
            : invalid;
    };
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
    return [=] (const std::string& text, const size_t& position) {
        const auto result1 = parser1(text, position);
        return result1.valid ? result1 : parser2(text, position);
    };
}

Parser operator,(const Parser& parser1, const Parser& parser2) {
    return [=] (const std::string& text, const size_t& position) {
        const auto result1 = parser1(text, position);
        if (!result1.valid) {
            return invalid;
        }

        const auto result2 = parser2(text, position);
        if (!result2.valid) {
            return invalid;
        }

        return Result{true, "", {result1, result2}, result2.position};
    };
}

int main(void) try {
    std::cout
        << Result{
            true,
            "test",
            {Result{true, "test", {}, 23}, Result{true, "test", {}, 23}},
            23
        }
        << std::endl;
} catch (std::exception& exception) {
    std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
