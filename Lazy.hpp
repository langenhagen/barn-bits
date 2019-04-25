/**
 * This file provides a thread-safe generic class for lazy evaluated values.
 *
 * It was adapted from the source code found at
 * http://www.codeproject.com/Articles/682455/Generic-Lazy-Evaluation-in-Cplusplus
 *
 * Use like:  _length = Lazy<float>([this]() { return sqrtf(_x * _x + _y * _y); });
 *
 *
 * TODO test
 *
 * @author barn
 * @version 20131121
 */
#pragma once


///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <mutex>


///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS


/// A thread safe template class for lazy initialisation.
template<typename T>
class Lazy
{
private: // vars

    /// The initialisation function.
    std::function<T()> _initiator;

    /// The pre-computed, lazy evaluated value.
    T _value;

    /// Specifies, if the _value is initialized.
    bool _initialized;

    /// Mutex for thread safety.
    std::mutex _mutex;

public: // constructor & destructor

    /// Main constructor. Do not use this one.
    Lazy()
        :
        _initiator(defaultInitiator),
        _initialized(false)
    {}

    /** Constructor
    @param initiator The function that will be used for initialisation of the value.
    */
    Lazy( std::function<T()> initiator)
        :
        _initiator(initiator),
        _initialized(false)
    {}

public: // methods

    /** Retrieves the lazy evaluated value.
    @return The value.
    */
    T& getValue()
    {
        if (!_initialized)
        {
            _mutex.lock();
            if (!_initialized)
            {
                _value = _initiator();
                _initialized = true;
            }
            _mutex.unlock();
        }
        return _value;
    }

    /** Shortcut for getValue(void).
    @return The value.
    @see getValue(void)
    */
    operator T()
    {
        return getValue();
    }

    /** Shortcut for getValue(void).
    @return The value.
    @see getValue(void)
    */
    T& operator* ()
    {
        return getValue();
    }

    /** Copy Assign. Does not evaluate the value.
    @param other The other lazy evaluation object of same type.
    */
    lazy<T>& operator=(const lazy<T>& other)
    {
        _mutex.lock();
        _initiator   = other._initiator;
        _initialized = false;
        _mutex.unlock();
        return *this;
    }

private: // helpers

    /// Throws an exception.
    static T default_initiator()
    {
        throw std::runtime_error("No lazy evaluator given.");
    }
};
