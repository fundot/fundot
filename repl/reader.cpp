#include "reader.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stack>

namespace fundot {

Reader::Reader() {
    rl_completion_entry_function = nullptr;
    rl_bind_key('\t', rl_complete);
}

std::string Reader::read() const {
    std::string input{read_line(primary_prompt)};
    while (!is_complete(input)) {
        input += read_line(secondary_prompt);
    }
    return input;
}

std::string Reader::read_line(const std::string& prompt) const {
    char* input{readline(prompt.c_str())};
    if (input == nullptr) {
        std::exit(EXIT_SUCCESS);
    }
    add_history(input);
    std::string line{input};
    free(input);
    return line;
}

bool Reader::is_complete(const std::string& str) const {
    std::stack<char> halves;
    auto length{str.length()};
    for (std::size_t i{0}; i < length; ++i) {
        if (pairs.count(str[i]) > 0) {
            halves.push(str[i]);
            continue;
        }
        if (reverse_pairs.count(str[i]) == 0) {
            continue;
        }
        if (pairs.at(halves.top()) != str[i]) {
            std::string message{'\''};
            message += str[i];
            message += "' does not match '";
            message += halves.top();
            message += '\'';
            throw Error{message};
        }
        halves.pop();
    }
    return halves.empty();
}

}
