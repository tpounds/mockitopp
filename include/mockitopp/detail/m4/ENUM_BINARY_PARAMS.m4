include(`mockitopp/detail/m4/COMMA_IF.m4')dnl
define(`M4_ENUM_BINARY_PARAMS', `ifelse(eval($1 > 0), 1, `M4_ENUM_BINARY_PARAMS(decr($1), $2, $3)M4_COMMA_IF(decr($1))`$2'decr($1) `$3'decr($1)', `')')dnl
