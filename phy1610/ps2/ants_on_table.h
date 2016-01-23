/**
   \file ants_on_table.h
 */
#if !defined phy1610_ps2_ants_on_table_h_included
#define phy1610_ps2_ants_on_table_h_included

#include "rarray"

/**
   Code that simulates ants walking on a table.
   The direction in which they walk, depends on where they are on the table, and they can fall of the edge.
   The simulation prints the number of ants left on the table after every time step.
 */
class ants_on_table
{
   int                  m_table_grid_size ;
   rarray<float, 2>     m_number_of_ants ;
   rarray<float, 2>     m_velocity_of_ants ;

public:

   /**
      \brief Allocate the ant count matrix and the ant velocity per grid point.

      \param table_grid_size [in]
         Total number of grid intervals in each direction.
    */
   ants_on_table( const size_t table_grid_size ) ;

   /**
      \retval The grid size that the simulation was initialized with.
    */
   inline int get_grid_size() const
   {
      return m_table_grid_size ;
   }

   /**
      \brief add the number of ants at each grid location.

      \retval The total number of ants.
    */
   float total_number_of_ants() const ;

   /**
      A simple forward iterator to drive the time stepping iterations.
     */
   class iterator
   {
      ants_on_table *   m_ants_p ;
      int               m_timevalue ;
      rarray<float, 2>  m_new_number_of_ants ;

      // Allow ants_on_table to construct a starting iterator, but nothing else.
      friend class ants_on_table ;

      /**
         An iterator object to be returned from ants_on_table::initialize()
       */
      explicit iterator( ants_on_table * p_ants ) ;

   public:

      /**
         A constructor to specify the end iteration.

         \param number_of_time_intervals [in]
            The number of times the ants walk around before we stop looking at them.
       */
      explicit iterator( const int number_of_time_intervals ) ;

      /**
         Perform one timestep operation.
       */
      iterator& operator++ () ; // Pre-increment

      /**
         Check against an end iterator to see if we've done the final timestep.
       */
      inline bool operator != ( iterator & rhs)
      {
         return m_timevalue != rhs.m_timevalue ;
      }

      /**
         Return the results of the last timestep operation (total number of ants on the table).
        */
      inline float operator* () const
      {
         return m_ants_p->total_number_of_ants() ;
      }

      /**
         Return the time step number that the iteration is on.
       */
      inline int operator()() const
      {
         return m_timevalue ;
      }
   } ;

   /**
      Reset the simulation, putting in a new number of total ants, and initial counts and velocities.
    */
   iterator initialize( const int total_ants ) ;

   /**
      \brief ants walk on a table

    */
   void timestep( iterator & i ) ;
} ;

#endif
