#include "object.h"

Object::Object(const Object &init_object)
{
    type_name = init_object.type_name;
    if (type_name == "Function")
    {
        vptr = new Function(*static_cast<Function *>(init_object.vptr));
    }
    else if (type_name == "int")
    {
        vptr = new int(*static_cast<int *>(init_object.vptr));
    }
    else if (type_name == "float")
    {
        vptr = new double(*static_cast<double *>(init_object.vptr));
    }
    else if (type_name == "string")
    {
        vptr = new string(*static_cast<string *>(init_object.vptr));
    }
}

Object::Object(const vector<Token> &init_tokens)
{
    if (init_tokens[2].value() != ":")
    {
        type_name = "Function";
        vptr = new Function(init_tokens);
    }
    else
    {
        static const regex int_regex(R"([+-]?\d+)");
        static const regex double_regex(R"([+-]?(?:0|[1-9]\d*)(?:.\d*)?(?:[eE][+-]?\d+)?)");
        static const regex string_regex(R"(".*")");
        if (regex_match(init_tokens[3].value(), int_regex))
        {
            type_name = "int";
            vptr = new int(stoi(init_tokens[3].value()));
        }
        else if (regex_match(init_tokens[3].value(), double_regex))
        {
            type_name = "float";
            vptr = new double(stod(init_tokens[3].value()));
        }
        else if (regex_match(init_tokens[3].value(), string_regex))
        {
            type_name = "string";
            vptr = new string(init_tokens[3].value().substr(1, init_tokens[3].value().size() - 2));
        }
    }
}

Object::~Object()
{
    if (type_name == "Function")
    {
        delete static_cast<Function *>(vptr);
    }
    else if (type_name == "int")
    {
        delete static_cast<int *>(vptr);
    }
    else if (type_name == "float")
    {
        delete static_cast<double *>(vptr);
    }
    else if (type_name == "string")
    {
        delete static_cast<string *>(vptr);
    }
}

Object &Object::operator=(const Object &other)
{
    type_name = other.type_name;
    if (type_name == "Function")
    {
        vptr = new Function(*static_cast<Function *>(other.vptr));
    }
    else if (type_name == "int")
    {
        vptr = new int(*static_cast<int *>(other.vptr));
    }
    else if (type_name == "float")
    {
        vptr = new double(*static_cast<double *>(other.vptr));
    }
    else if (type_name == "string")
    {
        vptr = new string(*static_cast<string *>(other.vptr));
    }
    return *this;
}

const string &Object::typeName()
{
    return type_name;
}

template <typename T>
const T &get(const Object &object)
{
    return *static_cast<T *>(object.vptr);
}