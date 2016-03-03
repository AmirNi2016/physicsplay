#include <silo.h>
#include <stdio.h>

void writemesh( DBfile * dbfile )
{
   /* Write a rectilinear mesh. */
   float x[] = {0., 1., 2.5, 5.} ;
   float y[] = {0., 2., 2.25, 2.55, 5.} ;
   int dims[] = {4, 5} ;
   int ndims = 2 ;
   float *coords[] = {x, y} ;

   DBPutQuadmesh( dbfile, "quadmesh", NULL, coords, dims, ndims, DB_FLOAT, DB_COLLINEAR, NULL ) ;
}

void writemesh_and_data( DBfile * dbfile )
{
   /* The data must be (NX-1) * (NY-1) since it is zonal. */
   float var1[] = {
      0., 1., 2.,
      3., 4., 5.,
      6., 7., 8.,
      9., 10., 11.
   } ;

   double var2[] = {
      0.00, 1.11, 2.22,
      3.33, 4.44, 5.55,
      6.66, 7.77, 8.88,
      9.99, 10.1, 11.11
   } ;

   int var3[] = {
      0, 1, 2,
      3, 4, 5,
      6, 7, 8,
      9, 10, 11
   } ;

   char var4[] = {
      0, 1, 2,
      3, 4, 5,
      6, 7, 8,
      9, 10, 11
   } ;

   /* Note dims are 1 less than mesh’s dims in each dimension. */
   int dims[]={3, 4} ;
   int ndims = 2 ;

   DBPutQuadvar1( dbfile, "var1", "quadmesh", var1, dims, ndims, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL ) ;

   /* Write a double-precision variable. */
   DBPutQuadvar1( dbfile, "var2", "quadmesh", (float*)var2, dims, ndims, NULL, 0, DB_DOUBLE, DB_ZONECENT, NULL ) ;

   /* Write an integer variable */
   DBPutQuadvar1( dbfile, "var3", "quadmesh", (float*)var3, dims, ndims, NULL, 0, DB_INT, DB_ZONECENT, NULL ) ;

   /* Write a char variable */
   DBPutQuadvar1( dbfile, "var4", "quadmesh", (float*)var4, dims, ndims, NULL, 0, DB_CHAR, DB_ZONECENT, NULL ) ;
}

int main( int argc, char *argv[] )
{
   DBfile * dbfile = NULL ;

   /* Open the Silo file */
   dbfile = DBCreate( "basic.silo", DB_CLOBBER, DB_LOCAL,
                      "Comment about the data", DB_HDF5 ) ;
   if ( dbfile == NULL )
   {
      fprintf( stderr, "Could not create Silo file!\n" ) ;
      return -1 ;
   }

   //writemesh( dbfile ) ;
   writemesh_and_data( dbfile ) ;

   /* Close the Silo file. */
   DBClose( dbfile ) ;

   return 0 ;
}
