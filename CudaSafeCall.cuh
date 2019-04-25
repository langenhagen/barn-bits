/******************************************************************************
/* @file Simple & generic CUDA error checking macros and functions.
/*
/* inspired by best practices and
/* http://choorucode.com/2011/03/02/how-to-do-error-checking-in-cuda/
/*
/* HOW TO USE:
/*
/*  If you want to enable error checking macros, define the first macro below.
/*  In addition, if you want to enable more careful, but performance hitting
/*  error checking with CudaCheckError() define also the second macro.
/*
/*      #define CUDA_ERROR_CHECK
/*      #define CUDA_ERROR_CHECK_CAREFUL
/*
/*  The following macros can be used for error checking. However, they are
/*  not recommended for production code.
/*
/*      CudaSafeCall()
/*      CudaCheckError()
/*
/*  The functions below are used by the macros.
/*  You should not use them directly.
/*
/*      __cudaSafeCall()
/*      __cudaCheckError()
/*
/*  .
/*
/* @author langenhagen
/* @version 14122
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <iostream>

#include "cuda_runtime.h"

///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS

/// Wrap around a a function that returns a cudaError (cudaError_t resp).
#define CudaSafeCall( err) __cudaSafeCall( err, std::cerr, __FILE__, __LINE__)

/// Call after kernel invocation.
#define CudaCheckError()   __cudaCheckError( std::cerr, __FILE__, __LINE__)


///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS


/// Provides error handling for the given cudaError.
inline bool __cudaSafeCall( cudaError_t err, std::ostream& os, const char *file, const int line) {
    bool ret(true);
#ifdef CUDA_ERROR_CHECK
    if ( cudaSuccess != err) {
        os << "CudaSafeCall() failed at: " << file << ":" << line << " : " << cudaGetErrorString( err) << "\n";
        ret = false;
    }
#endif
    return ret;
}


/// Provides cuda error handling, e.g. after kernel invocation.
inline bool __cudaCheckError( std::ostream& os, const char *file, const int line) {
    bool ret(true);
#ifdef CUDA_ERROR_CHECK
    cudaError_t err = cudaGetLastError();
#ifdef CUDA_ERROR_CHECK_CAREFUL
    err = cudaDeviceSynchronize();
#endif
    if ( cudaSuccess != err) {
        os << "CudaCheckError() failed at: " << file << ":" << line << " : " << cudaGetErrorString( err) << "\n";
        ret = false;
    }
#endif
    return ret;
}
