include(`mockitopp/detail/m4/COMMA_IF.m4')dnl
define(`M4_ENUM_SHIFTED_PARAMS', `ifelse(eval($1 > 1), 1, `M4_ENUM_SHIFTED_PARAMS(decr($1), $2)M4_COMMA_IF(decr($1)-1)`$2'decr($1)', `')')dnl
