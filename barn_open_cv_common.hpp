/******************************************************************************
* @file Contains opencv specific defines and macros and
* generic utility/convenience functions.
*
* @author barn
* @version 150719
******************************************************************************/
#pragma once


///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS


///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS, TYPE DECLARATIONS/IMPLEMENTATIONS and FUNCTIONS

#include <fstream>
#include <functional>
#include <string>
/** Convenience function that writes the contents of a Mat_ to a specified file.
 * Truncates all old entries in that given file.
 * Also does error handling via callbacks.
 * @param filename The name of the file to be written to.
 * @param mat The Mat_ that is to be written to file.
 * @param row_delimeter The delimeter between each row in in the matrix.
 * @param col_delimeter The delimeter between each column in in the matrix.
 * @param error_open_callback The function that is called when opening the file fails.
 *        It takes a string (the filename) as an argument.
 * @param error_write_callback The function that is called when writing to the file fails.
 *        It takes a string (the filename) as an argument.
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
template< class mat_type >
bool to_file( const std::string& filename,
              const mat_type& mat,
              const std::string& row_delimeter = "\n",
              const std::string& col_delimeter = " ",
              std::function< void(const std::string&) > error_open_callback = on_open_file_error,
              std::function< void(const std::string&) > error_write_callback = on_read_file_error) {
    bool ret(true);
    std::ofstream fstream( filename, std::ios::out | std::ios::trunc);
    if(!fstream.is_open() || fstream.bad()) {
        error_open_callback(filename);
        ret = false;
    } else {

        for( int r=0; r<mat.rows; ++r) {
            for( int c=0; c<mat.cols-1; ++c) {

                fstream << mat(r,c) << col_delimeter;

                if( fstream.bad()) {
                    error_write_callback(filename);
                    ret = false;
                    break;
                }
            }
            fstream << mat(r,mat.cols-1);
            if( r < mat.rows-1)
                fstream << row_delimeter;

            if( fstream.bad()) {
                error_write_callback(filename);
                ret = false;
                break;
            }
        }
    }
    return ret;
}


#include <sstream>
/** Retrieves the string giving the Matrix type of an opencv matrix.
 * @param number The numerical matrix type.
 * @return The string representation of the given matrix type.
 */
std::string get_mat_type(int number) {

    std::stringstream ret;

    // find type
    int img_type_int = number%8;
    std::string img_type_string;

    switch (img_type_int) {
        case 0:
            img_type_string = "8U";
            break;
        case 1:
            img_type_string = "8S";
            break;
        case 2:
            img_type_string = "16U";
            break;
        case 3:
            img_type_string = "16S";
            break;
        case 4:
            img_type_string = "32S";
            break;
        case 5:
            img_type_string = "32F";
            break;
        case 6:
            img_type_string = "64F";
            break;
        default:
            break;
    }

    // find channel
    int channel((number/8) + 1);

    ret << "CV_" << img_type_string << "C" << channel;
    return ret.str();
}


#include <functional>
/** Implements a fast iteration over all rows and columns in a convenient way.
 * Sadly, VS2010 doesn't support auto-inference of the template param at invocation,
 * therefore the name.
 * @param mat The matrix over which to iterate.
 * @param callback The function which is to be called on every element of the matrix.
 */
template <typename T>
inline void for_each( cv::Mat_<T>& mat, std::function< void(T& element) > callback) {

    for(int r=0; r<mat.rows; ++r) {
        T* val_ptr = mat.ptr<T>(r);
        for(int c=0; c<mat.cols; ++c) {
            callback( *val_ptr++);
        }
    }
}

#include <functional>
/** Implements a fast iteration over all rows and columns in a convenient way.
 * Sadly, VS2010 doesn't support auto-inference of the template param at invocation,
 * therefore the name.
 * @param mat The matrix over which to iterate.
 * @param callback The function which is to be called on every element of the matrix.
 */
template <typename T>
inline void for_each2( cv::Mat_<T>& mat, std::function< void(T& element, int row, int col) > callback) {

    for(int r=0; r<mat.rows; ++r) {
        T* val_ptr = mat.ptr<T>(r);
        for(int c=0; c<mat.cols; ++c) {
            callback( *val_ptr++, r, c);
        }
    }
}


#include <stdarg.h>
#include <sstream>
/** Convenience function for showing multiple opencv images on screen.
 * I recommend not to use it in final build.
 * There is one call to cv::waitKey(0) at the end of the function.
 * @param n The number of images to be displayed.
 * @param ... n cv::Mat matrices that shall be displayed.
 *            They have to meet the conditions of cv::imshow() to be shown.
 */
void show_imgs(int n, ...) {
    va_list vl;
    va_start(vl,n);

    for(int i=0; i<n ; ++i) {

        cv::Mat& mat = va_arg(vl,cv::Mat);

        std::stringstream window_name;
        window_name << "matrix #" << i;
        cv::imshow( window_name.str(), mat);
    }
    va_end(vl);

    cv::waitKey(0);
}


/** A convenience function for better readability of code.
 * equals to hierarchy[contour_index][3];
 * @param hierarchy A hierarchy of contours.
 * @param contour_index The index of a contour.
 * @return The index of the parent contour, -1 if there is no parent-contour.
 */
inline int parent( std::vector<cv::Vec4i> hierarchy, int contour_index) {
    return hierarchy[contour_index][3];
}


/** Mean shift algorithm.
 * @param im The matrix on which to apply the algorithm. It will be changed by the algorithm.
 * @param the radius of the quadratic sliding window that iterates over the image.
 * @param value_difference The maximum value difference that should occur in order to shift values together. Must not be negative.
 * @param n_iterations The number of iterations the algorithm will be called. It's a simple outmost for-loop.
 * @param value_norm_type The value norm type that is used to calculate the value difference with help of cv::norm.
 */
template< typename T, int CHANNELS>
void mean_shift( cv::Mat_<cv::Vec<T, CHANNELS>> &im,
                 const int radius,
                 const T value_difference,
                 const unsigned int n_iterations = 1,
                 const int value_norm_type = 4) {
    assert( value_difference >= 0 && "input argument value_difference must not be negative");
    typedef cv::Vec<T, CHANNELS> Vec_t;

    for( unsigned int iteration=0; iteration<n_iterations; ++iteration) {

        for( int r=0; r < im.rows; ++r) {
            Vec_t* row_ptr = im.ptr<Vec_t>(r);

            for( int c=0; c < im.cols; ++c) {
                Vec_t mean;
                float count(0);

                // sliding window
                for( int r_off=-radius; r_off < radius; ++r_off) {
                    Vec_t* row_tmp_ptr = im.ptr<Vec_t>( min( max(0, r+r_off), im.rows-1));

                    for( int c_off=-radius; c_off < radius; ++c_off) {
                        const Vec_t& val_tmp = row_tmp_ptr[ min( max(0, c+c_off), im.cols-1)];

                        if( cv::norm( row_ptr[c] /*current pixel*/, val_tmp, value_norm_type) < value_difference) {
                                mean += val_tmp;
                                ++count;
                        }
                    }
                }
                row_ptr[c] = mean / count;
            }
        }
    } // END iteration
}


#include <random>
/** Generates gaussian distributed random points on a matrix.
 * @param mat The matrix that is to be sprinkled with random points of gaussian distribution.
 * @param point_color The color - or value - the gaussian distributed points shall have.
 * @param n_points The number of points to be drawed.
 * @param mean_x The mean in width-dimension.
 * @param mean_y The mean in height-dimension.
 * @param var_x The variance in width-dimension.
 * @param var_y The variance in height-dimension.
 * @return The actual number of points that are drawn. Some points may not be drawn because
 *         their coordinates underflow or exceed the matrix-coordinate-space.
 */
template< typename T>
unsigned int make_gaussian_cloud( cv::Mat_<T>& mat,
                                  const T& point_color, const int n_points,
                                  const double mean_x, const double mean_y,
                                  const double var_x, const double var_y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dx(mean_x, var_x);
    std::normal_distribution<> dy(mean_y, var_y);
    unsigned int ret(0);

    for( unsigned int i=0; i<n_points; ++i) {
        int r = (int)dy(gen);
        int c = (int)dx(gen);

        if( r>=0 && r<mat.rows && c>=0 && c<mat.cols) {
            mat( r, c) = point_color;
            ++ret;
        }
    }
    return ret;
}


/** Puts randomly distributed noise pixels onto a matrix.
 * @param m The matrix on which to apply the noise.
 * @param probability The probability of one pixel to be set to the noise value.
 * @param The value, or color, a noise pixel shall have.
 */
template< typename T>
void noise( cv::Mat_<T> m, float probability, T color, unsigned long random_seed=1) {

    std::mt19937 gen(random_seed);
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    for( int r=0; r<m.rows; ++r) {
        for( int c=0; c<m.cols; ++c) {
            if( dis(gen) < probability)
                m(r,c) = color;
        }
    }
}


#include <Windows.h>
/** Retrieves the window dimensions of an opencv window.
 * @param winname The window's name as a c string.
 * @return A pair of that stores first the window's height and second the window's width in pixels.
 *         Returns undefined values in case the window with the given name could not be handled.
 */
std::pair<unsigned int, unsigned int> window_dimensions( const char* winname) {
    std::pair<unsigned int /*height*/, unsigned int /*width*/> ret;
    HWND hwnd = (HWND)cvGetWindowHandle( winname);
    assert( hwnd != 0 && "window handle must retrieve a valid window!");

    RECT rect;
	GetClientRect(hwnd, &rect);

    ret.first = rect.bottom - rect.top;
    ret.second = rect.right - rect.left;
    return ret;
}


#include <functional>
#include <string>
/** Loads a (one-dimensional) plain matrix from a file.
 * For more complex data formats consider cv::FileStorage.
 * @param fname The path to the file where the matrix is stored.
 * @param[out] out_mat A reference to the matrix that shall store the matrix.
 * @return TRUE in case of success.
 *         FALSE, if there occured any file i/o related error.
 */
template< typename T>
bool from_file( const std::string& fname, cv::Mat_<T>& out_mat,
                std::function< void(const std::string&, const int line) > error_invalid_mat_callback = on_invalid_mat) {
    bool ret;
    out_mat.release();
    ret = getlines_from_file(
        fname,
        [&]( string& line, uint line_nr) {
            std::vector<T> v = from_string<T,vector>( line);

            if( v.size()==0 || out_mat.rows != 0 && v.size() != out_mat.cols) {
                error_invalid_mat_callback(fname, line_nr);
                ret = false;
            } else {
                out_mat.push_back( cv::Mat_<T>(cv::Mat_<T>(v).t())); // not gonna love the MatExpr
            }
    });
    return ret;
}
