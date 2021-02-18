( dots_hf.fs )

( high fidelity .s word )
( Thu Feb 18 18:07:08 UTC 2021 )
( VERY BEST VERSION SO FAR 18:07:08 UTC Thu 18 Feb )

( TODO: factor the spaghetti )

HEX
: depth DEPTH ;
: dump DUMP ; : here HERE ; : words WORDS ; : cold COLD ; : .s .S ;
: hex HEX ; : decimal DECIMAL ; : cr CR ; : swap SWAP ; : drop DROP ;
: dup DUP ; : over OVER ; : space SPACE ; : spaces SPACES ;
: emit EMIT ; : tryloop DO blink LOOP ; : delay 1D000 * 0 DO 1 DROP LOOP ;
HEX
: hinum 7FFFFFFF ; : lonum -80000000 ; 
: #SD> DEPTH [CHAR] < EMIT . 8 EMIT [CHAR] > EMIT SPACE ;

: endfmtprt SIGN #> TYPE SPACE ;

: ###>
  <# DUP 0 #S ROT DUP 0 <
  IF
      DUP -FFFF 1 - >
      IF -1 * THEN
  THEN
  BASE @ 10 =
  IF
      DUP 7FFFFFFF 1 + + 0 >
      IF
          DUP -10000 SWAP >
          IF -1 * endfmtprt EXIT THEN
      THEN
  THEN
  -1 *

  DUP -1000 SWAP <
  IF
      1000 + INVERT 1 + -1 * SIGN #> DROP DROP DUP .
  EXIT
  THEN
  INVERT 1 - SIGN #> DROP DROP DUP .  ;

: .treal
  DUP ABS
  OVER = IF ( abs n equals n )
      DUP hinum = IF
          SPACE ." 7FFFFFFF " ( special )
      EXIT
      THEN
      DUP hinum 1 + = IF
          SPACE ." 80000000 " ( special )
      EXIT
      THEN
      DUP .
  EXIT
  THEN
  DUP FFFF0000 > IF
      SPACE DUP .
  EXIT
  THEN
  DUP .HHHH ;
  ( DUP . ; )

: sho 20 + 8 SPACES .treal ;
: CYAB 1 DEPTH 0 2 + = IF -1 EXIT THEN ;
: CYAO 0 DEPTH 0 1 + = IF -1 EXIT THEN ;
: DOTTUSUC
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
: CYB #SD>
  CYAO -1 = IF
      DROP QUIT THEN 
  CYAB -1 = IF
      DROP DUP ###> QUIT THEN
  DOTTUSUC ; ( was DROP ; )
: .s CYB DROP ; ( add back the drop to CYB def )
: .shelp ." dotS is mixed metaphor - careful - use .S for canonical " CR ;
: loadnums decimal -99 dup 1 + dup 1 + HEX D0000000 DUP A0000 + ;
( END )

