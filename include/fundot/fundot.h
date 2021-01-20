#ifndef FUNDOT_FUNDOT_H
#define FUNDOT_FUNDOT_H

#ifdef __cplusplus
extern "C" {
#endif

struct FunObject;

struct FunEvaluator;

#ifndef __cplusplus

typedef struct FunObject FunObject;

typedef struct FunEvaluator FunEvaluator;

#endif

FunObject* funCreateObject();

void funDestroyObject(FunObject* object);

FunEvaluator* funCreateEvaluator();

void funDestroyEvaluator(FunEvaluator* eval);

int funRead(FunObject* object, const char* input);

void funEval(FunEvaluator* eval, const FunObject* to_eval,
             FunObject* after_eval);

int funPrint(const FunObject* object, char* output);

#ifdef __cplusplus
}
#endif

#endif
