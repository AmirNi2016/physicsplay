/** \file mysolver.h
 */
#if !defined phy1610_ps5_mysolver_h_included
#define phy1610_ps5_mysolver_h_included

#include <gsl/gsl_roots.h>
#include "integers.h"

/**
   interval and derivative solver methods supplied by gsl
 */
enum class solver
{
   undefined,
   bisection,
   falsepos,
   brent,
   newton,
   secant,
   steffenson
} ;

inline bool isFdfSolver( solver s )
{
   return s >= solver::newton ;
}

const gsl_root_fsolver_type * solverToMethod( const solver whichSolver ) ;

const gsl_root_fdfsolver_type * solverToFdfMethod( const solver whichSolver ) ;

/**
   gsl based derivative root solver.
 */
template <class paramType>
class fdfSolver
{
   const gsl_root_fdfsolver_type *  T ;
   gsl_function_fdf                 F ;
   gsl_root_fdfsolver *             s ;
   paramType                        params ;

public:
   /**
      Initialize and allocation resources for root solving algorithm.
    */
   fdfSolver( const solver whichSolver ) ;

   /**
      Deallocate resources.
    */
   ~fdfSolver() ;

   /**
      Perform the root solution iteration.

      \param x0 [in]
         Initial guess.

      \param max_iter [in]
         Abort iteration if not finished in this many iterations.

      \param err [in]
         Required root precision.
    */
   int iterate( const double x0, const Uint max_iter, const double err ) ;
} ;

/**
   gsl based interval based root solver.
 */
template <class paramType>
class fSolver
{
   const gsl_root_fsolver_type *  T ;
   gsl_function                   F ;
   gsl_root_fsolver *             s ;
   paramType                      params ;

public:
   /**
      Initialize and allocation resources for root solving algorithm.
    */
   fSolver( const solver whichSolver ) ;

   /**
      Deallocate resources.
    */
   ~fSolver() ;

   /**
      Attempt to increase the initial interval to find one that brackets the root.

      \param x_min [in|out]
         starting lower bound on the interval.

      \param x_max [in|out]
         starting upper bound on the interval.

      \param iter_max [in]
         maximum number of times to attempt increasing the interval looking for a sign alternation.

      \retval
         true if a bracketing interval was found.
         false if a bracketing interval was not found.
    */
   bool increaseIntervalIfNotBracketed( double & x_min, double & x_max, const Uint iter_max ) ;

   /**
      Perform the root solution iteration.

      \param x_lo [in]
         Initial lower bound for the interval that contains the root.

      \param x_hi [in]
         Initial upper bound for the interval that contains the root.

      \param max_iter [in]
         Abort iteration if not finished in this many iterations.

      \param r_expected [in]
         Expected root (for informational purposes in verbose print loop).

      \param err [in]
         Required root precision.
    */
   int iterate( const double x_lo, const double x_hi, const Uint max_iter, const double err ) ;
} ;

#endif