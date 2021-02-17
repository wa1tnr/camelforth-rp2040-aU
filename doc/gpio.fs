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
