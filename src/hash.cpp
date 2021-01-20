#include "fundot/fundot.h"

namespace fundot {

std::size_t hash(const Symbol& symbol)
{
    return std::hash<std::string>{}(symbol.value);
}

std::size_t hash(const String& string)
{
    return std::hash<std::string>{}(string.value);
}

std::size_t Hasher::operator()(const Object& object) const
{
    if (object.value.type() == typeid(String)) {
        return hash(std::any_cast<const String&>(object.value));
    }
    if (object.value.type() == typeid(String)) {
        return hash(std::any_cast<const Symbol&>(object.value));
    }
    return 0;
}

}  // namespace fundot
