#include "fundot/fundot.h"

namespace fundot {

class Printer::Impl {
public:
    std::ostream& print(const Object& object, std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Boolean& boolean)
{
    return os << std::boolalpha << boolean.value << std::noboolalpha;
}

std::ostream& operator<<(std::ostream& os, const Integer& num)
{
    if (num.value < 0) {
        return os << "(-" << -num.value << ')';
    }
    return os << num.value;
}

std::ostream& operator<<(std::ostream& os, const Float& num)
{
    if (num.value < 0) {
        return os << "(-" << -num.value << ')';
    }
    return os << num.value;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    return os << '"' << string.value << '"';
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol)
{
    return os << symbol.value;
}

std::ostream& operator<<(std::ostream& os, const List& list)
{
    if (list.value.empty()) {
        return os << "()";
    }
    os << '(';
    for (const auto& object : list.value) {
        os << object << ' ';
    }
    return os << "\b)";
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    if (vector.value.empty()) {
        return os << "[]";
    }
    os << '[';
    for (const auto& object : vector.value) {
        os << object << ", ";
    }
    return os << "\b\b]";
}

std::ostream& operator<<(std::ostream& os, const UnorderedSet& set)
{
    if (set.value.empty()) {
        return os << "{}";
    }
    os << '{';
    for (const auto& object : set.value) {
        os << object << ", ";
    }
    return os << "\b\b}";
}

std::ostream& operator<<(std::ostream& os, const Setter& setter)
{
    return os << setter.value.first << " : " << setter.value.second;
}

std::ostream& operator<<(std::ostream& os, const Getter& getter)
{
    return os << getter.value.first << '.' << getter.value.second;
}

std::ostream& operator<<(std::ostream& os, const Assignment& assignment)
{
    return os << assignment.value.first << " = " << assignment.value.second;
}

std::ostream& operator<<(std::ostream& os, const Adder& adder)
{
    return os << adder.value.first << " + " << adder.value.second;
}

std::ostream& operator<<(std::ostream& os, const Subtractor& subtractor)
{
    return os << subtractor.value.first << " - " << subtractor.value.second;
}

std::ostream& operator<<(std::ostream& os, const Multiplier& multiplier)
{
    return os << multiplier.value.first << " * " << multiplier.value.second;
}

std::ostream& operator<<(std::ostream& os, const Divisor& divisor)
{
    return os << divisor.value.first << " / " << divisor.value.second;
}

std::ostream& operator<<(std::ostream& os, const Modular& modular)
{
    return os << modular.value.first << " % " << modular.value.second;
}

std::ostream& operator<<(std::ostream& os, const Less& less)
{
    return os << less.value.first << " < " << less.value.second;
}

std::ostream& operator<<(std::ostream& os, const Greater& greater)
{
    return os << greater.value.first << " > " << greater.value.second;
}

std::ostream& operator<<(std::ostream& os, const LessEqual& less_equal)
{
    return os << less_equal.value.first << " <= " << less_equal.value.second;
}

std::ostream& operator<<(std::ostream& os, const GreaterEqual& greater_equal)
{
    return os << greater_equal.value.first
              << " >= " << greater_equal.value.second;
}

std::ostream& operator<<(std::ostream& os, const EqualTo& equal_to)
{
    return os << equal_to.value.first << " == " << equal_to.value.second;
}

std::ostream& operator<<(std::ostream& os, const Quote& quote)
{
    return os << '\'' << quote.value;
}

std::ostream& operator<<(std::ostream& os, const Negator& negator)
{
    return os << '-' << negator.value;
}

std::ostream& operator<<(std::ostream& os, const And& logical_and)
{
    return os << logical_and.value.first << " && " << logical_and.value.second;
}

std::ostream& operator<<(std::ostream& os, const Or& logical_or)
{
    return os << logical_or.value.first << " || " << logical_or.value.second;
}

std::ostream& operator<<(std::ostream& os, const Not& logical_not)
{
    return os << '!' << logical_not.value;
}

std::ostream& operator<<(std::ostream& os, const BitwiseAnd& bitwise_and)
{
    return os << bitwise_and.value.first << " & " << bitwise_and.value.second;
}

std::ostream& operator<<(std::ostream& os, const BitwiseOr& bitwise_or)
{
    return os << bitwise_or.value.first << " | " << bitwise_or.value.second;
}

std::ostream& operator<<(std::ostream& os, const BitwiseXor& bitwise_xor)
{
    return os << bitwise_xor.value.first << " ^ " << bitwise_xor.value.second;
}

std::ostream& operator<<(std::ostream& os, const BitwiseNot& bitwise_not)
{
    return os << '~' << bitwise_not.value;
}

std::ostream& operator<<(std::ostream& os, const LeftShift& left_shift)
{
    return os << left_shift.value.first << " << " << left_shift.value.second;
}

std::ostream& operator<<(std::ostream& os, const RightShift& right_shift)
{
    return os << right_shift.value.first << " >> " << right_shift.value.second;
}

std::ostream& operator<<(std::ostream& os, const SpecialForm&)
{
    UnorderedSet set;
    Setter setter;
    setter.value.first.value = Symbol({"type"});
    setter.value.second.value = Symbol({"special_form"});
    set.value.insert({setter});
    return os << set;
}

std::ostream& operator<<(std::ostream& os, const PrimitiveFunction&)
{
    UnorderedSet set;
    Setter setter;
    setter.value.first.value = Symbol({"type"});
    setter.value.second.value = Symbol({"primitive_function"});
    set.value.insert({setter});
    return os << set;
}

std::ostream& operator<<(std::ostream& os, const SharedObject&)
{
    UnorderedSet set;
    Setter setter;
    setter.value.first.value = Symbol({"type"});
    setter.value.second.value = Symbol({"shared_object"});
    set.value.insert({setter});
    return os << set;
}

std::ostream& operator<<(std::ostream& os, const Object& object)
{
    const auto& value = object.value;
    if (value.type() == typeid(Boolean)) {
        return os << std::any_cast<const Boolean&>(value);
    }
    if (value.type() == typeid(Integer)) {
        return os << std::any_cast<const Integer&>(value);
    }
    if (value.type() == typeid(Float)) {
        return os << std::any_cast<const Float&>(value);
    }
    if (value.type() == typeid(String)) {
        return os << std::any_cast<const String&>(value);
    }
    if (value.type() == typeid(Symbol)) {
        return os << std::any_cast<const Symbol&>(value);
    }
    if (value.type() == typeid(List)) {
        return os << std::any_cast<const List&>(value);
    }
    if (value.type() == typeid(Vector)) {
        return os << std::any_cast<const Vector&>(value);
    }
    if (value.type() == typeid(UnorderedSet)) {
        return os << std::any_cast<const UnorderedSet&>(value);
    }
    if (value.type() == typeid(Setter)) {
        return os << std::any_cast<const Setter&>(value);
    }
    if (value.type() == typeid(Getter)) {
        return os << std::any_cast<const Getter&>(value);
    }
    if (value.type() == typeid(Assignment)) {
        return os << std::any_cast<const Assignment&>(value);
    }
    if (value.type() == typeid(Adder)) {
        return os << std::any_cast<const Adder&>(value);
    }
    if (value.type() == typeid(Subtractor)) {
        return os << std::any_cast<const Subtractor&>(value);
    }
    if (value.type() == typeid(Multiplier)) {
        return os << std::any_cast<const Multiplier&>(value);
    }
    if (value.type() == typeid(Divisor)) {
        return os << std::any_cast<const Divisor&>(value);
    }
    if (value.type() == typeid(Modular)) {
        return os << std::any_cast<const Modular&>(value);
    }
    if (value.type() == typeid(Less)) {
        return os << std::any_cast<const Less&>(value);
    }
    if (value.type() == typeid(Greater)) {
        return os << std::any_cast<const Greater&>(value);
    }
    if (value.type() == typeid(LessEqual)) {
        return os << std::any_cast<const LessEqual&>(value);
    }
    if (value.type() == typeid(GreaterEqual)) {
        return os << std::any_cast<const GreaterEqual&>(value);
    }
    if (value.type() == typeid(EqualTo)) {
        return os << std::any_cast<const EqualTo&>(value);
    }
    if (value.type() == typeid(Quote)) {
        return os << std::any_cast<const Quote&>(value);
    }
    if (value.type() == typeid(Negator)) {
        return os << std::any_cast<const Negator&>(value);
    }
    if (value.type() == typeid(Null)) {
        return os << "null";
    }
    if (value.type() == typeid(And)) {
        return os << std::any_cast<const And&>(value);
    }
    if (value.type() == typeid(Or)) {
        return os << std::any_cast<const Or&>(value);
    }
    if (value.type() == typeid(Not)) {
        return os << std::any_cast<const Not&>(value);
    }
    if (value.type() == typeid(BitwiseAnd)) {
        return os << std::any_cast<const BitwiseAnd&>(value);
    }
    if (value.type() == typeid(BitwiseOr)) {
        return os << std::any_cast<const BitwiseOr&>(value);
    }
    if (value.type() == typeid(BitwiseXor)) {
        return os << std::any_cast<const BitwiseXor&>(value);
    }
    if (value.type() == typeid(LeftShift)) {
        return os << std::any_cast<const LeftShift&>(value);
    }
    if (value.type() == typeid(RightShift)) {
        return os << std::any_cast<const RightShift&>(value);
    }
    if (value.type() == typeid(BitwiseNot)) {
        return os << std::any_cast<const BitwiseNot&>(value);
    }
    if (value.type() == typeid(SpecialForm)) {
        return os << std::any_cast<const SpecialForm&>(value);
    }
    if (value.type() == typeid(PrimitiveFunction)) {
        return os << std::any_cast<const PrimitiveFunction&>(value);
    }
    if (value.type() == typeid(SharedObject)) {
        return os << std::any_cast<const SharedObject&>(value);
    }
    if (value.type() == typeid(Void)) {
        return os;
    }
    return os << "{type : extern}";
}

std::ostream& Printer::Impl::print(const Object& object, std::ostream& os) const
{
    return os << object;
}

std::ostream& Printer::operator()(const Object& object, std::ostream& os) const
{
    return pimpl_->print(object, os);
}

Printer::Printer() : pimpl_(new Impl) {}

Printer::~Printer() = default;

}  // namespace fundot
