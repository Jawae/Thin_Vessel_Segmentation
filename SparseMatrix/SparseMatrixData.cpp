#define _CRT_SECURE_NO_WARNINGS
#include "SparseMatrixData.h"

#include <iostream>

using namespace std;

SparseMatrixData::SparseMatrixData( unsigned num_rows, unsigned num_cols )
	: ncol( num_cols ), nrow( num_rows ), datacol( nullptr ), datarow( nullptr )
{

}

SparseMatrixData::SparseMatrixData( int num_rows, int num_cols, const double non_zero_value[],
	const int col_index[], const int row_pointer[], int N )
	: ncol( num_cols ), nrow( num_rows ), datacol( nullptr ), datarow( nullptr )
{
	// N==0, then this is a zero matrix, then don't allocate matrix data
	if( N == 0 ) return;

	datarow = new SparseMatrixDataRow( num_rows, num_cols, non_zero_value, col_index, row_pointer, N );
}



SparseMatrixData::~SparseMatrixData(){
	// destro matrix data
	if( datacol ) delete datacol;
	if( datarow ) delete datarow;
}

SparseMatrixDataCol* SparseMatrixData::getCol(){
	if( datarow==nullptr || datacol ) return datacol;

	// memory of the following arrays will be allocated in func dCompRow_to_CompCol
	double* nzval = nullptr;
	int *rowidx = nullptr;
	int *colptr = nullptr;

	dCompRow_to_CompCol_yuchen(
		nrow,						// number of rows
		ncol,						// number of cols
		datarow->nnz,    // number of non-zero entries
		datarow->nzval,             // non-zero entries
		datarow->colind,            // column index
		datarow->rowptr,            // row pointers
		&nzval,                     // non-zero entries (for column-order matrix)
		&rowidx,                    // row indeces
		&colptr );                  // column pointers

	datacol = new SparseMatrixDataCol( nrow, ncol, nzval, rowidx, colptr, datarow->nnz );

	return datacol;
}

SparseMatrixDataRow* SparseMatrixData::getRow(){
	if( datacol==nullptr || datarow ) return datarow;

	// memory of the following arrays will be allocated in func dCompRow_to_CompCol
	double* nzval = nullptr;
	int *colidx = nullptr;
	int *rowptr = nullptr;

	// IMPORTANT!: ncol and nrow is reversed in the following function.
	// This is because dCompRow_to_CompCol is a function for converting
	// row-order sparse matrix to col-order matrix. But it can also be
	// used to comvert a col matrix into a row one if it is carefully used.
	dCompRow_to_CompCol_yuchen(
		ncol,						// number of rows
		nrow,						// number of cols
		datacol->nnz,    // number of non-zero entries
		datacol->nzval,           // non-zero entries
		datacol->rowind,          // pretend it is column index array
		datacol->colptr,          // pretend it is row pointers arrays
		&nzval,                     // non-zero entries (for row-order matrix)
		&colidx,                    // column indeces
		&rowptr );                  // row pointers

	datarow = new SparseMatrixDataRow( nrow, ncol, nzval, colidx, rowptr, datacol->nnz );

	return datarow;
}

void SparseMatrixData::transpose( void ) {
	// tanspose number of rows and columns
	std::swap( nrow, ncol );

	if( datarow && datacol ) {
		// if the matrix is stored as both row-order and col-order
		void* temp = datarow;
		datarow = (SparseMatrixDataRow*) datacol;
		datacol = (SparseMatrixDataCol*) temp;
	}
	else if( datarow )
	{
	    delete datacol;
	    datacol = (SparseMatrixDataCol*) datarow;
		datarow = nullptr;
	}
	else if( datacol )
	{
        delete datarow;
	    datarow = (SparseMatrixDataRow*) datacol;
		datacol = nullptr;
	}
	else
	{
		// both datacol and datarow are NULL
		// this is a empty matrix, nothing to transpose
	}
}

void SparseMatrixData::multiply( const double& value ){
	if( datarow ) {
		for( int i=0; i<datarow->nnz; i++ ) datarow->nzval[i] *= value;
	}
	if( datacol ) {
		for( int i=0; i<datacol->nnz; i++ ) datacol->nzval[i] *= value;
	}
}
