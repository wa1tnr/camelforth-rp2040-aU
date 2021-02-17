: PADS_BANK0_BASE ( -- adrs ) 4001C000 ;
: SIO_BASE ( -- adrs )        D0000000 ;
: GPIO_base PADS_BANK0_BASE ;
: GPIO25 ( -- n ) 68 ;
: LEDG ( -- adrs ) PADS_BANK0_BASE GPIO25 + ;
: GPIO_OUT ( -- n ) 10 ; ( bits 29:0 per GPIO )
: GPIO_OUT_SET ( -- n ) 14 ; ( Table 22 )
( 1 7 LSHIFT gives 128 )
( 1  2  4  8  16  32  64  128 )
( 0  1  2  3   4   5   6    7 )
( so  1 2 LSHIFT gives 4 )
( and 1 3 LSHIFT gives 8 )

: P25 19 ( -- n ) ; ( GPIO25 0x19 is 25 decimal )
: LED_OUT SIO_BASE GPIO_OUT + ( -- addr ) ;
: LED_OUTPUT ( -- )
  LED_OUT @ ( -- n )
  1 P25 LSHIFT OR LED_OUT !
;
: LED_INPUT_UNTEST ( -- ) ( not tested and wrong )
  LED_OUT @
  1 P25 LSHIFT NEGATE AND LED_OUT !
;
: LED_OUT_SET SIO_BASE GPIO_OUT_SET + ( -- addr ) ;
( the ONLY tested word was 'LED_HI' and it did work - LED turned on )
: LED_HI ( -- )
  LED_OUT_SET @ ( -- n ) ( gave 0x56 = 86 decimal )
  (  0 1 0 1   0 1 1 0 ) ( 86 decimal )
  1 P25 LSHIFT
  OR LED_OUT_SET !
;
( end )
