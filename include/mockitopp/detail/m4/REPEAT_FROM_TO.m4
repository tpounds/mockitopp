define(`M4_REPEAT_FROM_TO', `ifelse(eval($2 > $1), 1,`M4_REPEAT_FROM_TO($1, decr($2), `$3') $3(decr($2))', `')')dnl
