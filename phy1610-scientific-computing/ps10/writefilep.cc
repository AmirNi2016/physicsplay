/** \file writefilep.cc */
#include <vector>
#include "physicsplay_build_version.h"
#include "mpitask.h"
#include "rangePartition.h"
#include "iohandler.h"

int main( int argc, char ** argv )
{
   mpitask mpi( &argc, &argv ) ;

   constexpr int N{40} ;
   rangePartition p( N, mpi.m_size, mpi.m_rank ) ;

   std::vector<float> vecX( p.localPartitionSize() + 2 ) ;
   std::vector<float> vecRho( p.localPartitionSize() + 2 ) ;
   rangePartition::subrange r{ p.subsetOfGlobalRangeInThisPartition( 1, N ) } ;
   for( auto j{r.first-1} ; j <= r.second ; j++ )
   {
      int i = p.toLocalDomain( j ) ;

      vecX[i] = j ;
      vecRho[i] = j/10.0 ;
   }

   iohandler io( iohandler::cfg::netcdf, "foo", N, mpi.m_rank, PHYSICSPLAY_COMMIT_INFO ) ;

   io.writeMeta( p.m_myFirstGlobalElementIndex -1,
                 p.localPartitionSize(),
                 &vecX[1],
                 &vecRho[1] ) ;

   // Write out three timeslices of data:
   for ( size_t s{0} ; s < 3 ; s++ )
   {
      for( auto j{r.first-1} ; j <= r.second ; j++ )
      {
         int i = p.toLocalDomain( j ) ;

         vecX[i] ++ ;
      }
      
      io.writeData( s * 0.1,
                    p.m_myFirstGlobalElementIndex -1,
                    p.localPartitionSize(),
                    &vecX[1],
                    &vecRho[1] ) ;
   }

   io.close() ;

   return 0 ;
}
