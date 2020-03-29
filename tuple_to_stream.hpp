/******************************************************************************
/* @file Contains a tool to write an arbitrary std::tuple to an ostream.
/*       Which, of course, depends on the tuple members to be supported
/*       by an ostream operator
/*
/* - based on gen_seqs.
/* - implementation found here: http://ideone.com/Rihfre
/*
/*
/* @author langenhagen
/* @version 160205
/*****************************************************************************/
#pragma once

#include <ostream>
#include <tuple>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS, TYPE DECLARATIONS/IMPLEMENTATIONS and FUNCTIONS


namespace tuple_to_stream {

    /// Implementation details, clients never use these directly.
    namespace detail {

        /// Implementation details, clients never use these directly.
        template<std::size_t...> struct seq {};

        template<std::size_t N, std::size_t... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

        template<std::size_t... Is>
        struct gen_seq<0, Is...> : seq<Is...> {};

        template<class Ch, class Tr, class Tuple, std::size_t... Is>
        std::basic_ostream<Ch, Tr>& to_stream(std::basic_ostream<Ch, Tr>& os, Tuple const& t, seq<Is...>) {
            using swallow = int[];
            (void)swallow {
                0, (void(os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...
            };
            return os;
        }

    } // END namespace detail


    /// Writes the given tuple to the given stream.
    template<class Ch, class Tr, class... Args>
    inline std::basic_ostream<Ch, Tr>& to_stream(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
        os << "( ";
        detail::to_stream(os, t, detail::gen_seq<sizeof...(Args)>());
        return os << " )";
    }

    /// Ostream function for arbitrary tuples.
    template<class Ch, class Tr, class... Args>
    inline std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
        return to_stream(os, t);
    }

} // END namespace tuple_to_stream
