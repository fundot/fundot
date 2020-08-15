#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <regex>
#include <unordered_set>
#include <variant>
#include "function.h"
#include "global.h"
#include "token.h"

using namespace std;

class Object
{
public:
    Object() = default;
    Object(const Object &init_object);
    Object(const vector<Token> &init_tokens);
    ~Object();

    Object &operator=(const Object &other);

    const string &typeName();
    string toString();

    template <typename T>
    inline const T &get() { return *static_cast<T *>(vptr); }

private:
    string type_name;
    void *vptr;
};

#endif