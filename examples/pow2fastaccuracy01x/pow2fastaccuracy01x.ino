// fpow2accuracy01x.ino

// test 10 float values in the range 0.0 to +1.0

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <pow2fast.h>

float value[10];
float diff[10];

void printD( int d )
{
  if ( d < 100 ) Serial.print( " " );
  if ( d <  10 ) Serial.print( " " );
  Serial.print( d );
}

void setup( void )
{
  float p0, p1;

  Serial.begin( 9600 );
  while ( !Serial ) delay( 1 );
  Serial.println( "pow2fast accuracy - 10 floats [0.0 .. 1.0)" );

  for ( int i = 0; i < 10; i++ )
  {
    value[i] = float( i ) / 10.0;
  }

  unsigned long t;
  volatile float p;
  char str[32];

  Serial.println( "  i     random   pow(2,x)  pow2fast(x)       diff          %" );
  Serial.println( "---  ---------  ---------  -----------  ---------  ---------" );
  for ( int i = 0; i < 10; i++ )
  {
    p0 = pow( 2.0, value[i] );
    p1 = pow2fast( value[i] );
    diff[i] = p0 - p1;

    printD( i );
    dtostrf(       value[i], 11, 5, &str[0] ); Serial.print( str );
    dtostrf(       p0,       11, 5, &str[0] ); Serial.print( str );
    dtostrf(       p1,       13, 5, &str[0] ); Serial.print( str );
    dtostrf(       diff[i],  11, 5, &str[0] ); Serial.print( str );
    dtostrf( 100.0*diff[i],  11, 5, &str[0] ); Serial.println( str );
  }

  Serial.println( "---  ---------  ---------  -----------  ---------  ---------" );
  Serial.println( "finished" );
}

void loop( void )
{
  // empty
}
