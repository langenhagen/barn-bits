/******************************************************************************
* @file Contains widely usable defines and macros and
* generic utility/convenience functions.
*
* @author andreasl
* @version 18-06-08
******************************************************************************/
#pragma once


///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS


/// enhanced delete call
#define DESTROY( pointer) \
    if(pointer) { \
        delete pointer; \
        pointer=0; \
    }


/// a classical exit macro for console applications
#define CONSOLE_EXIT( return_value) \
    getch(); \
    exit(return_value);


/// EXIT macro
#define EXIT(return_value) CONSOLE_EXIT(return_value)


/// ultra short things only for private usage ;)
#ifdef HELLO

    using uint = unsigned int;
    using intvec = std::vector<int>;
    using uintvec = std::vector<unsigned int>;
    using floatvec = std::vector<float>;
    using doublevec = std::vector<double>;

    // Prevents Visual Studio compiler warning: conversion from 'type1' to 'type2', possible loss of data
    #pragma warning(disable:4244)

    // the best cout alternative you can.
    // it boils down to multiple statements, so beware of pitfals, e.g. of missing brackets in:
    //   if( some_val)
    //      $ "somestuff"
    #define $ std::cout << std::endl <<
    #define $e std::cout << std::endl;

    /// cout with preceeding endl command
    #define coutl std::cout << std::endl

    /// TAB like std::endl
    #define TAB "\t"
    #define TAB2 "\t\t"
    #define TAB3 "\t\t\t"
    #define TAB4 "\t\t\t\t"

    // shortcut for loop
    #define FORTO( a, b)        for( int i = a; i < b; ++i)

#endif


///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS, TYPE DECLARATIONS/IMPLEMENTATIONS and FUNCTIONS


#include <limits>
/** Checks if a given number is bigger than the type boundaries,
 *  e.g. if a number is infinite..
 *  With C++11 consider using std::isinf.
 * @param v The value to be checked.
 * @return TRUE, if the number is infinite,
 *        FALSE if the given value is not.
 */
template<typename T>
inline bool is_inf( const T &v ) {
    return ! ( -std::numeric_limits<T>::max() <= v &&
                std::numeric_limits<T>::max() >= v );
}


/** Checks whether a given number not a number.
 * With C++11 consider using std::isnan.
 * @param v The value to be checked.
 * @return TRUE, if the number is NaN,
 *        FALSE if the given value is not.
 */
template<typename T>
inline bool is_nan( const T &v) {
    return v != v; // yep
}


/** Checks wethers a given number is a valid number,
 * e.g. is finite and is not NaN.
 * With C++11 consider using std::isnan and std::isinf.
 * @param v The value to be checked.
 * @return TRUE if the given value is a valid number,
 *         FALSE if it is not.
 */
template<typename T>
inline bool is_valid( const T &v) {
    return ! is_inf(v) && ! is_nan(v);
}


/** Wraps the value of val into the range [0;upper_limit].
 * You could use it for e.g. wrapping degrees like 721° to a [0;360]° range.
 * @param val The value to be wrapped.
 * @param upper_limit The upper limit to which to wrap.
 * Values bigger than upper_limit will be wrapped.
 * @return The wrapped value.
 */
template< class T = double>
inline T wrap( T val, T upper_limit=360 ) {
    return abs( val - upper_limit * floor( val / upper_limit ));
}


/** Retrieves the smallest signed distance between two angles.
 * @param angle 1 An angle.
 * @param angle 2 An angle.
 * @return The smallest signed distance between the two angles.
 */
template< class T = double>
inline T angle_diff( T angle1, T angle2) {
     return wrap(angle1 - angle2 + 180) - 180;
}


#include <conio.h>
/** Convenience function for non-blocking getch().
 * @return The value that would be returned by getch()
 */
inline int nb_getch() {
    return _kbhit() ? _getch() : 0;
}


#include <fstream>
#include <string>
/** Checks, whether a file exists or not.
 * It uses an fstream to open & close a file
 * and checks the fail bit of the fstream.
 * Doesn't consider capital letters/non-capital letters.
 * Don't use it if you just want to check whether a file
 * exists to open it.
 * ! If you do more stuff with the file system consider
 * using Boost.Filesystem or if Cpp x11 is available
 * the filesystem module of the STL !
 * @param fname The filename.
 * @return
 * Returns TRUE, if the file exists,
 * returns FALSE if the file does not exist.
 */
inline bool file_exists( const std::string& fname ) {
    std::fstream file;
    file.open( fname, std::ios::in);
    file.close();
    return !file.fail();
}


#include <ostream>
/** Stream out oparator on pairs.
 * @param os An ostream.
 * @param float_pair A std::pair.
 * @return The ostream that was the first parameter.
 */
template< class T>
inline std::ostream& operator<<(std::ostream& os, const std::pair<T,T>& float_pair) {
    os << float_pair.first << ";\t" << float_pair.second;
    return os;
}


#include <sstream>
/** from_stream for stl containers.
 * Containers should implement push_back in order to work correctly.
 * @param in_stream The container in an istream form, spaces are supposed to be the delimeters.
 * @return A container consisting of the elements found in the stream.
 */
template< typename F, template<class T, class = std::allocator<T> > class container_type >
container_type<F> from_stream( std::istream& in_stream ) {
    container_type<F> ret;
    std::copy( std::istream_iterator<F>(in_stream),
               std::istream_iterator<F>(),
               std::back_inserter(ret));
    if( in_stream.fail() && !in_stream.eof())
        std::cerr << "Error: " << __FILE__ << "::from_stream(): could not parse read stream until end.";
    return ret;
}


#include <string>
#include <sstream>
/** Puts all numbers in a given string into an stl container.
 * The container type must be able to perform push_back().
 * @param str The string that is to be converted into a container.
 * @return An stl container of a given numerical type.
 */
template< typename F, template<class T, class = std::allocator<T> > class container_type >
inline container_type<F> from_string( const std::string& str) {
    return from_stream<F, container_type>( std::istringstream(str));
}


#include <algorithm>
#include <iterator>
#include <ostream>
/** Stream out operator on stl compliant containers such as lists and vectors.
* @param os An ostream.
* @param container An stl compliant container.
* @return The ostream that was the first parameter.
*/
template< typename F, template<class T, class = std::allocator<T> > class container_type >
std::ostream& operator<<(std::ostream& os, const container_type<F>& container) {
    copy(container.begin(), std::prev(container.end()), std::ostream_iterator<F>(os, ", "));
    os << container.back();
    return os;
}


#include <string>
/** Trims a string from and only from white spaces, tabs and newlines.
 * @param str Reference to the string that is to be trimmed.
 * @return Returns the given (trimmed) string.
 */
inline std::string& trim( std::string& str) {
    size_t last_char;
    str.erase(0,str.find_first_not_of(" \t\n"));
    last_char = str.find_last_not_of(" \t\n")+1;
    str.erase(last_char, str.size()-last_char);
    return str;
}


#include <iterator>
#include <sstream>
#include <string>
/** to-string for stl containers like vectors and sets.
 * The elements of the container must be consumable by a stream.
 * @param The container to be converted to a string.
 * @param The delimeter of the list elements.
 * @return A string consisting of the elements of the container.
 */
template< class container_type >
std::string to_string( const container_type& container, const std::string& delimeter = "; ") {
    auto it = container.begin();
    if( it == container.end() )
        return "";

    std::stringstream ss;
    for(; std::next(it) != container.end(); ++it)
        ss << *it << delimeter;
    ss << *it;
    return ss.str();
}


#include <algorithm>
#include <string>
/** Converts all capital letters in a to lower case.
 * @param s The input string.
 * @return The transformed input string for the sake of inline usage.
 */
inline std::string& to_lower( std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}


#include <algorithm>
#include <string>
/** Copies the given string in a new lower case string.
 * @param s The input string.
 * @return The transformed input string for the sake of inline usage.
 */
inline std::string to_lower( const std::string& s) {
    std::string ret = s;
    return to_lower( ret);
}


#include <sstream>
/** Converts an integer value into a string.
 * !!! better use stdlib.h itoa(int value, char* str, int base) if available !!!
 * @param an arbitrary integer value.
 * @return The specified integer value as a string.
 */
inline std::string itos( int i) {
        std::stringstream s;
        s << i;
        return s.str();
}


/** Returns the next bigger number that is a power of two.
 * @param num The input number
 * @return A number greater or equal to the input number that is a power of two.
 */
uint next_pow_two( uint num) {

    uint ret = num > 0 ? num - 1 : 0;
    ret |= ret >> 1;
    ret |= ret >> 2;
    ret |= ret >> 4;
    ret |= ret >> 8;
    ret |= ret >> 16;

    return ++ret;
}


/** Fills an given array with the digits of a given number.
 * TODO: not tested yet!!
 * @param out_array The array to be filled.
 * Must at least have digit_count slots.
 * The highest digit will be stored into the first slot and so on.
 * E.g. the number 1236 will be stored in the following way:
 * out_array[0] = 1
 * out_array[1] = 2
 * out_array[2] = 3
 * out_array[3] = 6
 * @param i The number to be decomposed.
 * @param digit_count The number of digits in i.
 * Usually something like floor(log10(i)+1) or less.
 */
template<typename T>
void get_digits(int* out_array, T i, int digit_count) {
    do {
        int digit = i % 10;
        i /= 10;
        out_array[--digit_count] = digit;
    } while (i > 0);
}


/** Returns the nearest power of two to the given number.
 * @param num the number.
 * @return The next nearest power of two.
 * In this implementation, when num=0, the return value will be 0,
 * if num is already power of two, the next bigger power of 2 will be
 * returned.
 */
uint next_pow_two_fast(uint num) {
    uint j, k;
    (j = num & 0xFFFF0000) || (j = num);
    (k = j   & 0xFF00FF00) || (k = j);
    (j = k   & 0xF0F0F0F0) || (j = k);
    (k = j   & 0xCCCCCCCC) || (k = j);
    (j = k   & 0xAAAAAAAA) || (j = k);
    return j << 1;
}


#include <algorithm> // all_of
#include <string>
/** Checks if all characters of the given string are digits.
 * @param str A string
 * @return Returns TRUE, if all characters in str are digits
 *                 FALSE, if any character is no digit.
 */
inline bool is_digits(const std::string &str) {
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}


#include <string>
#include <conio.h>
/**
 * Captures the input until ENTER is pressed or the maximum string buffer size (1024)
 * is reached. DEL deletes the last character.
 * @return The string that is captured until ENTER is pressed
 * or the maximum string buffer size is reached.
 */
std::string read_line() {
    const unsigned int max_buffer_length = 1024;
    char ret[max_buffer_length]("\0");
    unsigned int cursor(0);

    // non-blocking getch
    int kbval ( _kbhit() ? _getch() : 0);

    while( 13!=kbval ) {
        // until ENTER is pressed

        if(0==kbval) {
            // NOTHING
        } else if( 8==kbval && cursor > 0) {
            // DEL
            ret[--cursor] = '\0';
        } else if(cursor < max_buffer_length) {
            // ORDINARY CHARACTERS
            ret[cursor++] = unsigned char(kbval);
        }
        kbval = _kbhit() ? _getch() : 0;
    }
    return std::string(ret);
}


#include <iostream>
#include <string>
/** Open file error callback function originally for getlines_from_file().
 * @param fname The filename.
 * @see getlines_from_file()
 * @see to_file()
 */
inline void on_open_file_error( const std::string& fname) {
    std::cerr << "Error opening file \"" << fname << "\".\n";
}


#include <iostream>
#include <string>
/** Read line error callback function originally for getlines_from_file().
 * @param fname The filename.
 * @see getlines_from_file()
 */
inline void on_read_file_error( const std::string& fname) {
    std::cerr << "Error while reading file \"" << fname << "\".\n";
}


#include <iostream>
#include <string>
/** Read line error callback function originally for getlines_from_file().
 * @param fname The filename.
 * @param line The line number (0-based indexing) [sic].
 * @see getlines_from_file()
 */
inline void on_read_file_line_error( const std::string& fname, unsigned int line) {
    std::cerr << "Error while reading file \"" << fname << "\" at line " << line+1 << " (1-based indexing).";
}


#include <iostream>
#include <string>
/** Write error callback function originally for to_file().
 * @param fname The filename.
 * @see to_file()
 */
inline void on_write_file_error(const std::string& fname) {
    std::cerr << "Error writing to file \"" << fname << "\".\n";
}


#include <fstream>
#include <functional>
#include <string>
/** Convenience function that reads and processes every line in a file.
 * It opens the file, reads, and processes every line via a specified callback and then closes the file.
 * It does proper opening and error handling with help of the specified callback functions for the two error cases.
 * @param filename The path of the file to be read.
 * @param callback The function that is to be called for every line.
 *        It takes a string as an argument which will be set to the line read.
 * @param error_open_callback The function that is to be called when the file could not be openend.
 *        It takes a string as an argument which will be set to the original given filename.
 * @param error_read_callback The function that is called when there occured an error while reading the file.
 *        It takes a string as an argument which will be set to the original given filename.
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
bool getlines_from_file( const std::string& filename,
                std::function< void(std::string&) > callback,
                std::function< void(const std::string&) > error_open_callback = on_open_file_error,
                std::function< void(const std::string&) > error_read_callback = on_read_file_error) {
    bool ret(true);
    std::ifstream in_stream( filename);
    if( !in_stream.is_open()) {
        error_open_callback( filename);
        ret = false;
    }
    std::string line;
    while( getline(in_stream, line))
        callback(line);
    if(in_stream.bad()) {
        error_read_callback(filename);
        ret = false;
    }
    in_stream.close();
    return ret;
}


#include <fstream>
#include <functional>
#include <string>
/** Convenience function that writes the contents of a container to a specified file.
 * Truncates all old entries in that given file.
 * Also does error handling via callbacks.
 * @param filename The name of the file to be written to.
 * @param container The stl-compliant container to be written to file.
 * @param delimeter The delimeter between each entry in the container.
 * @param error_open_callback The function that is called when opening the file fails.
 *        It takes a string (the filename) as an argument.
 * @param error_write_callback The function that is called when writing to the file fails.
 *        It takes a string (the filename) as an argument.
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
template< typename F, template<class T, class = std::allocator<T> > class container_type > /* for vectors and stuff */
bool to_file( const std::string& filename,
              const container_type<F>& container,
              const std::string& delimeter = "\n",
              std::function< void(const std::string&) > error_open_callback = on_open_file_error,
              std::function< void(const std::string&) > error_write_callback = on_write_file_error) {
    bool ret(true);
    std::ofstream fstream( filename, std::ios::out | std::ios::trunc);
    if(!fstream.is_open() || fstream.bad()) {
        error_open_callback(filename);
        ret = false;
    } else {
        for( auto it=container.begin(); it!=container.end(); ++it) {
            fstream << *it;
            if( std::next(it) != container.end())
                    fstream << delimeter;

            if( fstream.bad()) {
                error_write_callback(filename);
                ret = false;
                break;
            }
        }
    }
    return ret;
}


#include <fstream>
#include <functional>
#include <string>
/** Convenience function that writes the contents of a container to a specified file.
 * Truncates all old entries in that given file.
 * Also does error handling via callbacks.
 * @param filename The name of the file to be written to.
 * @param container The stl-compliant container to be written to file.
 * @param delimeter The delimeter between each entry in the container.
 * @param error_open_callback The function that is called when opening the file fails.
 *        It takes a string (the filename) as an argument.
 * @param error_write_callback The function that is called when writing to the file fails.
 *        It takes a string (the filename) as an argument.
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
template< typename F, template<class T, class = std::less<T>, class = std::allocator<T> > class container_type > /* for sets and stuff */
bool to_file( const std::string& filename,
              const container_type<F>& container,
              const std::string& delimeter = "\n",
              std::function< void(const std::string&) > error_open_callback = on_open_file_error,
              std::function< void(const std::string&) > error_write_callback = on_write_file_error) {
    bool ret(true);
    std::ofstream fstream( filename, std::ios::out | std::ios::trunc);
    if(!fstream.is_open() || fstream.bad()) {
        error_open_callback(filename);
        ret = false;
    } else {
        for( auto it=container.begin(); it!=container.end(); ++it) {
            fstream << *it;
            if( std::next(it) != container.end())
                    fstream << delimeter;

            if( fstream.bad()) {
                error_write_callback(filename);
                ret = false;
                break;
            }
        }
    }
    return ret;
}


#include <fstream>
#include <functional>
#include <string>
/** Convenience function that writes the contents of an array to a specified file.
 * Truncates all old entries in that given file.
 * Also does error handling via callbacks.
 * @param filename The name of the file to be written to.
 * @param array The array to be written to file.
 * @param array_size The number of array elements.
 * @param delimeter The delimeter between each entry in the container.
 * @param error_open_callback The function that is called when opening the file fails.
 *        It takes a string (the filename) as an argument.
 * @param error_write_callback The function that is called when writing to the file fails.
 *        It takes a string (the filename) as an argument.
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
template< typename T>
bool to_file( const std::string& filename,
              const T* array,
              const unsigned int array_size,
              const std::string& delimeter = "\n",
              std::function< void(const std::string&) > error_open_callback  = on_open_file_error,
              std::function< void(const std::string&) > error_write_callback = on_write_file_error) {
    bool ret(true);
    std::ofstream fstream( filename, std::ios::out | std::ios::trunc);
    if(!fstream.is_open() || fstream.bad()) {
        error_open_callback(filename);
        ret = false;
    } else {
        for( int i=0; i<array_size;) {
            fstream << array[i];
            if( ++i != array_size)
                fstream << delimeter;

            if( fstream.bad()) {
                error_write_callback(filename);
                ret = false;
                break;
            }
        }
    }
    return ret;
}


/** Convenience function that appends the given stl compliant container of type string
 * with the lines found in the given file. In error case it calls the given callbacks.
 * @param fname The path to the file to be read.
 * @param out_container The stl compliant container of in which the read found lines
 *        shall be written. The container must support push_back().
 * @param error_open_callback The function that is to be called when the file could not be openend.
 *        It takes a string as an argument which will be set to the original given filename.
 * @param error_read_callback The function that is called when there occured an error while reading the file.
 *        It takes a string as an argument which will be set to the original given filename.
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
template< template<class T, class = std::allocator<T> > class container_type >
inline bool from_file( const std::string& fname,
                       container_type<std::string>& out_container,
                       std::function<void(const std::string&)> error_open_callback = on_open_file_error,
                       std::function<void(const std::string&)> error_read_callback = on_read_file_error ) {

    return getlines_from_file( fname,
                               [&out_container](std::string& line) { out_container.push_back(line); },
                               error_open_callback,
                               error_read_callback );
}

#include <fstream>
#include <functional>
#include <string>
/** Convenience function that appends the given stl compliant container with the elements
 * found in the lines of the given file. In error case it calls the given callbacks.
 * @param fname The path to the file to be read.
 * @param out_container The stl compliant container of in which the read found lines
 *        shall be written. The container must support push_back().
 * @param error_open_callback The function that is to be called when the file could not be openend.
 *        It takes a string as an argument which will be set to the original given filename.
 * @param error_read_callback The function that is called when there occured an error while reading the file.
 *        It takes a string as an argument which will be set to the original given filename and an unsigned
 *        int that represents the error-provoking line in the file (0-based indexing).
 * @return TRUE in case of success,
 *         FALSE in case of error.
 */
template< typename F, template<class T, class = std::allocator<T> > class container_type > /* for sets and stuff */
inline bool from_file( const std::string& fname,
                    container_type<F>& out_container,
                    std::function<void(const std::string&)> error_open_callback = on_open_file_error,
                    std::function<void(const std::string&, unsigned int)> error_read_callback = on_read_file_line_error ) {
    bool ret(true);

    std::ifstream in_file( fname);
    if( !in_file.is_open()) {
        error_open_callback( fname);
        ret = false;
    } else {

        std::string line;
        unsigned int line_nr(0);
        while( getline(in_file, line)) {
            std::stringstream ss;
            ss << line;
            std::copy( std::istream_iterator<F>(ss),
                        std::istream_iterator<F>(),
                        std::back_inserter(out_container));
            line_nr++;
        }
        if(in_file.bad()) {
            error_read_callback(fname, line_nr);
            ret = false;
        }
    }
    in_file.close();
    return ret;
}


#ifdef BL_BOOST_FILESYSTEM

#include <iostream>
#include <boost/filesystem.hpp>
/** filesystem_error exception callback function originally for for_each_file_in_direcory_tree().
 * @see for_each_file_in_direcory_tree()
 */
void on_filesystem_exception( boost::filesystem::filesystem_error& e) {
    std::cerr << "Exception with for_each_file_in_direcory_tree(): " << e.what() << "\n";
}


#include <boost/filesystem.hpp>
/** Performs a callback for every directory entry in a directory tree.
 * Also performs exception handling. If a filesystem_exception occurs,
 * it will be caught and the iteration will be aborted.
 * @param p The root directory path in which to start the iteration.
 * @param callback The callback to perform on every directory entry.
 *        It takes a boost::filesystem::directory_entry as an argument,
 *        also an unsigned int that will provide the iteration level
 *        and returns a bool. When the return value is FALSE,
 *        the whole iteration will be aborted and the function returns false.
 * @param exception_callback The function that is called when an exception occurs.
 *        Takes a boost::filesystem::filesystem_error as an argument.
 * @param max_level The maximum level to iterate into the directory tree starting where 0 is the base level.
 *        If max_level is set to -1, the function iterates into every file-tree depth.
 * @return TRUE in case of complete success.
 *         FALSE in case of an exception of kind boost::filesystem::filesystem_error.
 */
bool for_each_file_in_direcory_tree( boost::filesystem::path& p,
                                     std::function<bool( boost::filesystem::directory_entry&, uint level)> callback,
                                     std::function<void( boost::filesystem::filesystem_error&)> exception_callback = on_filesystem_exception,
                                     int max_level = -1) {
    namespace bfs = boost::filesystem;
    bool ret(true);
    try {
        for( bfs::recursive_directory_iterator it(p); it!=bfs::recursive_directory_iterator(); ++it)
            if( max_level == -1 || it.level() <= max_level ) {
                ret = callback(*it, it.level());
                if( ret == false)
                    break;
            }
    } catch (bfs::filesystem_error& e) {
        exception_callback(e);
        ret = false;
    }
    return ret;
}

#endif //defined BL_BOOST_FILESYSTEM


#include <Windows.h>
/** Retrieves current full path of the application.
TODO: currently works on windows only. Make it multi-platform maybe.

@param append_app_name Specifies, whether the executable name
shall be on the returned string or not.
TRUE - retrieve full path with application file name.
FALSE - retrieve full path without application file name.
@return The full path of the running application.
*/
std::string app_path( bool append_app_name=false) {
    char buffer[512];
    std::string ret;

    GetModuleFileName( NULL, buffer, MAX_PATH );
    ret = std::string(buffer);

    if( !append_app_name) {
        std::string::size_type pos = ret.find_last_of( "\\/" );
        ret = ret.substr( 0, pos);
    }
    return ret;
}


/** Gives a bool into a "yes"/"no" string representation.
 * @param b A boolean value.
 * @return The string representation of the input parameter.
 * true - returns "yes"
 * false - returns "no"
 */
inline std::string yes_no( bool b) {
    return b ? "yes" : "no";
}


#include <fstream>
/** Saves a pixel array as an ppm image. Overwrites an existing image.
 * @param name the name of the file (extensions may be included).
 * @param pixels ideally, the pixel-array should be like unsigned char[3*(width)*(height)+3].
 * @param width the width of the picture to save.
 * @param width the height of the picture to save.
 * @param max_color
 * the maximum value, a color entry can have according to ppm specification.
 * the value 255 is appropriate in most cases.
 * @param adaptive_max_color
 * if set to true, scales the brightness of the picture to maximum,
 * otherwise the specified max_color value will be considered as the maximum value.
 *
 * CAUTION: THIS FUNCTION IS UNTESTED
 *
 * @return returns TRUE, if the operation was successful, returns FALSE in case of error.
 */
bool savePPM( const char* name, unsigned char *pixels, unsigned int width, unsigned int height, unsigned int max_color = 255, bool adaptive_max_color = false) {
    // style header
    std::fstream file;
    file.open(  name, std::ios::out);
    file << "P3\n" << width << " " << height << std::endl;

    // max color part
    auto max_color_cursor_pos = file.tellp();
    file << "000" << std::endl;

    if( adaptive_max_color)
        max_color = 0;

    // style pixmap
    for( int y=height-1; y>=0; y--)
        for( unsigned int x=0; x<3*width; x++) {
            unsigned int pixel_index = y*(3*width) + x;
            file << (int)pixels[pixel_index] << "\t";
            if(pixel_index % (3*width) == 0)
                file << std::endl;
            if( adaptive_max_color && (int)pixels[pixel_index] > max_color)
                max_color = (int)pixels[pixel_index];
        }

    // set max color
    file.seekp( max_color_cursor_pos, std::ios::beg );
    file << max_color;
    file.close();

    return true;
}


#include <cassert>
#include <vector>
/** Retrieves a vector of all sub-vectors with a specific length consisting elements of the given vector.
 * Elements in the subvectors do not need to be neighbours in the original vector; the subvectors are like subsets,
 * with the difference that they are vectors and the order of the elements will not be changed.
 * XXX maybe make it more efficient.
 * @param v The vector from which to retrieve subvectors.
 * @param length The length of the subvectors to retrieve.
 * @return A vector of all subvectors with the given length.
 */
template< typename T>
std::vector<std::vector<T>> subvectors( std::vector<T> v, uint length) {
    using namespace std;

    vector<vector<T>> ret;
    assert( v.size() >= length);

    vector<int> indices;
    for( int i=0; i<length; ++i) {
        indices.push_back(i);
    }

    int off;
    do {
        vector<T> ret_element;
        for( int i=0; i<length; ++i) {
            ret_element.push_back( v[indices[i]]);
        }
        ret.push_back( ret_element);

        off = 1;
        while( off <= length && indices[length-off] == v.size()-off)
            ++off;
        // *** off at the right position to raise ***

        if(off <= length) {
            int index_to_raise = length - off;
            indices[index_to_raise]++;
            for( int i=1; i<off; ++i) {
                indices[index_to_raise + i] = indices[index_to_raise] + i;
            }
        }
    } while(off <= length);

    return ret;
}


#include <cassert>
#include <vector>
/** Retrieves a vector of all given-length sub-vectors indices of a vector with given length.
 * Elements in the subvectors do not need to be neighbouring indices; the index-subvectors are like subsets,
 * with the difference that they are vectors and the order of the elements will be changed lexicographic.
 * XXX maybe make it more efficient.
 * @param vector_length The length of the vector from which to retrieve the subvectors-indices.
 * @param subvectors_length The length of the index-subvectors to retrieve.
 * @return A vector of all subvectors with the given length containing indices from 0 to vector_length-1.
 */
std::vector<std::vector<size_t>> subvector_indices( size_t vector_length, size_t subvectors_length) {
    using namespace std;
    vector<vector<size_t>> ret;
    assert( vector_length >= subvectors_length);

    vector<size_t> indices;
    for(size_t i=0; i<subvectors_length; ++i) {
        indices.push_back(i);
    }

    size_t off;
    do {
        ret.push_back( indices);

        off = 1;
        while( off <= subvectors_length && indices[subvectors_length-off] == vector_length-off)
            ++off;
        // *** off at the right position to raise ***
        if(off <= subvectors_length) {
            size_t index_to_raise = subvectors_length - off;
            indices[index_to_raise]++;
            for(size_t i=1; i<off; ++i) {
                indices[index_to_raise + i] = indices[index_to_raise] + i;
            }
        }
    } while(off <= subvectors_length);

    return ret;
}


/** Resizes a vector and linearly interpolates the vector elements when  upscaling/downscaling.
 * @param v The vector of type T that is to be resized. Type T must understand operations
 * like addition T+T and multiplication with a floating point value.
 * @param new_size The size of the new output vector.
 * @return An resized, linearly interpolated version of the given vector with the given new length.
 */
template< typename T>
std::vector<T> resize_interpolated( const std::vector<T>& v, uint new_size) {
    std::vector<T> ret;
    double factor = double(v.size()) / new_size;

    for( int i=0; i<new_size; ++i) {
        double index = i * factor;
        int integer_part = (int)index;
        double fractional_part = index - integer_part;
        if( index+1 >= v.size())
            ret.push_back( v[integer_part]);
        else
            ret.push_back( v[integer_part] * (1 - fractional_part) + v[integer_part + 1] * fractional_part);
    }
    return ret;
}

#include <assert.h>
#include <vector>
/** Retrieves the normalized circular delayed cross correlatipon series of two given vectors.
 * The function calculates means and deviations under the hood, so maybe, if you have
 * these values beforehand you should rather calculate your own correlation series inline.
 * @param a The first vector.
 * @param b The second vector. Must have the same length as vector a.
 * @return The cross correlation series for both vectors with the index defining the delay.
 * Since cross_correllation(vector, delay) = cross_correllation(vector, vector.size-delay),
 * or, in other words, the cross correlation series is symmetric to delay = vector.size()/2,
 * The resulting vector will be half the size of the input vectors.
 * The vector elements are within [-1;1].
 */
template<typename R>
std::vector<R> circular_cross_correlation_series( const std::vector<R>& a, const std::vector<R>& b) {
    assert( a.size() == b.size() && "a and b must have same length");
    std::vector<R> ret;
    unsigned int size = static_cast<unsigned int>(a.size()/2) + (a.size()%2 == 0 ? 0 : 1);
    ret.reserve( size);

    register R mean_a = 0;
    register R mean_b = 0;
    R variance_a = 0;
    R variance_b = 0;
    register R denom;

    // calculate means
    for( int i=0; i<a.size(); ++i) {
        mean_a += a[i];
        mean_b += b[i];
    }
    mean_a /= a.size();
    mean_b /= a.size();
    // calculate variances
    for( int i=0; i<a.size(); ++i) {
        variance_a += (a[i] - mean_a) * (a[i] - mean_a);
        variance_b += (b[i] - mean_b) * (b[i] - mean_b);
    }
    denom = sqrt( variance_a * variance_b);

    // calculate correlation series
    if( denom == 0) {
        for( unsigned int delay=0; delay<size; ++delay) {
            ret.push_back(1);
        }
    } else {
        for( unsigned int delay=0; delay<size; ++delay) {
            R cross_correlation = 0;
            for( int idx_a=0; idx_a<a.size(); ++idx_a) {
                int idx_b = (idx_a+delay) % a.size();
                cross_correlation += (a[idx_a] - mean_a) * (b[idx_b] - mean_b);
            }
            ret.push_back( cross_correlation / denom);
        }
    }
    return ret;
}


/** Checks whether a given value is zero or a power of two. Takes constant time.
 * @param n The number to be checked.
 * @return TRUE when n is a power of two or n==0,
 *         FALSE otherwise.
 */
template< typename N>
constexpr bool is_zero_or_power_of_2( const N n) {
    return (n & (n - 1)) == static_cast<N>(0);
}


#include <chrono>
/** Helper function that calculates the duration between a given time point in the past and now.
@param clock_start A time point that should be in the past.
@return the time duration (e.g. milliseconds) between clock_start and now().
*/
template< typename T = std::chrono::milliseconds>
inline T time_since( const std::chrono::steady_clock::time_point& clock_start) {
    return std::chrono::duration_cast< T>(std::chrono::steady_clock::now() - clock_start);
}


#include <algorithm>
#include <iterator>
#include <map>
/** Flips an associative container of A,B pairs to B,A pairs.
Solution inspired by: http://stackoverflow.com/questions/5056645/sorting-stdmap-using-value
@param src The source container.
@return A std::multimap whose keys are the values of src and whose corresponding values are the keys of src.
*/
template<typename A, typename B, template<class, class, class...> class M, class... Args>
std::multimap<B, A> flip_map(const M<A, B, Args...> &src) {
    std::multimap<B, A> ret;
    std::transform(
        src.begin(),
        src.end(),
        std::inserter(ret, ret.begin()),
        [](auto& p) { return std::make_pair(p.second, p.first); }
    );
    return ret;
}


/** Binary search on sorted, non-empty stl compliant containers with random-access iterators, like vectors.
Internally, it stores the indices as signed ints, so beware of huge containers.
XXX make it more general with comparator functors for complex types.
XXX constrain tparam index_type to only accept signed values.
@tparam F The type held by the given container.
@tparam container_type The type of the given container, complements with F.
@tparam index_type The type used for index access on the container.
        Must be integral and signed. int should do for most containers.
@param container An stl compliant container. Must be non-empty and sorted.
@param value The value to be looked for in the container.
@return The index position of the element in the container or -1 if the element could not be found.
*/
template< typename F, template<class T, class = std::allocator<T> > class container_type, typename index_type = int >
index_type binary_search(const container_type<F>& container, const F value) {

    index_type idx = static_cast<index_type>(container.size()) / 2;
    index_type stepsize = idx;

    do {
        if (container[idx] == value)
            return idx;

        stepsize /= 2;
        idx += container[idx] > value ? -stepsize : +stepsize;
    } while (stepsize > 0);

    idx += container[idx] > value ? -1 : +1;
    if (container[idx] == value)
        return idx;

    return -1;
}


/** Calculates the overlap of two given one-dimensional ranges.
For example, for the ranges (1, 3.6) and (2,4) the returned value is 1.6.
@param lower1 The lower end of the first range.
@param upper1 The upper end of the first range. Must be >= lower1.
@param lower2 The lower end of the second range.
@param upper2 The upper end of the second range. Must be >= lower2.
@return Returns the overlap between the ranges or 0 when the ranges do not overlap.
*/
template< typename T>
constexpr T range_intersection(const T lower1, const T upper1, const T lower2, const T upper2) {

    return std::max(
        static_cast<T>(0),
        std::min(upper1, upper2) - std::max(lower1, lower2)
        );
}


/** Given a sorted container of consecutive unsigned integers starting at 0,
where one integer is missing, this function finds the first missing integer, or,
if no number is missing, the next bigger integer.
XXX Review, make better.
@param container An stl compliant container. Must be non - empty and sorted.
@return The the missing number or the next bigger integer if no number is missing.
*/
template< typename F, template<class T, class = std::allocator<T> > class container_type>
size_t find_missing_number(const container_type<F>& container) {

    size_t idx = container.size() / 2;
    size_t stepsize = idx;

    if (container[0] != 0)
        return 0;

    do {
        stepsize /= 2;
        container[idx] > idx ? idx -= stepsize : idx += stepsize;
    } while (stepsize > 0);

    idx += container[idx] > idx ? 0 : +1;

    if (container[idx] == idx)
        return idx + 1;
    return idx;
}


/** Indicates whether an element in the given container fulfills the given predicate.
use e.g.:
    contains( some_int_vector, []( const int& i ) { return i == 3; } );
@param container A (an stl compliant) container that provides the methods begin(), end().
@param predicate A function of type bool(const ContainerElementType&).
@return TRUE if at least one element fulfills the given predicate,
        FALSE otherwise.
 */
template< class Object,
          template<class T, class = std::allocator<T> > class Container,
          class UnaryPredicate >
bool contains( const Container< Object >& container,
               UnaryPredicate predicate )
{
    // this step is necessary bc cpp cannot infer template types from lambdas
    std::function< bool ( const Object& ) > cast_predicate
            = static_cast<std::function< bool ( const Object& ) > >( predicate );

    return std::find_if( container.begin(), container.end(), cast_predicate )
            != container.end( );
}


#include <algorithm>
#include <string>
/** Removes duplicate consecutive whitespaces from the given string.
Does not trim the string.
*/
void remove_duplicate_whitespaces( std::string& s) {
  bool prior_char_is_whitespace(false);
  s.erase(std::remove_if( s.begin(),
                          s.end(),
                          [&prior_char_is_whitespace](const unsigned char x) {
                            if(prior_char_is_whitespace) {
                              prior_char_is_whitespace = std::isspace(x);
                              return std::isspace(x);
                            } else {
                              prior_char_is_whitespace = std::isspace(x);
                              return 0;
                            }
                            }),
                          s.end());
}


void remove_duplicate_whitespaces( std::string& s) {
  bool prior_char_is_whitespace(false);
  s.erase(std::remove_if( s.begin(),
                          s.end(),
                          [&prior_char_is_whitespace](const unsigned char x) {
                            const bool cur_char_is_whitespace = std::isspace(x);
                            if(prior_char_is_whitespace) {
                              prior_char_is_whitespace = cur_char_is_whitespace;
                              return std::isspace(x);
                            } else {
                              prior_char_is_whitespace = cur_char_is_whitespace;
                              return 0;
                            }
                            }),
                          s.end());
}