// TODO HEADER
#pragma once

// TODO includes
#include <functional>
#include <numeric>
#include <vector>


namespace BANN
{
    /** TODO
    */
    template<class InputType, class WeightType, class InputContainerType, class WeightContainerType>
    class Neuron
    {
    public: // typedefs
        using TransferFunctionType = std::function< InputType(const InputType&) >;

    public: // vars
        WeightContainerType weights;

        TransferFunctionType transfer_function;
    public: // ctors & dtor

//        Neuron( size_t n_inputs

        /** TODO
         */
        Neuron(WeightContainerType& initial_weights, TransferFunctionType transfer_function)
            : weights(initial_weights)
            , transfer_function(transfer_function)
        {}

    public: // methods

        /** TODO
         */
        InputType calc(const InputContainerType& input_values) const {
            const auto weighted_sum = weighed_sum_function(input_values, weights);
            return transfer_function(weighted_sum);
        }

    private: // methods

        /** TODO
         */
        InputType weighed_sum_function(const InputContainerType& inputs, const WeightContainerType& weights ) const {
            assert(inputs.size() == weights.size() && "weight and input vectors must have the same size");

            InputType ret = static_cast<InputType>(0);

            auto input_it = inputs.cbegin();
            auto weights_it = weights.cbegin();
            for (; input_it != input_it.end(); ++input_it) {
                ret += input_it * weights_it;
            }
            return ret;
        }

    };


} // end BANN
