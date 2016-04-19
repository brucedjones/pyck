////////////////////////////////////////////////////////////////////////////////
// File: legendre_elliptic_integral_first_kind.c                              //
// Routine(s):                                                                //
//    Legendre_Elliptic_Integral_First_Kind                                   //
///////////////////////////////////////////////////////////////////////////////

#include <math.h>           // required for fabs(), sqrt(), log(), atanl(),
                            // tanl(), sqrtl(), fabsl() and M_PI_2 = pi/2.
#include <float.h>          // required for LDBL_EPSILON, DBL_MAX

//                         Internally Defined Routines                        //

static void Landen_Transform( long double phi, long double parameter,
                                                        double *K, double *F);
static void Elliptic_Integral_First_Kind( long double phi, long double m, 
                                                         double *K, double *F);
static double Large_Modulus(double amplitude, long double k);

//                         Internally Defined Constants                       //

static const long double PI_2 =  1.5707963267948966192313216916397514L; // pi/2
static const long double PI   =  3.1415926535897932384626433832795029L; // pi

////////////////////////////////////////////////////////////////////////////////
// double Legendre_Elliptic_Integral_First_Kind(double amplitude, char arg,   //
//                                                                 double x)  //
//                                                                            //
//  Description:                                                              //
//     Legendre's Elliptic Integral of the First Kind, F(phi,k), is the       //
//     integral from 0 to phi of the integrand                                //
//                   dtheta / sqrt( 1 - k^2 sin^2(theta) ).                   //
//     The upper limit phi is called the amplitude and the parameter k is     //
//     called the modulus.  This integral is even in k and odd in phi.        //
//     If k = 0 or |k| = 1 then the integral can be readily evaluated,        //
//     otherwise it must be approximated.                                     //
//                                                                            //
//     In practise the arguments of the elliptic function of the first kind   //
//     are also given as F(phi \ alpha) or F(phi | m) where the angle alpha,  //
//     called the modular angle, satisfies k = sin(alpha) and the argument    //
//     m = k^2 is simply called the parameter.                                //
//     In terms of these arguments F(phi \ alpha) = F(phi, sin(alpha))        //
//     and F(phi | m) = F(phi, sqrt(m)).                                      //
//                                                                            //
//     If phi = pi / 2, the integral as a function of the modulus k, modular  //
//     angle alpha, or parameter m is called the complete elliptic integral   //
//     of the first kind.                                                     //
//                                                                            //
//     Let F(phi,k) be Legendre's elliptic integral of the first kind where   //
//     phi is the amplitude and k is the modulus, k' = sqrt(1-k^2) is the     //
//     complementary modulus.                                                 //
//                                                                            //
//  Arguments:                                                                //
//     double  amplitude                                                      //
//                The upper limit of the integral.                            //
//     char    arg                                                            //
//                The type of argument of the second argument of F():         //
//                  If arg = 'k', then x = k, the modulus of F(phi,k).        //
//                  If arg = 'a', then x = alpha, the modular angle of        //
//                                F(phi \ alpha), alpha in radians.           //
//                  If arg = 'm', then x = m, the parameter of F(phi | m).    //
//                  The value of arg defaults to 'k'.                         //
//     double  x                                                              //
//                The second argument of the elliptic function F(phi,x),      //
//                F(phi \ alpha) or F(phi | m) corresponding to the value of  //
//                'arg'.                                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the elliptic integral of the first kind for the given     //
//     amplitude and modulus, modular angle, or parameter.  Note that if      //
//     |modulus| = 1 and |amplitude| >= pi / 2 then the integral diverges and //
//     sign(amplitude) * DBL_MAX is returned.  If |modulus| > 1, then         //
//     the real part of the integral is returned.                             //
//                                                                            //
//  Example:                                                                  //
//     double f, phi;                                                         //
//     double m, k, a;                                                        //
//                                                                            //
//     ( code to initialize phi and a )                                       //
//                                                                            //
//     k = sin(a);                                                            //
//     m = k * k;                                                             //
//     f = Legendre_Elliptic_Integral_First_Kind( phi, 'a', a );              //
//     printf("F(phi \ alpha) = %12.6f where phi = %12.6f, angle(radians) =   //
//                                                    %12.6f\n",f, phi, a);   //
//     f = Legendre_Elliptic_Integral_First_Kind( phi, 'k', k );              //
//     printf("F(phi,k) = %12.6f where phi = %12.6f, k = %12.6f\n",f, phi, k);//
//     f = Legendre_Elliptic_Integral_First_Kind( phi, 'm', m );              //
//     printf("F(phi|m) = %12.6f where phi = %12.6f, m = %12.6f\n",f, phi, m);//
////////////////////////////////////////////////////////////////////////////////

double Legendre_Elliptic_Integral_First_Kind(double amplitude, char arg, 
                                                                      double x)
{
   long double phi;
   long double k, m;
   double K,F;
   int n;
   int sgn_amplitude = (amplitude >= 0.0) ? 1 : -1;

                  // Check for special case: amplitude = 0 //

   if ( amplitude == 0.0 ) return 0.0;

                   // Check for special case: modulus = 0 //

   if ( x == 0.0 ) return amplitude;

 // Convert modulus, modular angle, or parameter to modulus and parameter. //

   switch (arg) {
      case 'k': k = fabsl((long double) x);
                m = k * k;
                break;
      case 'm': m = (long double) x;
                k = sqrtl(fabsl(m));
                break;
      case 'a': k = fabs(sinl((long double)x));
                m = k * k;
                break;
      default:  k = fabsl((long double) x);
                m = k * k;
   }

                  // Check for most common case 0 < m < 1. //
   
   if ( m > 0.0L && m < 1.0L ) {
      Elliptic_Integral_First_Kind( fabsl((long double) amplitude), m, &K, &F);
      return (double) (sgn_amplitude * F);
   }

          // Check for case m < 0 i.e. a purely imaginary modulus. //
   
   if (m < 0.0L ) {
      phi = PI_2 - fabsl((long double) amplitude);
      Elliptic_Integral_First_Kind( fabsl(phi), fabsl(m / (1.0L - m)), &K, &F);
      if (phi > PI_2)
         return (double) (sgn_amplitude * (K + F) / sqrtl(1.0 - m));
      else 
         return (double) (sgn_amplitude * (K - F) / sqrtl(1.0 - m));
   }

                        // Check for the case m = 1. //

   if ( m == 1.0L ) {
      if ( fabs(amplitude) >= M_PI_2) return sgn_amplitude * DBL_MAX;
      x = tan(amplitude);
      return sgn_amplitude * (log(fabs(x) + sqrt(1.0 + x * x)));
   }

                   // Check for the remaining case m > 1. //

   return sgn_amplitude * Large_Modulus(fabs(amplitude), k);

}

////////////////////////////////////////////////////////////////////////////////
// static void Elliptic_Integral_First_Kind( long double phi, long double m,  //
//                                                     double *K, double *F)  //
//                                                                            //
//  Description:                                                              //
//     This routine calculates Legendre's Elliptic Integral of the First Kind,//
//     F(phi | m) for 0 < m < 1.                                              //
//                                                                            //
//  Arguments:                                                                //
//     long double phi                                                        //
//                The upper limit of the integral.                            //
//     long double m                                                          //
//                The parameter of the Elliptic Integral of the first kind.   //
//                0 < m < 1.                                                  //
//     double *K                                                              //
//                The complete elliptic integral of the first kind,           //
//                F(pi/2 | m).                                                //
//     double *F                                                              //
//                The incomplete elliptic integral of the first kind,         //
//                F(phi | m).                                                 //
//                                                                            //
//  Return Value:                                                             //
//     The values of the complete and incomplete elliptic integrals of the    //
//     first kind for the given parameter m, 0 < m < 1, are returned via the  //
//     argument list.                                                         //
//                                                                            //
//  Example:                                                                  //
//     double F,K;                                                            //
//     long double phi, m;                                                    //
//                                                                            //
//     ( code to initialize phi and m )                                       //
//                                                                            //
//     Elliptic_Integral_First_Kind( phi, m, &K, &F );                        //
//     printf("F(phi |m) = %12.6f where phi = %12.6Lf, m =                    //
//                                                   %12.6Lf\n",F, phi, m);   //
////////////////////////////////////////////////////////////////////////////////

static void Elliptic_Integral_First_Kind(long double phi, long double m,
                                                          double *K, double *F)
{ 
   int n;

   n = (int) ( ( phi + PI_2 ) / PI );
   phi -= n * PI;
   n += n;
   Landen_Transform( fabsl(phi), m, K, F);
   if (phi >= 0.0) *F +=  n * *K;
   else *F = n * *K - *F;

   return;
}

////////////////////////////////////////////////////////////////////////////////
// static double Large_Modulus( double amplitude, long double k)              //
//                                                                            //
//  Description:                                                              //
//     This routine calculates the real part of Legendre's Elliptic Integral  //
//     of the First Kind, Re[ F(amplitude,k) ] for  k > 1.                    //
//                                                                            //
//  Arguments:                                                                //
//     double amplitude                                                       //
//                The upper limit of the integral.                            //
//     long double k                                                          //
//                The modulus of the Elliptic Integral of the first kind.     //
//                k > 1.                                                      //
//                                                                            //
//  Return Value:                                                             //
//     The real part of the value of the incomplete elliptic integral of the  //
//     first kind for the given modulus k, k > 1 and amplitude > 0.           //
//                                                                            //
//  Example:                                                                  //
//     long double k;                                                         //
//     double phi, F;                                                         //
//                                                                            //
//                                                                            //
//     ( code to initialize phi > 0 and k > 1 )                               //
//                                                                            //
//     F = Large_Modulus( amplitude, k );                                     //
//     printf("Re[F(phi,k)] = %12.6f where phi = %12.6Lf, k =                 //
//                                                    %12.6f\n",F, phi, k);   //
////////////////////////////////////////////////////////////////////////////////

static double Large_Modulus(double amplitude, long double k)
{
   double F, K; 
   long double phi = (long double) amplitude;
   long double sin_phi;
   int n;

   n = (int) ( ( phi + PI_2 ) / PI );
   phi -= n * PI;
   n += n;
   
   sin_phi = sinl(phi);
   if ( fabsl(sin_phi) >= 1.0L / k ) 
      if (phi > 0.0L) phi = PI_2;
      else phi = -PI_2;
   else phi = asinl(k * sin_phi);
   Landen_Transform( fabsl(phi), 1.0L/(k*k) , &K, &F);
   if (phi >= 0.0L) F +=  n * K;
   else F = n * K - F;
   
   return F/k;
}

////////////////////////////////////////////////////////////////////////////////
// static void Landen_Transform( long double phi, long double parameter,      //
//                                                     double *K, double *F)  //
//                                                                            //
//  Description:                                                              //
//     The common mean method, sometimes called the Gauss transform, is a     //
//     variant of the descending Landen transformation in which two sequences //
//     are formed: Setting a[0] = 1 and g[0] = k', the complementary modulus, //
//     a[i] is the arithmetic average and g[i] is the geometric mean of a[i-1]//
//     and g[i-1], i.e. a[i+1] = (a[i] + g[i])/2 and g[i+1] = sqrt(a[i]*g[i]).//
//     The sequences satisfy the inequalities g[0] < g[1] < ... < a[1] < a[0].//
//     Further, lim g[n] = lim a[n].  The sequence of amplitudes is defined by//
//     setting phi[0] = phi, and for i >= 0,                                  //
//       tan(2^(i+1) phi[i+1] - 2^i phi[i]) = (g[i]/a[i]) tan(2^i phi[i]).    //
//     The elliptic integral of the first kind F(phi,k) = lim phi[n]/g[n].    //
//                                                                            //
//  Arguments:                                                                //
//     long double  phi                                                       //
//                The upper limit of the integral, 0 <= phi < pi / 2.         //
//     long double  parameter                                                 //
//                The parameter, the modulus squared k^2,                     //
//                0 < parameter < 1.                                          //
//     double *K                                                              //
//                The complete elliptic integral of the first kind with       //
//                parameter 'parameter' between 0 and 1.                      //
//     double *F                                                              //
//                The incomplete elliptic integral of the first kind with     //
//                parameter 'parameter' between 0 and 1 and amplitude phi     //
//                with 0 <= phi < pi / 2.                                     //
//                                                                            //
//  Return Value:                                                             //
//     The value of the elliptic integral of the first kind for the given     //
//     amplitude and parameter is returned via F and the value of the         //
//     complete elliptic integral of the first kind for the given parameter   //
//     is returned via K.                                                     //
//                                                                            //
//  Example:                                                                  //
//     long double phi, m;                                                    //
//     double K, F;                                                           //
//                                                                            //
//     ( code to initialize phi and m )                                       //
//                                                                            //
//     Landen_Transform( phi, m, &K, &F );                                    //
////////////////////////////////////////////////////////////////////////////////

static void Landen_Transform( long double phi, long double parameter,
                                                         double *K, double *F) 
{ 
   long double two_n = 1.0L;
   long double a = 1.0L;
   long double g = sqrtl(1.0L - parameter);
   long double a_old;
   long double g_old;
   long double tan_2n_phi;

   while (1) {
      tan_2n_phi = tanl( phi );
      two_n += two_n;
      phi += phi 
          - atanl( (a - g) * tan_2n_phi / (a + g * tan_2n_phi * tan_2n_phi) );
      g_old = g;
      a_old = a;
      a = 0.5L * (g_old + a_old);
      g = sqrtl(g_old * a_old);
      if ( fabsl(a_old - g_old) <= (a_old * LDBL_EPSILON) ) break;
   }
   phi /= two_n;
   *F = (double) (phi / g); 
   *K = (double) (PI_2 / g);
}
