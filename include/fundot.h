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
        Fundot() : _obj(map<Identifier, Object>()) { _init(); }

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
        Object _obj;
        void _init();
        Object _add(Object &obj);
    };
} // namespace fundot

#endif