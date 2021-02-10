( quickvocab.fs )
HEX
: dump DUMP ; : here HERE ; : words WORDS ; 
: cold COLD ; : .s .S ; : hex HEX ; 
: decimal DECIMAL ; : cr CR ; 
: swap SWAP ; : drop DROP ; : dup DUP ; 
: over OVER ; 
: p 18 dump dup cr . ;
: q 3000 + p ; ( jump way ahead )
( interesting addresses )
: cpyaa 10066E20 ; ( ascii strings circuitpython )
( remnant remaining in the QSPI flashROM )
: cpybb 1006A6D0 ; ( end of ascii string stuff )
( end of list )
