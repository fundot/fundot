#ifndef FUNDOT_CORE_STRING_H
#define FUNDOT_CORE_STRING_H

#include "object.h"

namespace fundot {

class String : public Object {
public:
    String(const std::string& raw_str);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    const std::string& string_value() const;

    std::size_t size() const;

private:
    std::string raw_str;
};

}

#endif