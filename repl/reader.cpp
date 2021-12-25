#include "reader.h"
#include <cstdlib>
#include <cstring>
#include <readline/history.h>
#include <readline/readline.h>
#include <stack>

namespace fundot {

Reader::Reader() {
    rl_completion_entry_function = completion_entry;
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

char* Reader::completion_entry(const char* text, int state) {
    static std::vector<std::string> candidates;
    static std::size_t pos{0};
    static std::size_t size{0};
    if (state == 0) {
        auto scope{dynamic_cast<Set*>(get_scope())};
        if (scope == nullptr) {
            throw Error{"completion failed. Current scope is not a 'Set'"};
        }
        auto vec{scope->to_vector()};
        for (auto& obj : vec) {
            auto setter{dynamic_cast<Setter*>(obj)};
            if (setter != nullptr) {
                candidates.push_back(setter->first()->to_string());
            } else {
                candidates.push_back(obj->to_string());
            }
        }
        pos = 0;
        size = candidates.size();
    }
    for (std::size_t i{pos}; i < size; ++i) {
        const std::string& candidate{candidates[i]};
        if (std::strncmp(candidate.c_str(), text, std::strlen(text)) == 0) {
            char* match{
                static_cast<char*>(std::malloc(candidate.length() + 1))};
            std::strcpy(match, candidate.c_str());
            pos = i + 1;
            return match;
        }
    }
    return nullptr;
}

}
