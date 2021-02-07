// pow2fasttest.ino

// generate 100 x 100 random float values in the range [0.0 .. 1.0)

#include <Arduino.h>
#include <pow2fast.h>

float value[100];

const float scale = 0.001;

float randomfloat2( void )
{
  return float( random( 0, 1000 ) ) * scale;
}

void setup( void )
{
  Serial.begin( 9600 );
  while ( !Serial ) delay( 1 );
  Serial.println( "pow2fast test - 100 floats" );

  randomSeed( analogRead( A0 ) * analogRead( A4 ) );

  for ( int i = 0; i < 100; i++ )
  {
    value[i] = randomfloat2();
  }

  unsigned long t;
  volatile float p;  // volatile so the compiler doesn't 'optimize' it away

  Serial.print( "100 x 100 x pow( 2.0, x ) " );
  t = millis();
  for ( int j = 0; j < 100; j++ )
    for ( int i = 0; i < 100; i++ )
    {
      p = pow( 2.0, value[i] );
    }
  Serial.print( ( millis() - t ) ); Serial.println( " mS" );

  Serial.print( "100 x 100 x pow2fast( x ) " );
  t = millis();
  for ( int j = 0; j < 100; j++ )
    for ( int i = 0; i < 100; i++ )
    {
      p = pow2fast( value[i] );
    }
  Serial.print( ( millis() - t ) ); Serial.println( " mS" );

  Serial.println( "finished" );
}

void loop( void )
{
  // empty
}

// pow2fast test - 100 floats
// 100 x 100 x pow( 2.0, x ) 2704 mS
// 100 x 100 x pow2fast( x ) 383 mS
// finished

// 383/2704 = 0.1416 ~ 14%
// 2704 / 383 = 7.06 ~ 7x

