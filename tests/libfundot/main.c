#include <stdio.h>
#include <string.h>

#include "fundot/fundot.h"

int main(int argc, char* argv[])
{
    FunObject* to_eval = funCreateObject();
    FunObject* after_eval = funCreateObject();
    FunEvaluator* eval = funCreateEvaluator();
    char output[1024] = "";
    for (int i = 1; i < argc; ++i) {
        memset(output, '.', 1023);
        funRead(to_eval, argv[i]);
        funEval(eval, to_eval, after_eval);
        funPrint(after_eval, output);
        printf("%s\n", output);
    }
    funDestroyEvaluator(eval);
    funDestroyObject(after_eval);
    funDestroyObject(to_eval);
    return 0;
}
