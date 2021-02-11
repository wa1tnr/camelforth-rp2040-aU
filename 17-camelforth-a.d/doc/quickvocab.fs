( quickvocab.fs )
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
( interesting addresses )
: cpyaa 10066E20 ; ( ascii strings circuitpython )
( remnant remaining in the QSPI flashROM )
: cpybb 1006A6D0 ; ( end of ascii string stuff )
( end of list )
