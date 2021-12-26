#include "quote.h"

namespace fundot {

Quote::Quote(Object* quoted) : quoted(quoted) {
}

void Quote::trace() {
    Object::trace();
    quoted->trace();
}

std::string Quote::to_string() const {
    return "'" + quoted->to_string();
}

Object* Quote::eval() {
    return quoted;
}

}
