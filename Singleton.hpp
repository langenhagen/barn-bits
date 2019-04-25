/******************************************************************************
/* This file contains a singleton implementation from which you can derive.
/* inspired by: http://de.wikibooks.org/wiki/C++-Programmierung:_Entwurfsmuster:_Singleton
/*
/* EXAMPLE USAGE
/* *** Derive as follows: *** =======================================


class MySingleton : public Singleton<MySingleton> {

	friend class Singleton<MySingleton>;

protected: MySingleton() { } // hidden constructor


public:
	int value;
	void doFoo() { ... }
};


/*  *** End of example *** ==========================================
/*
/*
/* @author: barn
/* @version: 141218
/*
/******************************************************************************/
#pragma once


///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS

/// A singleton class from which one can derive.
template <typename T>
class Singleton {

private: static T* __instance; /// static singleton instance

protected: Singleton() { } /// hidden constructor

private: // private aka disabled constructors

	Singleton(const Singleton<T> &);
	Singleton& operator=(const Singleton<T> &);

public:

	/// Destructor.
	virtual ~Singleton() {
		__instance = 0;
	}


public: // static functions

    /** Static getter function.
     @return Returns a singleton object pointer.
     */
    static T* instance() {

		if (__instance == 0) {
          __instance = new T ();
		}

		return __instance;
	}

    /** Abbreviated static getter function.
     @return Returns a singleton object pointer.
     */
    static T* i() {
        return instance();
    }

    /** Static getter function.
     @return Returns a singleton object reference.
     */
    static T& instance_ref() {

		if (__instance == 0) {
          __instance = new T ();
		}

		return *__instance;
	}

    /** Abbreviated static getter function.
     @return Returns a singleton object reference.
     */
    static T& i_ref() {
        return instance_ref();
    }
};

template <typename T> T* Singleton<T>::__instance = 0;
