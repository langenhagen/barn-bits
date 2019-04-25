/******************************************************************************
/* @file Contains a singleton-map for storing string-string elements or
/* string-double elements. It is a convenience class for storing
/* tweakable values within your application.
/* Paired with some command line or config file parser
/* e.g. boost::program_options you can conveniently add and modify
/* values of this map from outside your program.
/*
/* @author: barn
/* @version 141218
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers

#include <Singleton.hpp>


///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <cstdlib> // atof
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS

/** For prototyping purposes, Tweak provides concise and easy
 * way of storing a global map of variables.
 */
class Tweak : public Singleton<Tweak> {

	friend class Singleton<Tweak>;

protected: Tweak() { } // hidden constructor


public: // vars

    /// The tweaks map
    std::map< std::string, std::string> map;

public: // operators

    /** Short hand method for Tweak.get().
     * Uses atof() internally.
     * @param The string parameter to be passed to the internal map.
     * If the parameter is not within the map it will throw an out_of_range exception.
     * @return Returns the double-converted value stored in the internal map.
     * @throw std::out_of_range Throws this exception, if the given key parameter
     * is not found in the internally stored map.
     */
    inline double operator[]( const std::string& key) {
        return get(key);
    }

public: // static functions


    /** Loads elements from a file and stores them into tweak.
     * Loads line-wise key/value pairs in the form: <key> = <value>
     * Uses boost::program_options under the hood.
     * Does not reset or eliminate old entries, but they may be overwritten.
     * @param filename The name/path of the file from which the variables are to be parsed.
     * @return TRUE in case of success, otherwise returns FALSE.
     */
    static bool from_file( const std::string& filename) {
        using namespace std;
        bool ret(true);
        Tweak& tweak = Tweak::instance_ref();


        std::ifstream in_stream( filename);
        if( !in_stream.is_open()) {
            std::cerr << "Error in " << __FILE__ << "::" << __LINE__ << ": Opening file \"" << filename << "\" failed.\n";
            ret = false;
        }

        string line;
        while( getline(in_stream, line)) {
            size_t delim_idx = line.find("=");
            size_t trim_l = line.find_first_not_of(" \t\n");
            size_t last_char;

            if( delim_idx == string::npos || line.at( trim_l) == '#')
                // consider empty lines or lines without '=' invalid, but continue gracefully
                // consider lines beginning with a '#' comments
                continue;

            // extract trimmed keys / values
            string key = line.substr(trim_l, delim_idx-trim_l);
            last_char = key.find_last_not_of(" \t\n")+1;
            key.erase( last_char, key.size()-last_char );

            string value = line.substr( delim_idx+1);
            value.erase( 0, value.find_first_not_of(" \t\n"));
            last_char = value.find_last_not_of(" \t\n")+1;
            value.erase( last_char, value.size()-last_char);

            tweak.map[key] = value;
        }

        if(in_stream.bad()) {
            std::cerr << "Error in " << __FILE__ << "::" << __LINE__ << ": Reading file \"" << filename << "\" failed.\n";
            ret = false;
        }
        in_stream.close();

        return ret;
    }

public: // methods

    /** Retrieves an element as a double value.
     * Uses atof() internally.
     * The key must be available, otherwise an exception is thrown.
     * Also, the value, stored internally as a string, must be float-convertible.
     * @param The string parameter to be passed to the internal map.
     * If the parameter is not within the map it will throw an out_of_range exception.
     * @return Returns the double-converted value stored in the internal map.
     * @throw std::out_of_range Throws this exception, if the given key parameter
     * is not found in the internally stored map.
     */
    double get( const std::string& key) {
        double ret(0);

        try {
            ret = atof( map.at(key).c_str());

        } catch( std::out_of_range& e) {
            std::cerr << "Exception in " << __FILE__ << "::" << __LINE__ << ": \"" << key.c_str() << "\" not in map.\n";
            throw( e);
        }
        return ret;
    }


    /** Retrieves an element as a string value.
     * The key must be available, otherwise an exception is thrown.
     * @param The string parameter to be passed to the internal map.
     * If the parameter is not within the map it will throw an out_of_range exception.
     * @return Returns the string to the value stored in the internal map.
     * @throw std::out_of_range Throws this exception, if the given key parameter
     * is not found in the internally stored map.
     */
    std::string get_str( const std::string& key) {
        std::string ret;

        try {
            ret = map.at(key);
        } catch( std::out_of_range& e) {
            std::cerr << "Exception in " << __FILE__ << "::" << __LINE__ << ": \"" << key.c_str() << "\" not in map.\n";
            throw( e);
        }
        return ret;
    }

};
