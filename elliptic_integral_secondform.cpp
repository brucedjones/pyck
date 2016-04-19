////////////////////////////////////////////////////////////////////////////////
// File: legendre_elliptic_integral_second_kind.c                             //
// Routine(s):                                                                //
//    Legendre_Elliptic_Integral_Second_Kind                                  //
////////////////////////////////////////////////////////////////////////////////

#include <math.h>           // required for fabs(), sqrt(), log(), atanl(),
                            // tanl(), sqrtl(), fabsl() and M_PI_2 = pi/2.
#include <float.h>          // required for LDBL_EPSILON, DBL_MAX

//                         Internally Defined Routines                        //

static void Landen_Transform( long double phi, long double parameter,
                               double *F, double *Fk, double *E, double *Ek);
static void Elliptic_Integral_Second_Kind( long double phi, long double m, 
                                                  double *Em, double *Em_phi);
static double Large_Modulus(double amplitude, long double k);

//                         Internally Defined Constants                       //

static const long double PI_4 = 0.7853981633974483096156608458198757L; // pi/4
static const long double PI_2 =  1.5707963267948966192313216916397514L; // pi/2
static const long double PI   =  3.1415926535897932384626433832795029L; // pi

////////////////////////////////////////////////////////////////////////////////
// double Legendre_Elliptic_Integral_Second_Kind(double amplitude, char arg,  //
//                                                                 double x)  //
//                                                                            //
//  Description:                                                              //
//     Legendre's Elliptic Integral of the Second Kind, E(phi,k), is the      //
//     integral from 0 to phi of the integrand                                //
//                   sqrt( 1 - k^2 sin^2(theta) ) dtheta .                    //
//     The upper limit phi is called the amplitude and the parameter k is     //
//     called the modulus.  This integral is even in k and odd in phi.        //
//     If k = 0 or |k| = 1 then the integral can be readily evaluated,        //
//     otherwise it must be approximated.                                     //
//     The amplitude must satisfy the condition |amplitude| <= pi / 2.        //
//                                                                            //
//     In practise the arguments the elliptic function of the second kind are //
//     also given as E(phi \ alpha) or E(phi | m) where the angle alpha,      //
//     called the modular angle, satisfies k = sin(alpha) and the argument    //
//     m = k^2 is simply called the parameter.                                //
//     In terms of these arguments  I.e. E(phi \ alpha) = E(phi, sin(alpha))  //
//     and E(phi | m) = E(phi, sqrt(m)).                                      //
//                                                                            //
//     If phi = pi / 2, the integral as a function of the modulus k, modular  //
//     angle alpha, or parameter m is called the complete elliptic integral   //
//     of the second kind.                                                    //
//                                                                            //
//     Let E(phi,k) be Legendre's elliptic integral of the second kind where  //
//     phi is the amplitude and k is the modulus, k' = sqrt(1-k^2) is the     //
//     complementary modulus.                                                 //
//                                                                            //
//  Arguments:                                                                //
//     double  amplitude                                                      //
//                The upper limit of the integral.                            //
//     char    arg                                                            //
//                The type of argument of the second argument of E():         //
//                  If arg = 'k', then x = k, the modulus of E(phi,k).        //
//                  If arg = 'a', then x = alpha, the modular angle of        //
//                                E(phi \ alpha), alpha in radians.           //
//                  If arg = 'm', then x = m, the parameter of E(phi | m).    //
//                  The value of arg defaults to 'k'.                         //
//     double  x                                                              //
//                The second argument of the elliptic function E(phi,x),      //
//                E(phi \ alpha) or E(phi | m) corresponding to the value of  //
//                'arg'.                                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the elliptic integral of the first kind for the given     //
//     amplitude and modulus, modular angle, or parameter.  Note that if      //
//     |modulus| > 1, then the real part of the integral is returned.         //
//                                                                            //
//  Example:                                                                  //
//     double e, phi;                                                         //
//     double m, k, a;                                                        //
//                                                                            //
//     ( code to initialize phi and a )                                       //
//                                                                            //
//     k = sin(a);                                                            //
//     m = k * k;                                                             //
//     e = Legendre_Elliptic_Integral_Second_Kind( phi, 'a', a );             //
//     printf("E(phi \ alpha) = %12.6f where phi = %12.6f, angle(radians) =   //
//                                                    %12.6f\n",e, phi, a);   //
//     e = Legendre_Elliptic_Integral_Second_Kind( phi, 'k', k );             //
//     printf("E(phi,k) = %12.6f where phi = %12.6f, k = %12.6f\n",e, phi, k);//
//     e = Legendre_Elliptic_Integral_First_Kind( phi, 'm', m );              //
//     printf("E(phi|m) = %12.6f where phi = %12.6f, m = %12.6f\n",e, phi, m);//
////////////////////////////////////////////////////////////////////////////////

double Legendre_Elliptic_Integral_Second_Kind(double amplitude, char arg,
                                                                      double x)
{
   long double phi;
   long double k, m;
   double Em, Em_phi;
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
      case 'a': k = sinl((long double)x);
                m = k * k;
                break;
      default:  k = fabsl((long double) x);
                m = k * k;
   }

                  // Check for most common case 0 < m < 1. //
   
   if ( m > 0.0L && m < 1.0L ) {
      Elliptic_Integral_Second_Kind( fabsl((long double) amplitude), m,
                                                                &Em, &Em_phi);
      return (double) (sgn_amplitude * Em_phi);
   }

          // Check for case m < 0 i.e. a purely imaginary modulus. //
   
   if (m < 0.0L ) {
      phi = PI_2 - fabsl((long double) amplitude);
      Elliptic_Integral_Second_Kind( fabsl(phi), fabsl(m / (1.0L - m)),
                                                                 &Em, &Em_phi);
      if (phi > PI_2)
         return (double) (sgn_amplitude * (Em + Em_phi) * sqrtl(1.0L - m));
      else 
         return (double) (sgn_amplitude * (Em - Em_phi) * sqrtl(1.0L - m));
   }

                        // Check for the case m = 1. //

   if ( m == 1.0L ) {
      if ( fabs(amplitude) <= M_PI_2) return sin(amplitude);
      n = (int) ( (amplitude + M_PI_2) / M_PI );
      n += n;
      return (double) n + sin(amplitude - n * M_PI);
   }

                   // Check for the remaining case m > 1. //

   return sgn_amplitude * Large_Modulus(fabs(amplitude), k);

}

////////////////////////////////////////////////////////////////////////////////
// static void Elliptic_Integral_Second_Kind(long double phi, long double m,  //
//                                               double *Em, double *Em_phi ) //
//                                                                            //
//  Description:                                                              //
//     This routine calculates Legendre's Elliptic Integral of the Second     //
//     Kind E(phi | m) for 0 < m < 1.                                         //
//                                                                            //
//  Arguments:                                                                //
//     long double phi                                                        //
//                The upper limit of the integral.                            //
//     long double m                                                          //
//                The parameter of the Elliptic Integral of the second kind.  //
//                0 < m < 1.                                                  //
//     double *Em                                                             //
//                The complete elliptic integral of the first kind,           //
//                E(pi/2 | m).                                                //
//     double *Em_phi                                                         //
//                The incomplete elliptic integral of the first kind,         //
//                E(phi | m).                                                 //
//                                                                            //
//  Return Value:                                                             //
//     The values of the complete and incomplete elliptic integrals of the    //
//     second kind for the given parameter m, 0 < m < 1, are returned via the //
//     argument list.                                                         //
//                                                                            //
//  Example:                                                                  //
//     double E,Em;                                                           //
//     long double phi, m;                                                    //
//                                                                            //
//     ( code to initialize phi and m )                                       //
//                                                                            //
//     Elliptic_Integral_Second_Kind( phi, m, &Em, &E );                      //
//     printf("E(phi |m) = %12.6f where phi = %12.6Lf, m =                    //
//                                                   %12.6Lf\n",E, phi, m);   //
////////////////////////////////////////////////////////////////////////////////

static void Elliptic_Integral_Second_Kind(long double phi, long double m,
                                                   double *Em, double *Em_phi)
{
   double F,Fk;
   int n;

   n = (int) ( ( phi + PI_2 ) / PI );
   phi -= n * PI;
   n += n;
   Landen_Transform( fabsl(phi), m, &F, &Fk, Em_phi, Em);
   if (phi >= 0.0) *Em_phi +=  n * *Em;
   else *Em_phi = n * *Em - *Em_phi;

   return;
}

////////////////////////////////////////////////////////////////////////////////
// static double Large_Modulus( double amplitude, long double k)              //
//                                                                            //
//  Description:                                                              //
//     This routine calculates the real part of Legendre's Elliptic Integral  //
//     of the Second Kind, Re[ E(amplitude,k) ] for  k > 1.                   //
//                                                                            //
//  Arguments:                                                                //
//     double amplitude                                                       //
//                The upper limit of the integral.                            //
//     long double k                                                          //
//                The modulus of the Elliptic Integral of the second kind.    //
//                k > 1.                                                      //
//                                                                            //
//  Return Value:                                                             //
//     The real part of the value of the incomplete elliptic integral of the  //
//     second kind for the given modulus k, k > 1 and amplitude > 0.          //
//                                                                            //
//  Example:                                                                  //
//     long double k;                                                         //
//     double phi, E;                                                         //
//                                                                            //
//                                                                            //
//     ( code to initialize phi > 0 and k > 1 )                               //
//                                                                            //
//     E = Large_Modulus( amplitude, k );                                     //
//     printf("Re[E(phi,k)] = %12.6f where phi = %12.6Lf, k =                 //
//                                                    %12.6f\n",E, phi, k);   //
////////////////////////////////////////////////////////////////////////////////

static double Large_Modulus(double amplitude, long double k)
{
   double F, K, E, Ek; 
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
   Landen_Transform( fabsl(phi), 1.0L/(k*k) , &F, &K, &E, &Ek);
   Ek = k * Ek + (1.0L - k*k) * K / k;
   E = k * E + (1.0 - k*k) * F / k;
   if (phi >= 0.0L) E +=  n * Ek;
   else E = n * Ek - E;
   
   return E;
}

////////////////////////////////////////////////////////////////////////////////
// static void Landen_Transform( long double phi, long double parameter,      //
//                             double *F, double *Fk, double *E, double *Ek)  //
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
//     The elliptic integral of the second kind                               //
//           E(phi,k) = lim (phi[n]/4g[n]) (4 - 2k^2 - Sum(2^j(a[j]-g[j])^2)  //
//                             + (1/2) Sum((a[j] - g[j])sin(2^j+1 phi[j+1]))  //
//     where the limit is as n -> inf and both Sums extend from j = 0 to n.   //
//                                                                            //
//  Arguments:                                                                //
//     long double  phi                                                       //
//                The upper limit of the integral, 0 <= phi <= pi / 2.        //
//     long double  parameter                                                 //
//                The parameter, the modulus squared k^2,                     //
//                0 < parameter < 1.                                          //
//     double *F                                                              //
//                The incomplete elliptic integral of the first kind with     //
//                parameter 'parameter' between 0 and 1 and amplitude between //
//                0 and pi/2.                                                 //
//     double *Fk                                                             //
//                The complete elliptic integral of the first kind with       //
//                parameter 'parameter' between 0 and 1.                      //
//     double *E                                                              //
//                The incomplete elliptic integral of the second kind with    //
//                parameter 'parameter' between 0 and 1 and amplitude between //
//                0 and pi/2.                                                 //
//     double *Ek                                                             //
//                The complete elliptic integral of the first second with     //
//                parameter 'parameter' between 0 and 1.                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the elliptic integral of the first kind for the given     //
//     amplitude and parameter is returned via F, the value of the complete   //
//     elliptic integral of the first kind for the given parameter is returned//
//     via Fk, the value of the elliptic integral of the second kind for the  //
//     given amplitude and parameter is returned via E, and the value of the  //
//     complete elliptic integral of the second kind for the given parameter  //
//     is returned via Ek.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double phi, m;                                                    //
//     double F, Fk, E, Ek;                                                   //
//                                                                            //
//     ( code to initialize phi and m )                                       //
//                                                                            //
//     Landen_Transform( phi, m, &F, &Fk, &E, &Ek );                          //
////////////////////////////////////////////////////////////////////////////////

static void Landen_Transform( long double phi, long double parameter,
                                 double *F, double *Fk, double *E, double *Ek) 
{ 
   long double two_n = 1.0L;
   long double a = 1.0L;
   long double g = sqrtl(1.0L - parameter);
   long double a_old;
   long double g_old;
   long double tan_2n_phi;
   long double sum = 2.0L * (2.0L - parameter);
   long double integral = 0.0L;

   while (1) {
      tan_2n_phi = tanl(two_n * phi );
      sum -= two_n * (a - g) * (a - g);
      two_n += two_n;
      phi -= atanl( (a - g) * tan_2n_phi / (a + g * tan_2n_phi * tan_2n_phi) )
                                                                       / two_n;
      integral += (a - g) * sinl(two_n * phi);
      g_old = g;
      a_old = a;
      a = 0.5L * (g_old + a_old);
      g = sqrtl(g_old * a_old);
      if ( fabsl(a_old - g_old) <= (a_old * LDBL_EPSILON) ) break;
   }
   *F = (double) (phi / g);
   *Fk = (double) (PI_2 / g);
   *E =  (double) (0.5 * integral + 0.25 * sum * phi / g);
   *Ek = (double) ((PI_4 / a) * sum / 2.0L);
}
