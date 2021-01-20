#include "fundot/fundot.h"

using namespace fundot;

Object quit_obj = {PrimitiveFunction({[](const List&) -> Object {
    std::exit(EXIT_SUCCESS);
}})};
