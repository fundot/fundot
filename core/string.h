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

    bool equals(const std::string& other) const;

private:
    std::string raw_str;
};

}

#endif
