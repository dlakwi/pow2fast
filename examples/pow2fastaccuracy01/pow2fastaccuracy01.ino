// fpow2accuracy01.ino

// test 100 random float values in the range 0.0 to +1.0

#include <Arduino.h>
#include <pow2fast.h>

float value[100];
float diff[100];

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
  Serial.println( "pow2fast accuracy - 100 floats [0.0 .. 1.0)" );

  for ( int i = 0; i < 100; i++ )
  {
    value[i] = float( i ) / 100.0;
  }

  unsigned long t;
  volatile float p;
  char str[32];
  float maxdiff = 0.0;

  Serial.println( "  i     random   pow(2,x)  pow2fast(x)       diff          %" );
  Serial.println( "---  ---------  ---------  -----------  ---------  ---------" );
  for ( int i = 0; i < 100; i++ )
  {
    p0 = pow( 2.0, value[i] );
    p1 = pow2fast( value[i] );
    diff[i] = fabs( p0 - p1 );
    if ( diff[i] > maxdiff ) maxdiff = diff[i];

    printD( i );
    dtostrf(       value[i], 11, 5, &str[0] ); Serial.print( str );
    dtostrf(       p0,       11, 5, &str[0] ); Serial.print( str );
    dtostrf(       p1,       13, 5, &str[0] ); Serial.print( str );
    dtostrf(       diff[i],  11, 5, &str[0] ); Serial.print( str );
    dtostrf( 100.0*diff[i],  11, 5, &str[0] ); Serial.println( str );
  }

  Serial.println( "---  ---------  ---------  -----------  ---------  ---------" );
  Serial.print( "maximum difference:" );
  dtostrf(       maxdiff, 11, 5, &str[0] ); Serial.print( str );
  dtostrf( 100.0*maxdiff, 11, 5, &str[0] ); Serial.print( str ); Serial.println( "%" );
  Serial.println( "finished" );
}

void loop( void )
{
  // empty
}

// pow2fast accuracy - 100 floats [0.0 .. 1.0)
//   i     random   pow(2,x)  pow2fast(x)       diff          %
// ---  ---------  ---------  -----------  ---------  ---------
//   0    0.00000    1.00000      1.00134    0.00134    0.13428
//   1    0.01000    1.00696      1.00679    0.00017    0.01655
//   2    0.02000    1.01396      1.01500    0.00104    0.10399
//   3    0.03000    1.02101      1.02051    0.00050    0.05044
//   4    0.04000    1.02811      1.02882    0.00071    0.07100
//   5    0.05000    1.03526      1.03442    0.00084    0.08411
//   6    0.06000    1.04247      1.04285    0.00038    0.03809
//   7    0.07000    1.04972      1.04852    0.00119    0.11938
//   8    0.08000    1.05702      1.05707    0.00005    0.00498
//   9    0.09000    1.06437      1.06569    0.00132    0.13189
//  10    0.10000    1.07177      1.07147    0.00030    0.03012
//  11    0.11000    1.07923      1.08022    0.00099    0.09872
//  12    0.12000    1.08673      1.08607    0.00066    0.06601
//  13    0.13000    1.09429      1.09494    0.00065    0.06465
//  14    0.14000    1.10191      1.10089    0.00101    0.10141
//  15    0.15000    1.10957      1.10986    0.00029    0.02937
//  16    0.16000    1.11729      1.11589    0.00140    0.13967
//  17    0.17000    1.12506      1.12498    0.00007    0.00738
//  18    0.18000    1.13288      1.13417    0.00129    0.12866
//  19    0.19000    1.14076      1.14032    0.00044    0.04439
//  20    0.20000    1.14870      1.14963    0.00093    0.09294
//  21    0.21000    1.15669      1.15587    0.00082    0.08197
//  22    0.22000    1.16473      1.16530    0.00056    0.05648
//  23    0.23000    1.17283      1.17162    0.00122    0.12194
//  24    0.24000    1.18099      1.18118    0.00019    0.01903
//  25    0.25000    1.18921      1.19081    0.00160    0.16041
//  26    0.26000    1.19748      1.19728    0.00020    0.01979
//  27    0.27000    1.20581      1.20705    0.00124    0.12387
//  28    0.28000    1.21419      1.21359    0.00060    0.06024
//  29    0.29000    1.22264      1.22350    0.00086    0.08552
//  30    0.30000    1.23114      1.23013    0.00101    0.10114
//  31    0.31000    1.23971      1.24017    0.00047    0.04656
//  32    0.32000    1.24833      1.24690    0.00143    0.14281
//  33    0.33000    1.25701      1.25708    0.00007    0.00666
//  34    0.34000    1.26576      1.26733    0.00158    0.15774
//  35    0.35000    1.27456      1.27420    0.00036    0.03601
//  36    0.36000    1.28343      1.28461    0.00118    0.11810
//  37    0.37000    1.29235      1.29158    0.00077    0.07726
//  38    0.38000    1.30134      1.30211    0.00077    0.07669
//  39    0.39000    1.31039      1.30917    0.00122    0.12199
//  40    0.40000    1.31951      1.31985    0.00035    0.03468
//  41    0.41000    1.32869      1.32703    0.00166    0.16594
//  42    0.42000    1.33793      1.33784    0.00008    0.00827
//  43    0.43000    1.34723      1.34875    0.00152    0.15212
//  44    0.44000    1.35660      1.35608    0.00053    0.05252
//  45    0.45000    1.36604      1.36714    0.00110    0.11015
//  46    0.46000    1.37554      1.37457    0.00097    0.09692
//  47    0.47000    1.38511      1.38577    0.00066    0.06633
//  48    0.48000    1.39474      1.39330    0.00145    0.14484
//  49    0.49000    1.40444      1.40466    0.00022    0.02182
//  50    0.50000    1.41421      1.41612    0.00191    0.19089
//  51    0.51000    1.42405      1.42381    0.00024    0.02372
//  52    0.52000    1.43396      1.43542    0.00147    0.14696
//  53    0.53000    1.44393      1.44322    0.00071    0.07070
//  54    0.54000    1.45397      1.45499    0.00101    0.10140
//  55    0.55000    1.46409      1.46289    0.00120    0.11951
//  56    0.56000    1.47427      1.47482    0.00055    0.05538
//  57    0.57000    1.48452      1.48283    0.00169    0.16897
//  58    0.58000    1.49485      1.49492    0.00007    0.00696
//  59    0.59000    1.50525      1.50711    0.00186    0.18638
//  60    0.60000    1.51572      1.51530    0.00041    0.04121
//  61    0.61000    1.52626      1.52766    0.00141    0.14050
//  62    0.62000    1.53688      1.53595    0.00093    0.09254
//  63    0.63000    1.54756      1.54848    0.00091    0.09122
//  64    0.64000    1.55833      1.55688    0.00144    0.14443
//  65    0.65000    1.56917      1.56958    0.00041    0.04120
//  66    0.66000    1.58008      1.57811    0.00197    0.19729
//  67    0.67000    1.59107      1.59097    0.00010    0.01001
//  68    0.68000    1.60214      1.60396    0.00182    0.18184
//  69    0.69000    1.61328      1.61267    0.00061    0.06126
//  70    0.70000    1.62450      1.62582    0.00132    0.13192
//  71    0.71000    1.63580      1.63464    0.00116    0.11606
//  72    0.72000    1.64718      1.64798    0.00080    0.07977
//  73    0.73000    1.65864      1.65692    0.00172    0.17177
//  74    0.74000    1.67018      1.67044    0.00026    0.02649
//  75    0.75000    1.68179      1.68407    0.00227    0.22739
//  76    0.76000    1.69349      1.69321    0.00028    0.02837
//  77    0.77000    1.70527      1.70702    0.00175    0.17463
//  78    0.78000    1.71713      1.71629    0.00084    0.08374
//  79    0.79000    1.72907      1.73029    0.00121    0.12112
//  80    0.80000    1.74110      1.73969    0.00142    0.14160
//  81    0.81000    1.75321      1.75388    0.00066    0.06641
//  82    0.82000    1.76541      1.76340    0.00201    0.20088
//  83    0.83000    1.77769      1.77777    0.00009    0.00857
//  84    0.84000    1.79005      1.79227    0.00222    0.22167
//  85    0.85000    1.80250      1.80200    0.00050    0.04990
//  86    0.86000    1.81504      1.81670    0.00166    0.16578
//  87    0.87000    1.82766      1.82657    0.00109    0.10945
//  88    0.88000    1.84038      1.84146    0.00109    0.10859
//  89    0.89000    1.85318      1.85146    0.00172    0.17203
//  90    0.90000    1.86607      1.86656    0.00050    0.04960
//  91    0.91000    1.87905      1.87669    0.00235    0.23519
//  92    0.92000    1.89212      1.89200    0.00012    0.01169
//  93    0.93000    1.90528      1.90744    0.00216    0.21640
//  94    0.94000    1.91853      1.91780    0.00073    0.07273
//  95    0.95000    1.93187      1.93344    0.00157    0.15686
//  96    0.96000    1.94531      1.94394    0.00137    0.13707
//  97    0.97000    1.95884      1.95979    0.00095    0.09526
//  98    0.98000    1.97247      1.97043    0.00204    0.20368
//  99    0.99000    1.98618      1.98650    0.00031    0.03111
// ---  ---------  ---------  -----------  ---------  ---------
// maximum difference:    0.00235    0.23519%
// finished
// 

