#include "fundot/fundot.h"

namespace fundot {

Object operator&&(const Object& lhs, const Object& rhs)
{
    bool first = !(lhs.value.type() == typeid(Null)
                   || lhs == Object({Boolean({false})}));
    bool second = !(rhs.value.type() == typeid(Null)
                    || rhs == Object({Boolean({false})}));
    return {Boolean({first && second})};
}

Object operator||(const Object& lhs, const Object& rhs)
{
    bool first = !(lhs.value.type() == typeid(Null)
                   || lhs == Object({Boolean({false})}));
    bool second = !(rhs.value.type() == typeid(Null)
                    || rhs == Object({Boolean({false})}));
    return {Boolean({first || second})};
}

Object operator!(const Object& object)
{
    return {Boolean({object.value.type() == typeid(Null)
                     || object == Object({Boolean({false})})})};
}

}  // namespace fundot
