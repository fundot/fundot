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
    else if (type_name == "bool")
    {
        vptr = new bool(*static_cast<bool *>(init_object.vptr));
    }
}

Object::Object(const Token &init_token)
{
    if (init_token.name() == Token::Name::LITERAL)
    {
        if (init_token.value() == "true")
        {
            type_name = "bool";
            vptr = new bool(true);
        }
        else if (init_token.value() == "false")
        {
            type_name = "bool";
            vptr = new bool(false);
        }
        static const regex int_regex(R"([+-]?\d+)");
        static const regex double_regex(R"([+-]?(?:0|[1-9]\d*)(?:.\d*)?(?:[eE][+-]?\d+)?)");
        static const regex string_regex(R"(".*")");
        if (regex_match(init_token.value(), int_regex))
        {
            type_name = "int";
            vptr = new int(stoi(init_token.value()));
        }
        else if (regex_match(init_token.value(), double_regex))
        {
            if (stod(init_token.value()) - stoi(init_token.value()) == 0)
            {
                type_name = "int";
                vptr = new int(stoi(init_token.value()));
            }
            else
            {
                type_name = "float";
                vptr = new double(stod(init_token.value()));
            }
        }
        else if (regex_match(init_token.value(), string_regex))
        {
            type_name = "string";
            vptr = new string(init_token.value().substr(1, init_token.value().size() - 2));
        }
    }
    else if (init_token.name() == Token::Name::IDENTIFIER)
    {
        *this = findObject(init_token.value());
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
        if (init_tokens[3].value() == "true")
        {
            type_name = "bool";
            vptr = new bool(true);
        }
        else if (init_tokens[3].value() == "false")
        {
            type_name = "bool";
            vptr = new bool(false);
        }
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
            if (stod(init_tokens[3].value()) - stoi(init_tokens[3].value()) == 0)
            {
                type_name = "int";
                vptr = new int(stoi(init_tokens[3].value()));
            }
            else
            {
                type_name = "float";
                vptr = new double(stod(init_tokens[3].value()));
            }
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
    else if (type_name == "bool")
    {
        delete static_cast<bool *>(vptr);
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
    else if (type_name == "bool")
    {
        vptr = new bool(*static_cast<bool *>(other.vptr));
    }
    return *this;
}

const string &Object::typeName()
{
    return type_name;
}

string Object::toString()
{
    string to_return;
    if (type_name == "Function")
    {
        // error
    }
    else if (type_name == "int")
    {
        to_return = to_string(get<int>());
    }
    else if (type_name == "float")
    {
        to_return = to_string(get<double>());
        to_return.erase(to_return.find_last_not_of('0') + 1);
    }
    else if (type_name == "string")
    {
        to_return = get<string>();
    }
    else if (type_name == "bool")
    {
        to_return = get<bool>() ? "true" : "false";
    }
    return to_return;
}

Object operator==(const Object &first, const Object &second)
{
    Object to_return;
    to_return.type_name = "bool";
    if (first.type_name == "int" && second.type_name == "int")
    {
        if (first.get<int>() == second.get<int>())
        {
            to_return.vptr = new bool(true);
        }
        else
        {
            to_return.vptr = new bool(false);
        }
    }
    else if (first.type_name == "int" && second.type_name == "float")
    {
        if (first.get<int>() == second.get<int>())
        {
            to_return.vptr = new bool(true);
        }
        else
        {
            to_return.vptr = new bool(false);
        }
    }
    else if (first.type_name == "float" && second.type_name == "int")
    {
        if (first.get<int>() == second.get<int>())
        {
            to_return.vptr = new bool(true);
        }
        else
        {
            to_return.vptr = new bool(false);
        }
    }
    else if (first.type_name == "float" && second.type_name == "float")
    {
        if (first.get<int>() == second.get<int>())
        {
            to_return.vptr = new bool(true);
        }
        else
        {
            to_return.vptr = new bool(false);
        }
    }
    else if (first.type_name == "string" && second.type_name == "string")
    {
        if (first.get<string>() == second.get<string>())
        {
            to_return.vptr = new bool(true);
        }
        else
        {
            to_return.vptr = new bool(false);
        }
    }
    else if (first.type_name == "bool" && second.type_name == "bool")
    {
        if (first.get<bool>() == second.get<bool>())
        {
            to_return.vptr = new bool(true);
        }
        else
        {
            to_return.vptr = new bool(false);
        }
    }
    else
    {
        to_return.vptr = new bool(false);
    }
    return to_return;
}

Object operator+(const Object &first, const Object &second)
{
    Object to_return;
    if (first.type_name == "int" && second.type_name == "int")
    {
        int sum = first.get<int>() + second.get<int>();
        to_return.type_name = "int";
        to_return.vptr = new int(sum);
    }
    else if (first.type_name == "int" && second.type_name == "float")
    {
        double sum = first.get<int>() + second.get<double>();
        to_return.type_name = "float";
        to_return.vptr = new double(sum);
    }
    else if (first.type_name == "float" && second.type_name == "int")
    {
        double sum = first.get<double>() + second.get<int>();
        to_return.type_name = "float";
        to_return.vptr = new double(sum);
    }
    else if (first.type_name == "float" && second.type_name == "float")
    {
        double sum = first.get<double>() + second.get<double>();
        to_return.type_name = "float";
        to_return.vptr = new double(sum);
    }
    return to_return;
}