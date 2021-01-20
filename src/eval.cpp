#include <boost/dll.hpp>

#include "fundot/fundot.h"

namespace fundot {

class Evaluator::Impl {
public:
    Object* get(Vector& owner, const Integer& integer);

    Object* get(Vector& owner, const Object& index);

    Object* get(UnorderedSet& owner, const Object& index);

    Object* get(Function& owner, const Object& index);

    Object* get(List& owner, const Integer& integer);

    Object* get(List& owner, const Object& index);

    Object* get(Object& owner, const Getter& getter);

    Object* get(Object& owner, const Object& index);

    void set(Vector& owner, const Integer& integer, const Object& value);

    void set(Vector& owner, const Object& index, const Object& value);

    void set(UnorderedSet& owner, const Object& index, const Object& value);

    void set(Function& owner, const Object& index, const Object& value);

    void set(List& owner, const Integer& index, const Object& value);

    void set(List& owner, const Object& index, const Object& value);

    void set(Object& owner, const Getter& index, const Object& value);

    void set(Object& owner, const Object& index, const Object& value);

    Object cond_(const List& list);

    Object defun_(const List& list);

    Object eval_(const List& list);

    Object global_();

    Object if_(const List& list);

    Object import_(const List& list);

    Object locate_(const List& list);

    Object while_(const List& list);

    Object eval(const Adder& adder);

    Object eval(const Subtractor& subtractor);

    Object eval(const Multiplier& multiplier);

    Object eval(const Divisor& divisor);

    Object eval(const Modular& modular);

    Object eval(const Negator& negator);

    Object eval(const Less& less);

    Object eval(const Greater& greater);

    Object eval(const LessEqual& less_equal);

    Object eval(const GreaterEqual& greater_equal);

    Object eval(const EqualTo& equal_to);

    Object eval(const NotEqualTo& not_equal_to);

    Object eval(const And& logical_and);

    Object eval(const Or& logical_or);

    Object eval(const Not& logical_not);

    Object eval(const BitwiseAnd& bitwise_and);

    Object eval(const BitwiseOr& bitwise_or);

    Object eval(const BitwiseXor& bitwise_xor);

    Object eval(const BitwiseNot& bitwise_not);

    Object eval(const LeftShift& left_shift);

    Object eval(const RightShift& right_shift);

    Object eval(const Symbol& symbol);

    Object eval(const Getter& getter);

    Object eval(const Setter& setter);

    Object eval(const Assignment& assignment);

    Object eval(const List& list);

    Object eval(const UnorderedSet& set);

    Object eval(const Quote& quote);

    Object eval(const SharedObject& shared_object);

    Object eval(const Object& object);

private:
    Object scope_ = {UnorderedSet()};
};

Object* Evaluator::Impl::get(Vector& owner, const Integer& integer)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        return &owner.value[integer.value];
    }
    return nullptr;
}

Object* Evaluator::Impl::get(Vector& owner, const Object& index)
{
    if (index.value.type() == typeid(Integer)) {
        return get(owner, std::any_cast<const Integer&>(index.value));
    }
    return nullptr;
}

Object* Evaluator::Impl::get(UnorderedSet& owner, const Object& index)
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

Object* Evaluator::Impl::get(Function& owner, const Object& index)
{
    if (index == Object({Symbol({"params"})})) {
        return &owner.params;
    }
    if (index == Object({Symbol({"body"})})) {
        return &owner.body;
    }
    return nullptr;
}

Object* Evaluator::Impl::get(List& owner, const Integer& integer)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        auto iter = owner.value.begin();
        std::advance(iter, integer.value);
        return &*iter;
    }
    return nullptr;
}

Object* Evaluator::Impl::get(List& owner, const Object& index)
{
    if (index.value.type() == typeid(Integer)) {
        return get(owner, std::any_cast<const Integer&>(index.value));
    }
    return nullptr;
}

Object* Evaluator::Impl::get(Object& owner, const Getter& getter)
{
    Object* obj_ptr = get(owner, getter.value.first);
    if (obj_ptr != nullptr) {
        return get(*obj_ptr, eval(getter.value.second));
    }
    return nullptr;
}

Object* Evaluator::Impl::get(Object& owner, const Object& index)
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

void Evaluator::Impl::set(Vector& owner, const Integer& integer,
                          const Object& value)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        owner.value[integer.value] = value;
    }
}

void Evaluator::Impl::set(Vector& owner, const Object& index,
                          const Object& value)
{
    if (index.value.type() == typeid(Integer)) {
        set(owner, std::any_cast<const Integer&>(index.value), value);
    }
}

void Evaluator::Impl::set(UnorderedSet& owner, const Object& index,
                          const Object& value)
{
    owner.value.erase({Setter({{index, value}})});
    owner.value.insert({Setter({{index, value}})});
}

void Evaluator::Impl::set(Function& owner, const Object& index,
                          const Object& value)
{
    if (index == Object({Symbol({"params"})})) {
        owner.params = value;
    }
    if (index == Object({Symbol({"body"})})) {
        owner.body = value;
    }
}

void Evaluator::Impl::set(List& owner, const Integer& index,
                          const Object& value)
{
    if (static_cast<std::size_t>(index.value) < owner.value.size()) {
        auto iter = owner.value.begin();
        std::advance(iter, index.value);
        *iter = value;
    }
}

void Evaluator::Impl::set(List& owner, const Object& index, const Object& value)
{
    if (index.value.type() == typeid(Integer)) {
        set(owner, std::any_cast<const Integer&>(index.value), value);
    }
}

void Evaluator::Impl::set(Object& owner, const Getter& index,
                          const Object& value)
{
    set(*get(owner, index.value.first), eval(index.value.second), value);
}

void Evaluator::Impl::set(Object& owner, const Object& index,
                          const Object& value)
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

Object Evaluator::Impl::cond_(const List& list)
{
    auto iter = list.value.begin();
    while (++iter != list.value.end()) {
        Object result = eval(*iter);
        ++iter;
        if (result.value.type() != typeid(Null)
            && result != Object({Boolean({false})})) {
            return eval(*iter);
        }
    }
    return {Null()};
}

Object Evaluator::Impl::defun_(const List& list)
{
    if (list.value.size() < 4) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    Setter setter;
    setter.value.first = *iter;
    setter.value.second = {Function({*++iter, *++iter})};
    return eval({setter});
}

Object Evaluator::Impl::eval_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    return eval(*++list.value.begin());
}

Object Evaluator::Impl::global_()
{
    return scope_;
}

Object Evaluator::Impl::if_(const List& list)
{
    auto iter = ++list.value.begin();
    Object result = eval(*iter);
    if (result.value.type() == typeid(Null)
        || result == Object({Boolean({false})})) {
        if (++iter != list.value.end() && ++iter != list.value.end()) {
            return eval(*iter);
        }
        return {Null()};
    }
    if (++iter != list.value.end()) {
        return eval(*iter);
    }
    return {Null()};
}

Object Evaluator::Impl::import_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    PrimitiveFunction function;
    if (iter->value.type() != typeid(String)) {
        return {Null()};
    }
    std::string lib_path = std::any_cast<const String&>(iter->value).value;
    if ((++iter)->value.type() != typeid(String)) {
        return {Null()};
    }
    std::string obj_name = std::any_cast<const String&>(iter->value).value;
    boost::shared_ptr<Object> obj_ptr =
        boost::dll::import<Object>(lib_path, obj_name);
    SharedObject shared_object = {std::shared_ptr<Object>(
        obj_ptr.get(), [obj_ptr](Object*) mutable { obj_ptr.reset(); })};
    Object first = {Symbol({obj_name})};
    Object second = {shared_object};
    set(scope_, first, second);
    return eval(shared_object);
}

Object Evaluator::Impl::locate_(const List& list)
{
    boost::dll::fs::path bin_path = boost::dll::program_location();
    auto iter = ++list.value.begin();
    if (iter == list.value.end()) {
        return {String({bin_path.string()})};
    }
    if (*iter == Object({Symbol({"lib"})})) {
        return {
            String({bin_path.parent_path().parent_path().string() + "/lib"})};
    }
    return {Null()};
}

Object Evaluator::Impl::while_(const List& list)
{
    auto iter = ++list.value.begin();
    Object predicate = *iter;
    Object to_eval = *++iter;
    Object result = eval(predicate);
    Object ret({Null()});
    while (result.value.type() != typeid(Null)
           && result != Object({Boolean({false})})) {
        ret = eval(to_eval);
        result = eval(predicate);
    }
    return ret;
}

Object Evaluator::Impl::eval(const Adder& adder)
{
    return eval(adder.value.first) + eval(adder.value.second);
}

Object Evaluator::Impl::eval(const Subtractor& subtractor)
{
    return eval(subtractor.value.first) - eval(subtractor.value.second);
}

Object Evaluator::Impl::eval(const Multiplier& multiplier)
{
    return eval(multiplier.value.first) * eval(multiplier.value.second);
}

Object Evaluator::Impl::eval(const Divisor& divisor)
{
    return eval(divisor.value.first) / eval(divisor.value.second);
}

Object Evaluator::Impl::eval(const Modular& modular)
{
    return eval(modular.value.first) % eval(modular.value.second);
}

Object Evaluator::Impl::eval(const Negator& negator)
{
    return -eval(negator.value);
}

Object Evaluator::Impl::eval(const Less& less)
{
    return {Boolean({eval(less.value.first) < eval(less.value.second)})};
}

Object Evaluator::Impl::eval(const Greater& greater)
{
    return {Boolean({eval(greater.value.first) > eval(greater.value.second)})};
}

Object Evaluator::Impl::eval(const LessEqual& less_equal)
{
    return {Boolean(
        {eval(less_equal.value.first) <= eval(less_equal.value.second)})};
}

Object Evaluator::Impl::eval(const GreaterEqual& greater_equal)
{
    return {Boolean(
        {eval(greater_equal.value.first) >= eval(greater_equal.value.second)})};
}

Object Evaluator::Impl::eval(const EqualTo& equal_to)
{
    return {
        Boolean({eval(equal_to.value.first) == eval(equal_to.value.second)})};
}

Object Evaluator::Impl::eval(const NotEqualTo& not_equal_to)
{
    return {Boolean(
        {eval(not_equal_to.value.first) != eval(not_equal_to.value.second)})};
}

Object Evaluator::Impl::eval(const And& logical_and)
{
    return eval(logical_and.value.first) && eval(logical_and.value.second);
}

Object Evaluator::Impl::eval(const Or& logical_or)
{
    return eval(logical_or.value.first) || eval(logical_or.value.second);
}

Object Evaluator::Impl::eval(const Not& logical_not)
{
    return !eval(logical_not.value);
}

Object Evaluator::Impl::eval(const BitwiseAnd& bitwise_and)
{
    return eval(bitwise_and.value.first) & eval(bitwise_and.value.second);
}

Object Evaluator::Impl::eval(const BitwiseOr& bitwise_or)
{
    return eval(bitwise_or.value.first) | eval(bitwise_or.value.second);
}

Object Evaluator::Impl::eval(const BitwiseXor& bitwise_xor)
{
    return eval(bitwise_xor.value.first) ^ eval(bitwise_xor.value.second);
}

Object Evaluator::Impl::eval(const BitwiseNot& bitwise_not)
{
    return ~eval(bitwise_not.value);
}

Object Evaluator::Impl::eval(const LeftShift& left_shift)
{
    return eval(left_shift.value.first) << eval(left_shift.value.second);
}

Object Evaluator::Impl::eval(const RightShift& right_shift)
{
    return eval(right_shift.value.first) >> eval(right_shift.value.second);
}

Object Evaluator::Impl::eval(const Symbol& symbol)
{
    Object* obj_ptr = get(scope_, {symbol});
    if (obj_ptr != nullptr) {
        return *obj_ptr;
    }
    return {symbol};
}

Object Evaluator::Impl::eval(const Getter& getter)
{
    Object* obj_ptr = get(scope_, {getter});
    if (obj_ptr != nullptr) {
        return *obj_ptr;
    }
    return {Null()};
}

Object Evaluator::Impl::eval(const Setter& setter)
{
    Object after_eval = eval(setter.value.second);
    set(scope_, setter.value.first, after_eval);
    return after_eval;
}

Object Evaluator::Impl::eval(const Assignment& assignment)
{
    return eval(
        {Setter({{eval(assignment.value.first), assignment.value.second}})});
}

Object Evaluator::Impl::eval(const List& list)
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

Object Evaluator::Impl::eval(const UnorderedSet& set)
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

Object Evaluator::Impl::eval(const Quote& quote)
{
    return quote.value;
}

Object Evaluator::Impl::eval(const SharedObject& shared_object)
{
    return eval(*shared_object.value);
}

Object Evaluator::Impl::eval(const Object& object)
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
    if (object.value.type() == typeid(SharedObject)) {
        return eval(std::any_cast<const SharedObject&>(object.value));
    }
    return object;
}

Object Evaluator::operator()(const Object& object)
{
    return pimpl_->eval(object);
}

Evaluator::Evaluator() : pimpl_(new Evaluator::Impl)
{
    Symbol name;
    PrimitiveFunction function;
    name.value = "cond";
    function.value = [this](const List& list) {
        return pimpl_->cond_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "defun";
    function.value = [this](const List& list) {
        return pimpl_->defun_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "eval";
    function.value = [this](const List& list) {
        return pimpl_->eval_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "global";
    function.value = [this](const List&) {
        return pimpl_->global_();
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "if";
    function.value = [this](const List& list) {
        return pimpl_->if_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "import";
    function.value = [this](const List& list) {
        return pimpl_->import_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "locate";
    function.value = [this](const List& list) {
        return pimpl_->locate_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
    name.value = "while";
    function.value = [this](const List& list) {
        return pimpl_->while_(list);
    };
    pimpl_->eval(Setter({{{name}, {function}}}));
}

Evaluator::~Evaluator() = default;

}  // namespace fundot
