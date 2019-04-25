/******************************************************************************
/* @file Test routines for functions in barn_common.
/*
/* @author langenhagen
/* @version 160130
/*****************************************************************************/
#pragma once


#include "barn_common.hpp"
#include "barn_test/FunctionTest.hpp"

using namespace std;
using namespace unittest;


/// Calls the testing routine
void barn_common_test_all() {

    auto& os = std::cout;
    auto all_passed = true;
    os << "\n";

    os << "Test find_missing_number<int,vector>" << std::endl;
    FunctionTest<size_t, intvec> find_missing_number_test(find_missing_number<int, vector>);
    find_missing_number_test.verbosity_level = verbosity::NORMAL;

    find_missing_number_test.test("0", size_t(0), { 1u,2,3,4,5,6,7,8,9 });
    find_missing_number_test.test("1", size_t(1), { 0u,2,3,4,5,6,7,8,9 });
    find_missing_number_test.test("2", size_t(2), { 0u,1,3,4,5,6,7,8,9 });
    find_missing_number_test.test("3", size_t(3), { 0u,1,2,4,5,6,7,8,9 });
    find_missing_number_test.test("4", size_t(4), { 0u,1,2,3,5,6,7,8,9 });
    find_missing_number_test.test("5", size_t(5), { 0u,1,2,3,4,6,7,8,9 });
    find_missing_number_test.test("6", size_t(6), { 0u,1,2,3,4,5,7,8,9 });
    find_missing_number_test.test("7", size_t(7), { 0u,1,2,3,4,5,6,8,9 });
    find_missing_number_test.test("8", size_t(8), { 0u,1,2,3,4,5,6,7,9 });
    find_missing_number_test.test("9", size_t(9), { 0u,1,2,3,4,5,6,7,8 });
    all_passed &= find_missing_number_test.write_test_series_summary();







    os << "\n";
    if (all_passed) os << "+++ ALL TEST SERIES PASSED +++ :)))";
    else            os << "--- SOME ERRORS OCCURED ---    :(((";
    os << "\n\n\n";
}
