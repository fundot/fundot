#include "fundot_eval.h"

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

Object cond(Evaluator* eval, const List& list)
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

Object lambda(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return {Function({*iter, *++iter})};
}

Object defun(Evaluator* eval, const List& list)
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

Object quit()
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

Object read(const List& list)
{
    Object object = {Null()};
    Scanner scan;
    if (list.value.size() == 1) {
        scan(std::cin, object);
        return object;
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() == typeid(File)) {
        scan(*std::any_cast<const File&>(iter->value).value, object);
    }
    return object;
}

Object print(const List& list)
{
    Object end = {Symbol({"\n"})};
    auto iter = list.value.begin();
    Object to_print;
    if (++iter == list.value.end()) {
        std::cout << end;
        return {Void()};
    }
    to_print = *iter;
    if (++iter == list.value.end()) {
        std::cout << to_print << end;
        return {Void()};
    }
    if (iter->value.type() == typeid(File)) {
        *std::any_cast<const File&>(iter->value).value << to_print << end;
        return {Void()};
    }
    return {Void()};
}

Object open(const List& list)
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

Object close(const List& list)
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

Object count(const List& list)
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

Evaluator::Evaluator()
{
    registerSpecialForm("if",
                        [this](const List& list) { return if_(this, list); });
    registerSpecialForm("cond",
                        [this](const List& list) { return cond(this, list); });
    registerSpecialForm(
        "while", [this](const List& list) { return while_(this, list); });
    registerSpecialForm("lambda", lambda);
    registerSpecialForm("defun",
                        [this](const List& list) { return defun(this, list); });
    registerPrimitiveFunction("global",
                              [this](const List&) { return global(); });
    registerPrimitiveFunction("eval",
                              [this](const List& list) { return eval(list); });
    registerPrimitiveFunction("quit", [](const List&) { return quit(); });
    registerPrimitiveFunction("read", read);
    registerPrimitiveFunction("print", print);
    registerPrimitiveFunction("open", open);
    registerPrimitiveFunction("close", close);
    registerPrimitiveFunction("do", do_);
    registerPrimitiveFunction("count", count);
    registerPrimitiveFunction("append", append_);
    registerPrimitiveFunction("insert_", insert_);
    registerPrimitiveFunction("pop", pop_);
    registerPrimitiveFunction("remove", remove_);
}

Object Evaluator::operator()(const Object& object)
{
    return eval(object);
}

Object* Evaluator::get(Vector& owner, const Integer& integer)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        return &owner.value[integer.value];
    }
    return nullptr;
}

Object* Evaluator::get(Vector& owner, const Object& index)
{
    if (index.value.type() == typeid(Integer)) {
        return get(owner, std::any_cast<const Integer&>(index.value));
    }
    return nullptr;
}

Object* Evaluator::get(UnorderedSet& owner, const Object& index)
{
    auto iter = owner.value.find(index);
    if (iter != owner.value.end()) {
        if (iter->value.type() == typeid(Setter)) {
            return &const_cast<Object&>(
                std::any_cast<const Setter&>(iter->value).value.second);
        }
        return &const_cast<Object&>(*iter);
    }
    return nullptr;
}

Object* Evaluator::get(Function& owner, const Object& index)
{
    if (index == Object({Symbol({"params"})})) {
        return &owner.params;
    }
    if (index == Object({Symbol({"body"})})) {
        return &owner.body;
    }
    return nullptr;
}

Object* Evaluator::get(List& owner, const Integer& integer)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        auto iter = owner.value.begin();
        std::advance(iter, integer.value);
        return &*iter;
    }
    return nullptr;
}

Object* Evaluator::get(List& owner, const Object& index)
{
    if (index.value.type() == typeid(Integer)) {
        return get(owner, std::any_cast<const Integer&>(index.value));
    }
    return nullptr;
}

Object* Evaluator::get(Object& owner, const Getter& getter)
{
    Object* obj_ptr = get(owner, getter.value.first);
    if (obj_ptr != nullptr) {
        return get(*obj_ptr, eval(getter.value.second));
    }
    return nullptr;
}

Object* Evaluator::get(Object& owner, const Object& index)
{
    if (index.value.type() == typeid(Getter)) {
        return get(owner, std::any_cast<const Getter&>(index.value));
    }
    if (owner.value.type() == typeid(UnorderedSet)) {
        return get(std::any_cast<UnorderedSet&>(owner.value), index);
    }
    if (owner.value.type() == typeid(Vector)) {
        return get(std::any_cast<Vector&>(owner.value), index);
    }
    if (owner.value.type() == typeid(Function)) {
        return get(std::any_cast<Function&>(owner.value), index);
    }
    if (owner.value.type() == typeid(List)) {
        return get(std::any_cast<List&>(owner.value), index);
    }
    return nullptr;
}

void Evaluator::set(Vector& owner, const Integer& integer, const Object& value)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        owner.value[integer.value] = value;
    }
}

void Evaluator::set(Vector& owner, const Object& index, const Object& value)
{
    if (index.value.type() == typeid(Integer)) {
        set(owner, std::any_cast<const Integer&>(index.value), value);
    }
}

void Evaluator::set(UnorderedSet& owner, const Object& index,
                    const Object& value)
{
    owner.value.erase({Setter({{index, value}})});
    owner.value.insert({Setter({{index, value}})});
}

void Evaluator::set(Function& owner, const Object& index, const Object& value)
{
    if (index == Object({Symbol({"params"})})) {
        owner.params = value;
    }
    if (index == Object({Symbol({"body"})})) {
        owner.body = value;
    }
}

void Evaluator::set(List& owner, const Integer& index, const Object& value)
{
    if (static_cast<std::size_t>(index.value) < owner.value.size()) {
        auto iter = owner.value.begin();
        std::advance(iter, index.value);
        *iter = value;
    }
}

void Evaluator::set(List& owner, const Object& index, const Object& value)
{
    if (index.value.type() == typeid(Integer)) {
        set(owner, std::any_cast<const Integer&>(index.value), value);
    }
}

void Evaluator::set(Object& owner, const Getter& index, const Object& value)
{
    set(*get(owner, index.value.first), eval(index.value.second), value);
}

void Evaluator::set(Object& owner, const Object& index, const Object& value)
{
    if (index.value.type() == typeid(Getter)) {
        set(owner, std::any_cast<const Getter&>(index.value), value);
    }
    if (owner.value.type() == typeid(UnorderedSet)) {
        set(std::any_cast<UnorderedSet&>(owner.value), index, value);
    }
    if (owner.value.type() == typeid(Vector)) {
        set(std::any_cast<Vector&>(owner.value), index, value);
    }
    if (owner.value.type() == typeid(Function)) {
        set(std::any_cast<Function&>(owner.value), index, value);
    }
    if (owner.value.type() == typeid(List)) {
        set(std::any_cast<List&>(owner.value), index, value);
    }
}

void Evaluator::registerSpecialForm(
    const std::string& name, const std::function<Object(const List&)>& function)
{
    set(scope_, {Symbol({name})}, {SpecialForm({function})});
}

void Evaluator::registerPrimitiveFunction(
    const std::string& name, const std::function<Object(const List&)>& function)
{
    set(scope_, {Symbol({name})}, {PrimitiveFunction({function})});
}

Object Evaluator::global()
{
    return scope_;
}

Object Evaluator::eval(const Adder& adder)
{
    return eval(adder.value.first) + eval(adder.value.second);
}

Object Evaluator::eval(const Subtractor& subtractor)
{
    return eval(subtractor.value.first) - eval(subtractor.value.second);
}

Object Evaluator::eval(const Multiplier& multiplier)
{
    return eval(multiplier.value.first) * eval(multiplier.value.second);
}

Object Evaluator::eval(const Divisor& divisor)
{
    return eval(divisor.value.first) / eval(divisor.value.second);
}

Object Evaluator::eval(const Modular& modular)
{
    return eval(modular.value.first) % eval(modular.value.second);
}

Object Evaluator::eval(const Negator& negator)
{
    return -eval(negator.value);
}

Object Evaluator::eval(const Less& less)
{
    return {Boolean({eval(less.value.first) < eval(less.value.second)})};
}

Object Evaluator::eval(const Greater& greater)
{
    return {Boolean({eval(greater.value.first) > eval(greater.value.second)})};
}

Object Evaluator::eval(const LessEqual& less_equal)
{
    return {Boolean(
        {eval(less_equal.value.first) <= eval(less_equal.value.second)})};
}

Object Evaluator::eval(const GreaterEqual& greater_equal)
{
    return {Boolean(
        {eval(greater_equal.value.first) >= eval(greater_equal.value.second)})};
}

Object Evaluator::eval(const EqualTo& equal_to)
{
    return {
        Boolean({eval(equal_to.value.first) == eval(equal_to.value.second)})};
}

Object Evaluator::eval(const NotEqualTo& not_equal_to)
{
    return {Boolean(
        {eval(not_equal_to.value.first) != eval(not_equal_to.value.second)})};
}

Object Evaluator::eval(const And& logical_and)
{
    return eval(logical_and.value.first) && eval(logical_and.value.second);
}

Object Evaluator::eval(const Or& logical_or)
{
    return eval(logical_or.value.first) || eval(logical_or.value.second);
}

Object Evaluator::eval(const Not& logical_not)
{
    return !eval(logical_not.value);
}

Object Evaluator::eval(const BitwiseAnd& bitwise_and)
{
    return eval(bitwise_and.value.first) & eval(bitwise_and.value.second);
}

Object Evaluator::eval(const BitwiseOr& bitwise_or)
{
    return eval(bitwise_or.value.first) | eval(bitwise_or.value.second);
}

Object Evaluator::eval(const BitwiseXor& bitwise_xor)
{
    return eval(bitwise_xor.value.first) ^ eval(bitwise_xor.value.second);
}

Object Evaluator::eval(const BitwiseNot& bitwise_not)
{
    return ~eval(bitwise_not.value);
}

Object Evaluator::eval(const LeftShift& left_shift)
{
    return eval(left_shift.value.first) << eval(left_shift.value.second);
}

Object Evaluator::eval(const RightShift& right_shift)
{
    return eval(right_shift.value.first) >> eval(right_shift.value.second);
}

Object Evaluator::eval(const Symbol& symbol)
{
    Object* obj_ptr = get(scope_, {symbol});
    if (obj_ptr != nullptr) {
        return *obj_ptr;
    }
    return {symbol};
}

Object Evaluator::eval(const Getter& getter)
{
    Object* obj_ptr = get(scope_, {getter});
    if (obj_ptr != nullptr) {
        return *obj_ptr;
    }
    return {Null()};
}

Object Evaluator::eval(const Setter& setter)
{
    Object after_eval = eval(setter.value.second);
    set(scope_, setter.value.first, after_eval);
    return after_eval;
}

Object Evaluator::eval(const Assignment& assignment)
{
    return eval(
        {Setter({{eval(assignment.value.first), assignment.value.second}})});
}

Object Evaluator::eval(const List& list)
{
    if (list.value.empty()) {
        return {Null()};
    }
    List after_eval = list;
    auto iter = after_eval.value.begin();
    *iter = eval(*iter);
    const Object& front = after_eval.value.front();
    if (front.value.type() == typeid(SpecialForm)) {
        const SpecialForm& special_form =
            std::any_cast<const SpecialForm&>(front.value);
        return special_form.value(list);
    }
    while (++iter != after_eval.value.end()) {
        *iter = eval(*iter);
    }
    if (front.value.type() == typeid(PrimitiveFunction)) {
        const PrimitiveFunction& function =
            std::any_cast<const PrimitiveFunction&>(front.value);
        return function.value(after_eval);
    }
    if (front.value.type() == typeid(Function)) {
        const Function& function =
            std::any_cast<Function&>(after_eval.value.front().value);
        Object scope = scope_;
        auto iter = after_eval.value.begin();
        if (function.params.value.type() != typeid(Vector)) {
            return {function};
        }
        auto vector = std::any_cast<const Vector&>(function.params.value).value;
        for (const auto& arg : vector) {
            if (++iter == after_eval.value.end()) {
                break;
            }
            eval(Setter({{arg, *iter}}));
        }
        Object ret = eval(function.body);
        scope_ = scope;
        return ret;
    }
    if (list.value.size() == 1) {
        return after_eval.value.back();
    }
    return {after_eval};
}

Object Evaluator::eval(const UnorderedSet& set)
{
    Object set_copy = {set};
    Object* obj_ptr = get(set_copy, {Symbol({"type"})});
    if (obj_ptr == nullptr) {
        return {set};
    }
    if (*obj_ptr == Object({Symbol({"function"})})) {
        Function function;
        obj_ptr = get(set_copy, {Symbol({"params"})});
        if (obj_ptr == nullptr) {
            return {set};
        }
        function.params = *obj_ptr;
        obj_ptr = get(set_copy, {Symbol({"body"})});
        if (obj_ptr == nullptr) {
            return {set};
        }
        function.body = *obj_ptr;
        return {function};
    }
    return {set};
}

Object Evaluator::eval(const Quote& quote)
{
    return quote.value;
}

Object Evaluator::eval(const Object& object)
{
    if (object.value.type() == typeid(Adder)) {
        return eval(std::any_cast<const Adder&>(object.value));
    }
    if (object.value.type() == typeid(Subtractor)) {
        return eval(std::any_cast<const Subtractor&>(object.value));
    }
    if (object.value.type() == typeid(Multiplier)) {
        return eval(std::any_cast<const Multiplier&>(object.value));
    }
    if (object.value.type() == typeid(Divisor)) {
        return eval(std::any_cast<const Divisor&>(object.value));
    }
    if (object.value.type() == typeid(Modular)) {
        return eval(std::any_cast<const Modular&>(object.value));
    }
    if (object.value.type() == typeid(Negator)) {
        return eval(std::any_cast<const Negator&>(object.value));
    }
    if (object.value.type() == typeid(Less)) {
        return eval(std::any_cast<const Less&>(object.value));
    }
    if (object.value.type() == typeid(Greater)) {
        return eval(std::any_cast<const Greater&>(object.value));
    }
    if (object.value.type() == typeid(LessEqual)) {
        return eval(std::any_cast<const LessEqual&>(object.value));
    }
    if (object.value.type() == typeid(GreaterEqual)) {
        return eval(std::any_cast<const GreaterEqual&>(object.value));
    }
    if (object.value.type() == typeid(EqualTo)) {
        return eval(std::any_cast<const EqualTo&>(object.value));
    }
    if (object.value.type() == typeid(NotEqualTo)) {
        return eval(std::any_cast<const NotEqualTo&>(object.value));
    }
    if (object.value.type() == typeid(And)) {
        return eval(std::any_cast<const And&>(object.value));
    }
    if (object.value.type() == typeid(Or)) {
        return eval(std::any_cast<const Or&>(object.value));
    }
    if (object.value.type() == typeid(Not)) {
        return eval(std::any_cast<const Not&>(object.value));
    }
    if (object.value.type() == typeid(BitwiseAnd)) {
        return eval(std::any_cast<const BitwiseAnd&>(object.value));
    }
    if (object.value.type() == typeid(BitwiseOr)) {
        return eval(std::any_cast<const BitwiseOr&>(object.value));
    }
    if (object.value.type() == typeid(BitwiseXor)) {
        return eval(std::any_cast<const BitwiseXor&>(object.value));
    }
    if (object.value.type() == typeid(BitwiseNot)) {
        return eval(std::any_cast<const BitwiseNot&>(object.value));
    }
    if (object.value.type() == typeid(LeftShift)) {
        return eval(std::any_cast<const LeftShift&>(object.value));
    }
    if (object.value.type() == typeid(RightShift)) {
        return eval(std::any_cast<const RightShift&>(object.value));
    }
    if (object.value.type() == typeid(Symbol)) {
        return eval(std::any_cast<const Symbol&>(object.value));
    }
    if (object.value.type() == typeid(Getter)) {
        return eval(std::any_cast<const Getter&>(object.value));
    }
    if (object.value.type() == typeid(Setter)) {
        return eval(std::any_cast<const Setter&>(object.value));
    }
    if (object.value.type() == typeid(Assignment)) {
        return eval(std::any_cast<const Assignment&>(object.value));
    }
    if (object.value.type() == typeid(List)) {
        return eval(std::any_cast<const List&>(object.value));
    }
    if (object.value.type() == typeid(UnorderedSet)) {
        return eval(std::any_cast<const UnorderedSet&>(object.value));
    }
    if (object.value.type() == typeid(Quote)) {
        return eval(std::any_cast<const Quote&>(object.value));
    }
    return object;
}

}  // namespace fundot
