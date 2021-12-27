#include "null.h"

namespace fundot {

bool Null::equals(const Object* obj) const {
    return dynamic_cast<const Null*>(obj) != nullptr;
}

std::string Null::to_string() const {
    return "null";
}

}
