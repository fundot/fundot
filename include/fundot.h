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
    using std::cin;
    using std::cout;
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
         * Initialize the object and explicitly set input streams.
         * @param is std::istream to extract data.
         */
        Fundot(istream &is);

        /**
         * Initialize the object and explicitly set I/O streams.
         * @param is std::istream to extract data.
         * @param os std::ostream to insert data.
         */
        Fundot(istream &is, ostream &os);

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
        void repl();

    private:
        Object _obj;                               /**< Code stored just as data. */
        vector<map<Identifier, Object> *> _scopes; /**< std::vector that contains scopes from global to local. */
        map<Identifier, Object> *_local_scope;     /**< Points to the local scope that the code is evaluated. */

        istream &_input_stream;  /**< Input stream to extract data. */
        ostream &_output_stream; /**< Output stream to insert data. */

        /**
         * Find the last occurence of an Identifier as a key in scopes.
         * @param id Identifier to find.
         */
        vector<map<Identifier, Object> *>::reverse_iterator _inWhichScope(const Identifier &id);

        void _scopeTraceForward(map<Identifier, Object> *current_scope);

        void _scopeTraceBackward(map<Identifier, Object> *previous_scope);

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
         * Evaluate an if statement.
         * @param obj Object with a if statement.
         */
        Object _if(Object &obj);

        /**
         * Print an Object.
         * @param obj Object with Object to print.
         */
        Object _print(Object &obj);

        /**
         * Add a list of numbers.
         * @param obj Object with numbers to add.
         */
        Object _add(Object &obj);

        /**
         * Subtract a list of numbers from the front.
         * @param obj Object with numbers to subtract.
         */
        Object _sub(Object &obj);

        /**
         * Multiply a list of numbers.
         * @param obj Object with numbers to multiply.
         */
        Object _mul(Object &obj);

        /**
         * Divide a list of numbers by the front.
         * @param obj Object with numbers to divide.
         */
        Object _div(Object &obj);

        /**
         * Module a list of two numbers.
         * @param obj Object with numbers to module with.
         */
        Object _mod(Object &obj);
    };
} // namespace fundot

#endif