( all_vocab.fs )
HEX
: dump DUMP ; : here HERE ; : words WORDS ; 
: cold COLD ; : .s .S ; : hex HEX ; 
: decimal DECIMAL ; : cr CR ; : swap SWAP ;
: drop DROP ; : dup DUP ; : over OVER ;
: space SPACE ; : spaces SPACES ; : emit EMIT ;
: p 18 dump dup cr . ; ( maximum dump single screenful )
: q 3000 + p ; ( jump way ahead )
: tryloop ( hi lo -- ) ( ex. 4 0 tryloop )
  DO blink LOOP ;
: delay ( n -- ) ( tenths of a second )
  1D000 *
  0 DO 1 DROP LOOP ;
(                       )
: cpyaa 10066E20 ; ( ascii strings circuitpython )
: cpybb 1006A6D0 ; ( end of ascii string stuff )
HEX
: #SD> DEPTH [CHAR] < EMIT . 8 EMIT [CHAR] > EMIT SPACE ;
: ###> <# DUP ABS 0 #S ROT SIGN #> TYPE SPACE ;
: CYAB 1 DEPTH 0 2 + = IF -1 EXIT THEN ;
: CYAO 0 DEPTH 0 1 + = IF -1 EXIT THEN ;
: DOTTUS
  DEPTH
  BEGIN
      SWAP >R
      DEPTH 2 = IF 
          SWAP DUP ###> SWAP 2 -
          BEGIN
              R> DUP ###> SWAP 1 -
              DUP 1 + 0 = IF
                  EXIT THEN 
          AGAIN
      EXIT THEN
  AGAIN  ;
: CYA #SD>
  CYAO -1 = IF
      DROP QUIT THEN 
  CYAB -1 = IF
      DROP DUP ###> QUIT THEN
  DOTTUS DROP ;
: .s CYA ;
( END )
( : #SD> DEPTH 3C EMIT . 8 EMIT 3E EMIT SPACE ; )
