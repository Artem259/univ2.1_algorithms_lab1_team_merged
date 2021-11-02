#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include "RationalMatrix.h"

bool Test_inverse_GaussJordan()
{
    std::vector<RationalMatrix> input;
    std::vector<RationalMatrix> output;
    //-------------------------------------------------------------------------------------------------//
    // Test 0
    input.push_back(RationalMatrix{{
                    {{6,5},{-7,9}},
                    {{4,7},{1,3}}}});
    output.push_back(RationalMatrix{{
                    {{15,38},{35,38}},
                    {{-90,133},{27,19}}}});
    //-------------------------------------------------------------------------------------------------//
    // Test 1
    input.push_back(RationalMatrix{{
                    {{1,2},{3,4},{0,1}},
                    {{7,8},{-7,13},{1,3}},
                    {{0,1},{-7,9},{-4,5}}}});
    output.push_back(RationalMatrix{{
                    {{1384,1745},{8424,12215},{702,2443}},
                    {{1404,1745},{-5616,12215},{-468,2443}},
                    {{-273,349},{156,349},{-1485,1396}}}});
    //-------------------------------------------------------------------------------------------------//
    // Test 2
    input.push_back(RationalMatrix{{
                    {{7,6},{-1,2},{6,1}},
                    {{1,3},{0,1},{1,3}},
                    {{8,7},{0,1},{78,65}}}});
    output.push_back(RationalMatrix{{
                    {{0,1},{63,1},{-35,2}},
                    {{-2,1},{-573,1},{1015,6}},
                    {{0,1},{-60,1},{35,2}}}});
    //-------------------------------------------------------------------------------------------------//
    // Test 3
    input.push_back(RationalMatrix{{
                    {{4,7},{2,5},{6,74}},
                    {{8,3},{-1,2},{-65,7}},
                    {{8,7},{4,5},{12,74}}}});
    output.push_back(RationalMatrix{{{{0,1}}}});
    //-------------------------------------------------------------------------------------------------//
    // Test 4
    input.push_back(RationalMatrix{{
                    {{4,7},{2,5},{6,74}},
                    {{8,3},{-1,2},{-65,7}},
                    {{0,1},{0,1},{0,1}}}});
    output.push_back(RationalMatrix{{{{0,1}}}});
    //-------------------------------------------------------------------------------------------------//
    // Test 5
    input.push_back(RationalMatrix{{
                    {{1,1},{0,1},{0,1}},
                    {{0,1},{1,1},{0,1}},
                    {{0,1},{0,1},{1,1}}}});
    output.push_back(RationalMatrix{{
                    {{1,1},{0,1},{0,1}},
                    {{0,1},{1,1},{0,1}},
                    {{0,1},{0,1},{1,1}}}});
    //-------------------------------------------------------------------------------------------------//
    // Test 6 (random) [always FAIL]
    /*
    input.push_back({RationalMatrix{300,300}});
    input.back().fillRandom(5);
    output.push_back(RationalMatrix{{{{0,1}}}});
    */
    //-------------------------------------------------------------------------------------------------//
    RationalMatrix res(1,1);
    std::cout<<"Section 1 [inverse_GaussJordan]\n\n";
    for(size_t i=0; i<input.size(); i++)
    {
        std::cout<<"Test "<<i<<": ";

        auto start = std::chrono::high_resolution_clock::now();
        res = input[i].inverse_GaussJordan();
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if(res != output[i])
        {
            std::cout<<"Failed ("<<time.count()<<" ms)\n";
            return false;
        }
        else
        {
            std::cout<<"Passed ("<<time.count()<<" ms)\n";
        }
    }
    std::cout<<"\nSection passed\n";
    return true;
}
bool Test_inverse_byLU()
{
    std::vector<RationalMatrix> input;
    std::vector<RationalMatrix> output;
    //-------------------------------------------------------------------------------------------------//
    // Test 0
    input.push_back(RationalMatrix{ {
                                            {{6,5},{-7,9}},
                                            {{4,7},{1,3}}} });
    output.push_back(RationalMatrix{ {
                                             {{15,38},{35,38}},
                                             {{-90,133},{27,19}}} });
    //-------------------------------------------------------------------------------------------------//
    // Test 1
    input.push_back(RationalMatrix{ {
                                            {{1,2},{3,4},{0,1}},
                                            {{7,8},{-7,13},{1,3}},
                                            {{0,1},{-7,9},{-4,5}}} });
    output.push_back(RationalMatrix{ {
                                             {{1384,1745},{8424,12215},{702,2443}},
                                             {{1404,1745},{-5616,12215},{-468,2443}},
                                             {{-273,349},{156,349},{-1485,1396}}} });
    //-------------------------------------------------------------------------------------------------//
    // Test 2
    input.push_back(RationalMatrix{ {
                                            {{7,6},{-1,2},{6,1}},
                                            {{1,3},{0,1},{1,3}},
                                            {{8,7},{0,1},{78,65}}} });
    output.push_back(RationalMatrix{ {
                                             {{0,1},{63,1},{-35,2}},
                                             {{-2,1},{-573,1},{1015,6}},
                                             {{0,1},{-60,1},{35,2}}} });
    //-------------------------------------------------------------------------------------------------//
    // Test 3
    input.push_back(RationalMatrix{ {
                                            {{4,7},{2,5},{6,74}},
                                            {{8,3},{-1,2},{-65,7}},
                                            {{8,7},{4,5},{12,74}}} });
    output.push_back(RationalMatrix{ {{{0,1}}} });
    //-------------------------------------------------------------------------------------------------//
    // Test 4
    input.push_back(RationalMatrix{ {
                                            {{4,7},{2,5},{6,74}},
                                            {{8,3},{-1,2},{-65,7}},
                                            {{0,1},{0,1},{0,1}}} });
    output.push_back(RationalMatrix{ {{{0,1}}} });
    //-------------------------------------------------------------------------------------------------//
    // Test 5
    input.push_back(RationalMatrix{ {
                                            {{1,1},{0,1},{0,1}},
                                            {{0,1},{1,1},{0,1}},
                                            {{0,1},{0,1},{1,1}}} });
    output.push_back(RationalMatrix{ {
                                             {{1,1},{0,1},{0,1}},
                                             {{0,1},{1,1},{0,1}},
                                             {{0,1},{0,1},{1,1}}} });
    //-------------------------------------------------------------------------------------------------//
    RationalMatrix res(1, 1);
    std::cout<<"Section 1 [inverse_byLU]\n\n";
    for (size_t i = 0; i < input.size(); i++)
    {
        std::cout << "Test " << i << ": ";

        auto start = std::chrono::high_resolution_clock::now();
        res = input[i].inverse_byLU();
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (res != output[i])
        {
            std::cout << "Failed (" << time.count() << " ms)\n";
            return false;
        }
        else
        {
            std::cout << "Passed (" << time.count() << " ms)\n";
        }
    }
    std::cout << "\nSection passed\n";
    return true;
}
bool Test_strassen_matrix_mul(int from, int to, long long d)
{
    if(from>to) return false;
    std::cout<<"Section 1 [strassen_matrix_mul]\n\n";
    for (int k = from; k <= to; k++)
    {
        RationalMatrix mTest1(k, k);
        mTest1.random(d);

        RationalMatrix mTest2(k, k);
        mTest2.random(d);

        RationalMatrix mTest3(k, k);
        auto start1 = std::chrono::high_resolution_clock::now();
        normal_matrix_mul(mTest1, mTest2, mTest3);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

        RationalMatrix mTest4(k, k);
        auto start2 = std::chrono::high_resolution_clock::now();
        strassen_matrix_mul(mTest1, mTest2, mTest4);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);


        std::cout << "Execution time of multiplication by normal algorithm: " << time1.count() << std::endl;
        std::cout << "Execution time of multiplication by Strassen's algorithm: " << time2.count() << std::endl;


        std::cout << "Test " << k-from << ": ";
        if(mTest3==mTest4)
        {
            std::cout << "Passed\n\n";
        }
        else
        {
            std::cout << "Failed\n\n";
            return false;
        }
    }
    std::cout << "Section passed\n";
    return true;
}

int main()
{
    std::cout<<"----------------------------------------------------------------------------\n";
    if(!Test_inverse_GaussJordan()) return 1;
    std::cout<<"----------------------------------------------------------------------------\n";
    if(!Test_inverse_byLU()) return 1;
    std::cout<<"----------------------------------------------------------------------------\n";
    if(!Test_strassen_matrix_mul(65,69, 12)) return 1;
    std::cout<<"----------------------------------------------------------------------------\n";
    return 0;
}
