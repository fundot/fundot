lib_path : (locate lib) / "libfunstd.funso"

append : (import lib_path "append_obj")

close : (import lib_path "close_obj")

count : (import lib_path "count_obj")

do : (import lib_path "do_obj")

expand : (import lib_path "expand_obj")

hash : (import lib_path "hash_obj")

insert : (import lib_path "insert_obj")

open : (import lib_path "open_obj")

pop : (import lib_path "pop_obj")

print : (import lib_path "print_obj")

quit : (import lib_path "quit_obj")

quote : (import lib_path "quote_obj")

read : (import lib_path "read_obj")

remove : (import lib_path "remove_obj")

lambda : {
  type : macro,
  params : [params, body],
  body : ('do
    ('let 'fun ': {})
    ('let 'fun'.'type ': 'function)
    ('let 'fun'.'params ': params)
    ('let 'fun'.'body ': ('quote body))
    'fun)
}

defmacro : {
  type : macro,
  params : [name, params, body],
  body : ('do
    name ': {}
    name'.'type ': 'macro
    name'.'params ': params
    name'.'body ': ('quote body))
}

defun : {
  type : macro,
  params : [name, params, body],
  body : ('do
    name ': ('lambda params body))
}
