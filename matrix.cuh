/******************************************************************************
/* @file A simple matrix class.
/*
/*
/* @author langenhagen
/* @version 150104
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers

#include "CudaSafeCall.cuh"

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <iostream>

#include <cuda_runtime.h>

///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS

#ifdef __CUDACC__
#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
#define CUDA_CALLABLE_MEMBER
#endif

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS

/** Simple matrix class.
 */
template<typename T=float>
class Matrix {

public: // vars

    unsigned int rows;
    unsigned int cols;
    unsigned int channels;
    T* data;
    bool data_is_shared;    ///< Whether or not the data is used outside the object.

public: // c'tor & d'tor

    /** Main constructor.
     * @param n_rows The number of rows.
     * @param n_cols The number of columns.
     * @params n_channels The number of channels.
     * @params shared Whether or not the data is shared by another object.
     *         If TRUE, data will not be deallocated on destruction or re-initialisation.
     * @param data_ptr If the matrix data is already in memory,
     *        use this pointer to initialize the matrix data pointer.
     *        if nullptr will be passed, new memory will be automatically allocated.
     */
    __host__
    Matrix( unsigned int n_rows, unsigned int n_cols, unsigned int n_channels=1, bool shared=false, T* data_ptr=nullptr)
        : rows(n_rows), cols(n_cols), channels(n_channels), data_is_shared(shared) {

        if( data_ptr == nullptr)
            this->data = (T*)malloc( this->data_size());
        else
            data = data_ptr;
    }


    /** Destructor.
     */
    __host__
    ~Matrix() {
        if( !data_is_shared)
            free(this->data);
    }


public: // methods

    /** Re-initializes the matrix again effectively deleting all its pevious contents.
     * @param n_rows The number of rows.
     * @param n_cols The number of columns.
     * @params n_channels The number of channels.
     * @return The pointer to the matrix.
     */
    __host__
    inline Matrix<T>* re_init( unsigned int n_rows, unsigned int n_cols, unsigned int n_channels=1) {

        this->rows = n_rows;
        this->cols = n_cols;
        this->channels = n_channels;

        if( !data_is_shared)
            free(this->data);
        this->data = (T*)malloc( this->data_size());

        return this;
    }


    /** Retrieves the number of data elements in the matrix.
     * @return The total number of elements in the matrix.
     */
    CUDA_CALLABLE_MEMBER
    inline unsigned int n_cells() const {
        return this->rows*this->cols*this->channels;
    }


    /** Retrieves the size of the matrix data elements in bytes.
     * @return The size of the matrix elements in bytes.
     */
    CUDA_CALLABLE_MEMBER
    inline unsigned int data_size() const {
        return this->n_cells()*sizeof(T);
    }


    /** Retrieves a reference to the value at the specified position in the matrix.
     * @param r The row.
     * @param c The column.
     * @param channel The channel.
     * @return Reference to the value at the specified matrix position.
     */
    CUDA_CALLABLE_MEMBER
    inline T& at( unsigned int r, unsigned int c, unsigned int channel = 0) const {
        return (this->data[ (r*this->cols + c)*this->channels + channel]);
    }


    /** Retrieves a reference to the value at the specified position in the matrix.
     * @param pos The position in form of dim3(column, row, channel).
     * @return Reference to the value at the specified matrix position.
     */
    CUDA_CALLABLE_MEMBER
    inline T& at( const dim3& pos) const {
        return this->at( pos.y, pos.x, pos.z);
    }


    /** Prints the matrix to the screen. Only good for small matrices.
     * @param show_metadata Whether or not to show the metadata.
     */
    __host__
    void print( bool show_metadata=true) {
        using namespace std;

        cout << "Matrix: " << this << ": =======================\n";

        if( show_metadata) {
            cout << "rows: " << this->rows << "   cols: " << this->cols << "   channels: " << this->channels << "\n";
        }
        cout << "[\n";

        for( unsigned int r=0; r<this->rows; ++r) {
            for( unsigned int c=0; c<this->cols; ++c) {
                cout << "(";

                int ch=0;
                for( ; ch<this->channels-1; ++ch) {
                    cout << this->at( r,c,ch) << ", ";
                }
                cout << this->at( r,c,ch);

                cout << ") ";
            }
            cout << "\n";
        }
        cout << "] =======================================\n";
    }


    /** Checks if the dimensions of this and a given matrix are equal.
     * Rows, columns and channels have to be equal
     * @param rhs Right hand side operand.
     * @return TRUE if the dimensions are equal.
     */
     __host__ __device__
    inline bool equal_dims( const Matrix<T>& rhs) const {
        return this->rows     == rhs.rows &&
               this->cols     == rhs.cols &&
               this->channels == rhs.channels;
    }

public: // operators

    /** Shorthand call to at( dim3).
     * @see Matrix<T>::at(dim3)
     */
    CUDA_CALLABLE_MEMBER
    inline T& operator[]( const dim3& pos) const {
        return at(pos);
    }


public: // host/device transfer methods

    /** Transfers the matrix from host to device.
     * @return The pointer of the transferred matrix.
     */
    __host__
    Matrix<T>* h2d() const {
        // since the field "data" points to different locations on host and device,
        // we have to cudaMalloc in two passes
        Matrix<T>* d;
        Matrix<T>* h_tmp = new Matrix<T>(*this);
        unsigned int size = this->data_size();

        CudaSafeCall( cudaMalloc((void**)&h_tmp->data, size));
        CudaSafeCall( cudaMemcpy( h_tmp->data, this->data, size, cudaMemcpyHostToDevice));
        // *** data copied to device ***

        CudaSafeCall( cudaMalloc( (void**)&d, sizeof(Matrix<T>)));
        CudaSafeCall( cudaMemcpy( d, h_tmp, sizeof(Matrix<T>), cudaMemcpyHostToDevice));

        // since h_tmp->data points to device memory, set it to NULL before deleting h_tmp;
        h_tmp->data = nullptr;
        delete h_tmp;
        return d;
    }


    /** Transfers the matrix to a specified location in device memory.
     * @param d The pointer of the matrix-pendant in device memory.
     *        The matrix on the device and the matrix on the host side
     *        must have equal dimensions.
     * @return TRUE in case of success, FALSE otherwise.
     */
    __host__
    bool h2d( Matrix<T> *d) {
        bool ret;
        unsigned int class_size = sizeof(Matrix<T>);
        Matrix<T>* h_tmp = new Matrix(0,0,0);

        ret = CudaSafeCall( cudaMemcpy( h_tmp, d, class_size, cudaMemcpyDeviceToHost)); // download device matrix header

        if( this->equal_dims( h_tm) ) {
            ret = ret & CudaSafeCall( cudaMemcpy( h_tmp->data, this->data, this->data_size(), cudaMemcpyHostToDevice));
        } else {
            ret = false;
        }

        delete h_tmp;

        return ret;
    }


    /** Transfers a given device matrix to the host.
     * It will de-allocate the old memory on the object site
     * and re-initialize the object.
     * If specified, also deallocates the device memory.
     * @param d A matrix on a device.
     * @param free_device If set TRUE, frees the device memory consumed by the matrix.
     * @return TRUE in case of success, FALSE in case of error.
     */
    __host__
    bool d2h( Matrix<T> *d, bool free_device=false) {
        bool ret;
        unsigned int data_size = this->data_size();
        T* h_data = this->data;
        T* d_data;

        ret = CudaSafeCall( cudaMemcpy( this, d, sizeof(Matrix<T>), cudaMemcpyDeviceToHost)); // copy metadata
        d_data = this->data;

        // reallocate host space if necessary
        if( this->data_size() /*new*/ != data_size /*old*/) {
            if( !data_is_shared)
                free(h_data);
            h_data = (T*)malloc( this->data_size());
        }

        ret = ret & CudaSafeCall( cudaMemcpy( h_data, d_data, data_size, cudaMemcpyDeviceToHost)); // copy data
        this->data = h_data;

        if( free_device) {
            ret = ret & CudaSafeCall( cudaFree( d_data));
            ret = ret & CudaSafeCall( cudaFree(d));
        }

        return ret;
    }
};
