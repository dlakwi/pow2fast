// pow2fast.c

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <math.h>

#include "pow2fast.h"

// implementation -----------------------------------------------------------

/**
 * Following the bit-twiddling idea in:
 *
 * 'A Fast, Compact Approximation of the Exponential Function'
 *  Technical Report IDSIA-07-98
 *  Nicol N. Schraudolph;
 *  IDSIA,
 *  1998-06-24.
 *
 * [Rewritten for floats by HXA7241, 2007.]
 *
 * and the adjustable-lookup idea in:
 *
 * 'Revisiting a basic function on current CPUs: A fast logarithm implementation with adjustable accuracy'
 *  Technical Report ICSI TR-07-002;
 *  Oriol Vinyals, Gerald Friedland, Nikki Mirghafori;
 *  ICSI,
 *  2007-06-21.
 *
 * [Improved (doubled accuracy) and rewritten by HXA7241, 2007.]
 * 
 * from pow(2,X) approximation by rasmithuk.com
 *   https://www.rasmithuk.org.uk/entry/pow-2-approx
 * 
 */

typedef union fiunion
{
  int32_t i;
  float   f;
} fiUNION;

const float   _2p23   =  8388608.0;  // = 2^23
const int32_t base    = 0x3F800000;  // base exponent for values 1.x
const int32_t mask    = 0x007FFFFF;  // mask mantissa
const float   pow2[8] = { 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0 };

#if 0
// debug

void printHex( int x, int precision )
{
  char strHex[16];
  char format[16];

  sprintf( format, "0x%%.%dX", precision );

  sprintf( strHex, format, x );
  Serial.print( strHex );
}

char strFloat[24] = { 0 };

void printFloat( float f )
{
  Serial.print( " " );
  dtostrf( f, 11, 8, &strFloat[0] );
  Serial.print( strFloat ); 
}
#endif

// get pow( 2, x ) (fast!)
//   not tested with negative x
//  (it was designed for positive inputs 0.0 .. 7.0 ~ for a 1 V/octave response)

float pow2fast( float x )
{
  int32_t  w, n;
  uint16_t t;
  float    _2pw, r;
  fiUNION  f, p;
                                                // this could probably be cleaned up -- I wanted to have one operation per line ( - + * [] .. )
  w     = int32_t( x );                         // whole        // f.f = modf( x, &wf );
  f.f   = x - float( w );                       // fraction     // w   = int32_t( wf );
  n     = int32_t( f.f * 256.0 );               // map [0.0 .. 1.0) to [0 .. 256)
  t     = pgm_read_word_near( &pow2tab[ n ] );  // lookup value in PROGMEM table
  p.i   = int32_t( t );                         // avoid overflow in ..
  p.i <<= 7;                                    // 16-bit lookup -> 23-bit mantissa
  p.i  |= base;                                 // base exponent == 2^0
  _2pw  = pow2[ w ];                            // calculate integer multiplier 2^w
  r = _2pw * p.f;                               // pow2( x ) = pow2( integer( x ) ) * pow2( fraction( x ) )

#if 0
  // debug
  Serial.print( "x =" ); printFloat( x ); Serial.print( " ==> " ); Serial.print( w ); Serial.print( " +" ); printFloat( f.f );  Serial.println();
  Serial.print( "n = " ); printHex( n, 2 ); Serial.print( " --> " ); printHex( t,4 ); Serial.print( " > " ); printHex( p.i, 8 ); Serial.print( " ~" ); printFloat( p.f ); Serial.println();
  printFloat( r ); Serial.print( " =" ); printFloat( _2pw ); Serial.print( " *" ); printFloat( p.f ); Serial.println();
#endif

  return r;
}
