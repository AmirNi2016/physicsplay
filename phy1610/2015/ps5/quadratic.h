/** \file quadratic.h
 */
#if !defined phy1610_ps5_quadratic_h_included
#define phy1610_ps5_quadratic_h_included

#include <cmath>

struct quadratic
{
   double a ;
   double b ;
   double c ;

   quadratic() : a{1.0}, b{0.0}, c{-5.0} {}

   static double function( double x, void * params ) ;
   static double derivative( double x, void * params ) ;
   static void functionAndDerivative( double x, void * params, double * y, double * dy ) ;

   static inline expectedRoot()
   {
      return std::sqrt( 5.0 ) ;
   }
} ;

#endif
