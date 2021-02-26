HEX
: compare ( offset -- offset )  ( or ) ( n -- n lo+incr hi+incr )
  ( offset returned unchanged )
  -20 MAX FFFF MIN
  1000030C 200000C0
  ROT DUP >R + SWAP R> DUP >R +
  1 DUMP >R 1 DUMP
  R> R> SWAP ROT
  ( DROP DROP )
;

: next ( n -- n )
  10 + compare ;

: demo_near_top ( -- )
  ." type this: C5F4 10 - next DROP DROP " ;

( end )
