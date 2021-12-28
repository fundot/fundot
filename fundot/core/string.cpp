#include "string.h"

namespace fundot {

String::String(const std::string& raw_str) : raw_str{raw_str} {
}

bool String::equals(const Object* obj) const {
    auto other{dynamic_cast<const String*>(obj)};
    return other != nullptr && raw_str == other->raw_str;
}

std::size_t String::hash() const {
    return std::hash<std::string>{}(raw_str);
}

std::string String::to_string() const {
    std::string str{'"'};
    for (const auto& ch : raw_str) {
        switch (ch) {
        case '"':
            str += "\\\"";
            break;
        case '\\':
            str += '\\';
            break;
        case '\b':
            str += "\\b";
            break;
        case '\f':
            str += "\\f";
            break;
        case '\n':
            str += "\\n";
            break;
        case '\r':
            str += "\\r";
            break;
        case '\t':
            str += "\\t";
            break;
        default:
            str += ch;
        }
    }
    str.push_back('"');
    return str;
}

const std::string& String::string_value() const {
    return raw_str;
}

std::size_t String::size() const {
    return raw_str.size();
}

}
