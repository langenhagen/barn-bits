/******************************************************************************
/* @file Cuda specific defines and generic utility/convenience functions.
/*
/*
/* @author langenhagen
/* @version 150104
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers



///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <cuda_runtime.h>

///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS


///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS


/** Collaboratively copies data from one array to another,
 * e.g. from global to shared memory arrays.
 * If number of threads in the block are less or equal the given array size,
 * The first array_size threads are used to load the array.
 * If the size of the array exceeds the number of threads in the block,
 * all N threads in the block load N elements repeatedly until less elements
 * than threads are left. These elements are then loaded by the first threads
 * in the block.
 * CAUTION: Doesn't do the __syncthreads(); for you.
 * @param dst Destination array.
 * @param src Source array that is to be copied.
 * @param size The array size. Both arrays should at least
 *        have the given size.
 */
template<typename T>
__device__
void d_memcpy( T* dst, T* src, const int size) {
    const int n_threads = blockDim.x * blockDim.y * blockDim.z;
    int pos = ( threadIdx.z * blockDim.y + threadIdx.y ) * blockDim.x  +  threadIdx.x;

    while( pos < size ) {

        dst[pos] = src[pos];
        pos += n_threads;
    }
}
