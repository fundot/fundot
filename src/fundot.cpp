#include "fundot/fundot.h"

#include <sstream>

#include "object.h"

struct FunObject {
    fundot::Object value;
};

struct FunEvaluator {
public:
    void operator()(const FunObject* to_eval, FunObject* after_eval);

    FunEvaluator();

private:
    std::unique_ptr<fundot::Evaluator> eval_;
};

void FunEvaluator::operator()(const FunObject* to_eval, FunObject* after_eval)
{
    after_eval->value = eval_->operator()(to_eval->value);
}

FunEvaluator::FunEvaluator() : eval_(new fundot::Evaluator) {}

FunObject* funCreateObject()
{
    return new FunObject;
}

void funDestroyObject(FunObject* object)
{
    delete object;
}

FunEvaluator* funCreateEvaluator()
{
    return new FunEvaluator;
}

void funDestroyEvaluator(FunEvaluator* eval)
{
    delete eval;
}

int funRead(FunObject* object, const char* input)
{
    fundot::Reader read;
    std::stringstream is(input);
    if (read(object->value, is)) {
        return 0;
    }
    return EOF;
}

void funEval(FunEvaluator* eval, const FunObject* to_eval,
             FunObject* after_eval)
{
    (*eval)(to_eval, after_eval);
}

int funPrint(const FunObject* object, char* output)
{
    fundot::Printer print;
    std::stringstream os;
    print(object->value, os);
    std::size_t i = 0;
    while (os >> output[i]) {
        if (output[i] == '\0') {
            return -1;
        }
        ++i;
    }
    output[i] = '\0';
    return 0;
}
