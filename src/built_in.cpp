#include "built_in.h"

namespace fundot {

Object if_(Evaluator* eval, const List& list)
{
    auto iter = ++list.value.begin();
    Object result = (*eval)(*iter);
    if (result.value.type() == typeid(Null)
        || result == Object({Boolean({false})})) {
        if (++iter != list.value.end() && ++iter != list.value.end()) {
            return (*eval)(*iter);
        }
        return {Null()};
    }
    if (++iter != list.value.end()) {
        return (*eval)(*iter);
    }
    return {Null()};
}

Object cond_(Evaluator* eval, const List& list)
{
    auto iter = list.value.begin();
    while (++iter != list.value.end()) {
        Object result = (*eval)(*iter);
        ++iter;
        if (result.value.type() != typeid(Null)
            && result != Object({Boolean({false})})) {
            return (*eval)(*iter);
        }
    }
    return {Null()};
}

Object while_(Evaluator* eval, const List& list)
{
    auto iter = ++list.value.begin();
    Object predicate = *iter;
    Object to_eval = *++iter;
    Object result = (*eval)(predicate);
    Object ret({Null()});
    while (result.value.type() != typeid(Null)
           && result != Object({Boolean({false})})) {
        ret = (*eval)(to_eval);
        result = (*eval)(predicate);
    }
    return ret;
}

Object lambda_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return {Function({*iter, *++iter})};
}

Object defun_(Evaluator* eval, const List& list)
{
    if (list.value.size() < 4) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    Setter setter;
    setter.value.first = *iter;
    setter.value.second = {Function({*++iter, *++iter})};
    return (*eval)({setter});
}

Object quit_()
{
    std::exit(EXIT_SUCCESS);
}

Object eval_(Evaluator* eval, const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    return (*eval)(*++list.value.begin());
}

Object read_(const List& list)
{
    Object object = {Null()};
    Reader read;
    if (list.value.size() == 1) {
        read(object, std::cin);
        return object;
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() == typeid(File)) {
        read(object, *std::any_cast<const File&>(iter->value).value);
    }
    return object;
}

Object print_(const List& list)
{
    Object end = {String({"\n"})};
    auto iter = list.value.begin();
    Object to_print;
    Printer print;
    if (++iter == list.value.end()) {
        print(end, std::cout);
        return {Void()};
    }
    to_print = *iter;
    if (++iter == list.value.end()) {
        print(to_print, std::cout);
        print(end, std::cout);
        return {Void()};
    }
    if (iter->value.type() == typeid(File)) {
        print(to_print, *std::any_cast<const File&>(iter->value).value);
        print(end, *std::any_cast<const File&>(iter->value).value);
        return {Void()};
    }
    return {Void()};
}

Object open_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() != typeid(String)) {
        return {Null()};
    }
    const String& file_name = std::any_cast<const String&>(iter->value);
    std::ios::openmode mode = std::ios::in;
    if (++iter != list.value.end()) {
        if (*iter == Object({String({"w"})})) {
            mode = std::ios::out;
        }
        if (*iter == Object({String({"a"})})) {
            mode = std::ios::app;
        }
        if (*iter == Object({String({"b"})})) {
            mode = std::ios::binary;
        }
        if (*iter == Object({String({"+"})})) {
            mode = std::ios::in | std::ios::out;
        }
    }
    File file({std::make_shared<std::fstream>(file_name.value, mode)});
    if (file.value->is_open()) {
        return {file};
    }
    return {Null()};
}

Object close_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() == typeid(File)) {
        const File& file = std::any_cast<const File&>(iter->value);
        file.value->close();
        return {Boolean({!file.value->is_open()})};
    }
    return {Null()};
}

Object do_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    return list.value.back();
}

Object count_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    Integer size = {0};
    if (iter->value.type() == typeid(String)) {
        size.value = std::any_cast<const String&>(iter->value).value.size();
        return {size};
    }
    if (iter->value.type() == typeid(UnorderedSet)) {
        size.value =
            std::any_cast<const UnorderedSet&>(iter->value).value.size();
        return {size};
    }
    if (iter->value.type() == typeid(Vector)) {
        size.value = std::any_cast<const Vector&>(iter->value).value.size();
        return {size};
    }
    if (iter->value.type() == typeid(List)) {
        size.value = std::any_cast<const List&>(iter->value).value.size();
        return {size};
    }
    return list.value.back();
}

Object append(const Vector& owner, const Object& value)
{
    Vector ret = owner;
    ret.value.emplace_back(value);
    return {ret};
}

Object append(const List& owner, const Object& value)
{
    List ret = owner;
    ret.value.emplace_back(value);
    return {ret};
}

Object append(const Object& owner, const Object& value)
{
    if (owner.value.type() == typeid(Vector)) {
        return append(std::any_cast<const Vector&>(owner.value), value);
    }
    if (owner.value.type() == typeid(List)) {
        return append(std::any_cast<const List&>(owner.value), value);
    }
    return {Null()};
}

Object append_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return append(*iter, *++iter);
}

Object insert(const Vector& owner, const Object& index, const Object& value)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    Vector ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i > ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.emplace(iter, value);
    return {ret};
}

Object insert(const List& owner, const Object& index, const Object& value)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    List ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i > ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.emplace(iter, value);
    return {ret};
}

Object insert(const Object& owner, const Object& index, const Object& value)
{
    if (owner.value.type() == typeid(Vector)) {
        return insert(std::any_cast<const Vector&>(owner.value), index, value);
    }
    if (owner.value.type() == typeid(List)) {
        return insert(std::any_cast<const List&>(owner.value), index, value);
    }
    return {Null()};
}

Object insert_(const List& list)
{
    if (list.value.size() < 4) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return insert(*iter, *++iter, *++iter);
}

Object remove(const UnorderedSet& owner, const Object& value)
{
    UnorderedSet ret = owner;
    auto iter = std::find(ret.value.begin(), ret.value.end(), value);
    if (iter == ret.value.end()) {
        return {Null()};
    }
    ret.value.erase(iter);
    return {ret};
}

Object remove(const Vector& owner, const Object& value)
{
    Vector ret = owner;
    auto iter = std::find(ret.value.begin(), ret.value.end(), value);
    if (iter == ret.value.end()) {
        return {Null()};
    }
    ret.value.erase(iter);
    return {ret};
}

Object remove(const List& owner, const Object& value)
{
    List ret = owner;
    auto iter = std::find(ret.value.begin(), ret.value.end(), value);
    if (iter == ret.value.end()) {
        return {Null()};
    }
    ret.value.erase(iter);
    return {ret};
}

Object remove(const Object& owner, const Object& value)
{
    if (owner.value.type() == typeid(UnorderedSet)) {
        return remove(std::any_cast<const UnorderedSet&>(owner.value), value);
    }
    if (owner.value.type() == typeid(Vector)) {
        return remove(std::any_cast<const Vector&>(owner.value), value);
    }
    if (owner.value.type() == typeid(List)) {
        return remove(std::any_cast<const List&>(owner.value), value);
    }
    return {Null()};
}

Object remove_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return remove(*iter, *++iter);
}

Object pop(const Vector& owner, const Object& index)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    Vector ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i >= ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.erase(iter);
    return {ret};
}

Object pop(const List& owner, const Object& index)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    List ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i >= ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.erase(iter);
    return {ret};
}

Object pop(const Object& owner, const Object& index)
{
    if (owner.value.type() == typeid(Vector)) {
        return pop(std::any_cast<const Vector&>(owner.value), index);
    }
    if (owner.value.type() == typeid(List)) {
        return pop(std::any_cast<const List&>(owner.value), index);
    }
    return {Null()};
}

Object pop(const Vector& owner)
{
    if (owner.value.empty()) {
        return {Null()};
    }
    Vector ret = owner;
    ret.value.pop_back();
    return {ret};
}

Object pop(const List& owner)
{
    if (owner.value.empty()) {
        return {Null()};
    }
    List ret = owner;
    ret.value.pop_back();
    return {ret};
}

Object pop(const Object& owner)
{
    if (owner.value.type() == typeid(Vector)) {
        return pop(std::any_cast<const Vector&>(owner.value));
    }
    if (owner.value.type() == typeid(List)) {
        return pop(std::any_cast<const List&>(owner.value));
    }
    return {Null()};
}

Object pop_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    if (list.value.size() == 2) {
        return pop(*iter);
    }
    return pop(*iter, *++iter);
}

}  // namespace fundot
