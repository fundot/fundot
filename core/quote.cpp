#include "quote.h"

namespace fundot {

Quote::Quote(Object* quoted) : quoted(quoted) {
}

Object* Quote::eval() {
    return quoted;
}

}
