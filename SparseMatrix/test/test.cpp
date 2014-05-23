#include "gtest/gtest.h"

#include "SparseMatrixTest.h"

#include <iostream>
using namespace std;


//TEST_F(SparseMatrixTest, Constructor){
//        /* [19,  0, 21, 21,  0,  0;
//    	12, 21,  0,  0,  0,  0;
//    	 0, 12, 16,  0,  0,  0;
//    	 0,  0,  0,  5, 21,  0;
//    	12, 12,  0,  0, 18,  1]; */
//    const int N = 13;
//    double non_zero_value_A1[N] = {19, 21, 21, 12, 21, 12, 16,  5, 21, 12, 12, 18, 1};
//    int    col_index_A1[N] =     { 0,  2,  3,  0,  1,  1,  2,  3,  4,  0,  1,  4, 5};
//    int    row_pointer_A1[6] =    { 0,          3,      5,      7,      9,        13};
//    SparseMatrix A1(5, 6, non_zero_value_A1, col_index_A1, row_pointer_A1, N);
//
//    A1.print(cout);
//    cout << A1 << endl;
//
//    SparseMatrix A2 = A1;
//}


TEST_F(SparseMatrixTest, Addition){
    const int row = 5;
    const int col = 5;
    double expetec[row][col] = {
        { 0,    266,   0,  105,  441 },
        { 252,  168,   0,    0,  147 },
        { 144,    0,   0,    0,   84 },
        { 252,  252,   0,   25,  483 },
        { 360,  384,   0,    0,  409 } };

    cout << A1 + A2 << endl;
    test_equal( expetec, A1 + A2 );
}


TEST_F(SparseMatrixTest, Transpose){
    const int row = 5;
    const int col = 5;
    double expetec[row][col] = {
        { 0,    266,   0,  105,  441 },
        { 252,  168,   0,    0,  147 },
        { 144,    0,   0,    0,   84 },
        { 252,  252,   0,   25,  483 },
        { 360,  384,   0,    0,  409 } };

    cout << A1.clone() << endl;


    cout << A1.t() << endl;
    test_equal( expetec, A1 * A1.t() );
}





int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    int flag = RUN_ALL_TESTS();
    system("pause");
    return flag;
}


