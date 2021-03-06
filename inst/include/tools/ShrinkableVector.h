#ifndef dplyr_ShrinkableVector_H
#define dplyr_ShrinkableVector_H

namespace Rcpp {
    
    template <int RTYPE>
    class ShrinkableVector {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
        ShrinkableVector( int n ) : data( no_init(n) ), max_size(n), start( internal::r_vector_start<RTYPE>(data) ) {}
        
        inline void resize( int n){
            SETLENGTH( data, n ) ;    
        }
        
        inline operator SEXP() const {
            return data ;
        }
        
        inline void borrow( STORAGE* begin, int n){
            memcpy( start, begin, n * sizeof(STORAGE) );
            SETLENGTH(data, n) ;
        }
        
        ~ShrinkableVector(){
            // restore the initial length so that R can reclaim the memory
            SETLENGTH( data, max_size );   
        }
        
    private:
        Rcpp::Vector<RTYPE> data ;
        int max_size ;
        STORAGE* start ;
    } ;
    
}

#endif
