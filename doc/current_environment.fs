( current_environment.fs )

( Sat Feb 27 12:28:18 UTC 2021 )

HEX
: depth DEPTH ;
: dump DUMP ; : here HERE ; : words WORDS ; : cold COLD ; : .s .S ;
: hex HEX ; : decimal DECIMAL ; : cr CR ; : swap SWAP ; : drop DROP ;
: dup DUP ; : over OVER ; : space SPACE ; : spaces SPACES ;
: emit EMIT ; : tryloop DO blink LOOP ; : delay 1D000 * 0 DO 1 DROP LOOP ;

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

: PADS_BANK0_BASE ( -- adrs ) 4001C000 ;
: SIO_BASE ( -- adrs )        D0000000 ;
: GPIO_base PADS_BANK0_BASE ;
: GPIO25 ( -- n ) 68 ;
: LEDG ( -- adrs ) PADS_BANK0_BASE GPIO25 + ;
: GPIO_OUT ( -- n ) 10 ; ( bits 29:0 per GPIO )
: GPIO_OUT_SET ( -- n ) 14 ; ( Table 22 )
: GPIO_OUT_CLR ( -- n ) 18 ; ( 2.3.1.7 List of Registers )
( 1 7 LSHIFT gives 128 )
( 1  2  4  8  16  32  64  128 )
( 0  1  2  3   4   5   6    7 )
( so  1 2 LSHIFT gives 4 )
( and 1 3 LSHIFT gives 8 )

: P25 19 ( -- n ) ; ( GPIO25 0x19 is 25 decimal )
: LED_OUT SIO_BASE GPIO_OUT + ( -- addr ) ;

( LED_OUTPUT means place the port pin in OUTPUT mode )
: LED_OUTPUT ( -- )
  LED_OUT @ ( -- n )
  1 P25 LSHIFT OR LED_OUT !
;
( LED_INPUT means place the port pin in INPUT mode )
: LED_INPUT ( -- )
  LED_OUT @
  1 P25 LSHIFT INVERT AND LED_OUT !
;
( just an address for LED_OUT_SET )
: LED_OUT_SET SIO_BASE GPIO_OUT_SET + ( -- addr ) ;
: LED_OUT_CLR SIO_BASE GPIO_OUT_CLR + ( -- addr ) ;

( turn on the port pin for the LED with LED_HI )
: LED_HI ( -- )
  LED_OUT_SET @ ( -- n ) ( gave 0x56 = 86 decimal )
  (  0 1 0 1   0 1 1 0 ) ( 86 decimal )
  1 P25 LSHIFT
  OR LED_OUT_SET ! ;

: LED_LOW_NOPE ( -- ) ( do NOT use )
  LED_OUT_CLR @
  1 P25 LSHIFT INVERT
  AND LED_OUT_CLR ! ;

: LED_LOW ( -- )
  LED_OUT_CLR @
  1 P25 LSHIFT
  OR LED_OUT_CLR ! ;

(  2000000 19 RSHIFT . 1  ok ) 
(  1000000 18 RSHIFT . 1  ok )

( end )
( include gpio.fs )
HEX
: shdelay 3FF 0 DO 1 DROP LOOP ; 
: xldelay ( n -- ) 111 * 0 DO shdelay LOOP ;
( 74 delay close but too rapid want 75 or 76 to slow it )
: ldelay ( n -- )  72 * 0 DO shdelay LOOP ;
: hi LED_HI ; : lo LED_LOW ;
: pip hi shdelay lo ; 
( 7C and A were ten seconds over at 120 pips )
( 79 and A now on trial )
( 72 now ) ( 11:30:40 )
: pips ( n -- ) 0 DO pip  A ldelay LOOP ; 
: heartbeat 999 pips ;

: explaa hex 2 * dup 8 SPACES .  decimal dup 7 SPACES . hex ;
( prints hex vs decimal after doubling )
( use to explore what dot does )
( compare with U. )
