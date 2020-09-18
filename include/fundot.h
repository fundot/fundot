/**
 * @file fundot.h
 * 
 * @author Jiacheng Huang
 */

#ifndef FUNDOT_H
#define FUNDOT_H

#include "object.h"

namespace fundot
{
    using std::endl;

    /**
     * An interpreter class of Fundot.
     * This class handles input and output as well as the evaluation process of Fundot code.
     */
    class Fundot
    {
    public:
        /**
         * Initialize the object with a map and insert some built-in functions into it.
         */
        Fundot();

        /**
         * Evaluate an Object as code.
         * @param obj Object to be evaluated.
         */
        Object eval(Object &obj);

        /**
         * Start a read-eval-print loop.
         * @param is std::istream to be extracted.
         * @param os std::ostream to be inserted.
         */
        void repl(istream &is, ostream &os);

    private:
        Object _obj; /**< Code stored just as data. */
        map<Identifier, Object> *_local_scope; /**< Points to the local scope that the code is evaluated. */

        /**
         * Evaluate a list.
         * @param obj Object that has type std::list<Object>.
         */
        Object _evalList(Object &obj);

        /**
         * Evaluate an identifier.
         * @param obj Object that has type Identifier.
         */
        Object _evalIdentifier(Object &obj);

        /**
         * Evaluate a pair.
         * @param obj Object that has type std::pair<Identifier, Object>.
         */
        Object _evalPair(Object &obj);

        /**
         * Evaluate a vector.
         * @param obj Object that has type std::vector<Object>.
         */
        Object _evalVector(Object &obj);

        /**
         * Evaluate a function.
         * @param obj Object that has type std::list<Object> and its front object has type function.
         */
        Object _evalFunction(Object &obj);

        /**
         * Initialize the Object and prepare for evaluation process.
         */
        void _init();
        
        /**
         * Add a list of numbers.
         * @param obj Object with numbers to add.
         */
        Object _add(Object &obj);
    };
} // namespace fundot

#endif