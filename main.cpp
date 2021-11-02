#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include "RationalMatrix.h"

bool Test()
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
    for(size_t i=0; i<input.size(); i++)
    {
        std::cout<<"Test "<<i<<": ";

        auto start = std::chrono::high_resolution_clock::now();
        res = input[i].inverse();
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
    std::cout<<"Testing passed\n";
    return true;
}

int main()
{
    Test();
    return 0;
}
