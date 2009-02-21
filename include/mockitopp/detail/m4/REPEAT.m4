define(`M4_REPEAT', `ifelse(eval($1 > 0), 1,`M4_REPEAT(decr($1), `$2') $2(decr($1))', `')')dnl
