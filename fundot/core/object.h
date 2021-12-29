#ifndef FUNDOT_CORE_OBJECT_H
#define FUNDOT_CORE_OBJECT_H

#include <list>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace fundot {

class Object {
public:
    using Error = std::runtime_error;

    struct Equal {
        bool operator()(const Object* lhs, const Object* rhs) const;
    };

    struct Hash {
        std::size_t operator()(const Object* obj) const;
    };

    Object();

    virtual ~Object();

    virtual void trace();

    virtual bool equals(const Object* obj) const;

    virtual std::size_t hash() const;

    virtual std::string to_string() const;

    virtual Object* get(Object* obj) const;

    virtual Object* set(Object* index, Object* value);

    virtual Object* call(Object* obj);

    virtual Object* eval();

    virtual Object* quote(std::size_t count);

    void mark();

    static void add_root(Object* obj);

    static void collect();

    static Object* get_global_context();

    static Object* get_local_context();

    static void set_global_context(Object* context);

    static void set_local_context(Object* context);

private:
    using Color = std::list<Object*>;

    static Color roots;

    static Color white;

    static Color gray;

    static Color black;

    static Object* global_context;

    static Object* local_context;

    Color* color;

    Color::iterator iter;
};

}

#endif
