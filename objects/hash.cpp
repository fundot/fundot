#include "fundot/fundot.h"

using namespace fundot;

Object hash_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    
    Integer hash_value;
    hash_value.value = Hasher{}(*iter);
    return {hash_value};
}

Object hash_obj = {PrimitiveFunction({hash_})};
