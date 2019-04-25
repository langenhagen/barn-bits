/******************************************************************************
/* @file F-score and precision/recall tests.
/*
/*
/* @author langenhagen
/* @version 1500615
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS

/// Namespace for the f_score module.
namespace f_score {

    typedef unsigned int uint; ///< unsigned int.
    typedef float real;        ///< float.

    /** @brief Calculates the precision.
     * @param true_positives The true positives.
     * @param false_positives The false positives.
     * @return The precision value el. [0..1].
     */
    inline real precision( const uint true_positives, const uint false_positives) {
        return static_cast<real>(true_positives) / static_cast<real>(true_positives + false_positives);
    }

    /** @brief Calculates the recall.
     * @param true_positives The true positives.
     * @param false_negatives The false negatives.
     * @return The recall value el. [0..1].
     */
    inline real recall( const uint true_positives, const uint false_negatives) {
        return static_cast<real>(true_positives) / static_cast<real>(true_positives + false_negatives);
    }

    /** @brief the f_beta measure.
     * @param true_positives The true positives.
     * @param false_positives The false positives.
     * @param false_negatives The false negatives.
     * @param beta The beta.
     * @return The f-score.
     */
    inline real f_score( const uint true_positives,
                         const uint false_positives,
                         const uint false_negatives,
                         const real beta = static_cast<real>(1.0)) {

        register const real beta_sq = beta*beta;
        return (1+beta_sq) * true_positives / ( (1+beta_sq)*true_positives + beta_sq*false_negatives + false_positives );
    }


} // END namespace f_score
