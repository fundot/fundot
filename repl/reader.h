#ifndef FUNDOT_REPL_READER_H
#define FUNDOT_REPL_READER_H

#include "core/set.h"
#include <unordered_map>

namespace fundot {

class Reader : public Object {
public:
    Reader();

    std::string read_line(const std::string& prompt) const;

    std::string read() const;

private:
    bool is_complete(const std::string& str) const;

    static char* completion_entry(const char* text, int state);

    std::string primary_prompt{"> "};

    std::string secondary_prompt{"  "};

    std::unordered_map<char, char> pairs{
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    };

    std::unordered_map<char, char> reverse_pairs{
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
};

}

#endif
