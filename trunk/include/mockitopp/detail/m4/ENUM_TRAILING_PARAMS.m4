define(`M4_ENUM_TRAILING_PARAMS', `ifelse(eval($1 > 0), 1, `M4_ENUM_TRAILING_PARAMS(decr($1), $2), `$2'decr($1)', `')')dnl
