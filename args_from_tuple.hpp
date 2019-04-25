/******************************************************************************
/* @file Contains a tool for calling arbitrary functions with parameters
/*       passed as tuples.
/*
/* It is built on a solution found here:
/* http://stackoverflow.com/questions/10766112/c11-i-can-go-from-multiple-args-to-tuple-but-can-i-go-from-tuple-to-multiple
/* http://en.cppreference.com/w/cpp/utility/integer_sequence
/*
/* Example usage:
###################################################################################################

void foo(int, float, string);
int bar(int, float, string);
int baz();

// ...

using tuple_type = tuple<int, float, string>;

tuple_type args = make_tuple( 42, 12.5, "hellow");      // parameter pack for later usage


args_from_tuple::call(foo, args);                       // calls foo( 42, 12.5, "hellow");
// auto v1 = args_from_tuple::call(foo, args);          // won't compile
auto v2 = args_from_tuple::call(bar, args);             // equals v2 = bar( 42, 12.5, "hellow");
auto v3 = args_from_tuple::call(baz, tuple<>());        // equals v3 = baz();

###################################################################################################
/*
/*
/* @author langenhagen
/* @version 160203
/*****************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS, TYPE DECLARATIONS/IMPLEMENTATIONS and FUNCTIONS


namespace args_from_tuple {

    /// Implementation details, clients never use these directly.
    namespace detail {

        /// Recursive implementation of the call structure.
        template <typename F, typename Tuple, bool Done, int Total, int... N>
        struct call_impl {

            /// Recursively calls the recursive call_impl::call function until The the last tuple element was unpacked.
            constexpr static auto call(F f, Tuple&& t) {
                return call_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, std::forward<Tuple>(t));
            }
        };

        /// Final recursive implementation of the call structure.
        template <typename F, typename Tuple, int Total, int... N>
        struct call_impl<F, Tuple, true, Total, N...> {

            /// Final recursive call to the actual function with all arguments unpacked.
            constexpr static auto call(F f, Tuple&& t) {
                return f( std::get<N>(std::forward<Tuple>(t))...);
            }
        };
    } // END namespace detail


    /** Calls the given function f with the parameters found in the given tuple and,
    if f returns a value, also returns this value.
    @param f A function.
    @param t A tuple containing the parameters for the invocation of f.
             If f takes no arguments, pass std::tuple<>().
    @return Returns the return value of f.
            If f's result type would be void, the return type
            of this function would also be void.
    */
    template <typename F, typename Tuple>
    constexpr auto call(F f, Tuple&& t) {
        using ttype = std::decay<Tuple>::type;
        return detail::call_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, std::forward<Tuple>(t));
    }

} // END namespace args_from_tuple
