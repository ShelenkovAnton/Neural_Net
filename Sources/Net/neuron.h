#pragma once

#include "activationfunction.h"

#include <vector>

namespace net
{

class Neuron
{
public:
    explicit Neuron( const uint64_t, float* const, ActFunctType );

    auto get_ptr_output( ) -> nType_t*;

    auto propagate( const std::vector<nType_t*>& ) -> void;

    auto set_act_func_type( const ActFunctType ) -> void;

    auto set_error( nType_t ) -> void;

    auto calculate_errors( ) -> void;

    auto get_ptr_weight_errors( const uint64_t ) -> std::vector<nType_t*>;

    auto set_weights_error_ptr( const std::vector<nType_t*>& ) -> void;

    auto calculate_weights_error_product( ) -> void;

    auto compute_delta_weights( const std::vector<nType_t*>& ) -> void;

private:
    static auto weight_generator( ) -> nType_t;

    auto init_weights( const size_t ) -> void;
    auto init_weights_errors( const size_t ) -> void;

private:
    ActFunctType m_act_function_type;

    std::vector<nType_t> m_weights;

    float* m_learning_rate{nullptr};

    nType_t m_output{0};
    nType_t m_error{0};

    std::vector<nType_t> m_weights_errors;
    std::vector<nType_t*> m_weights_errors_second;
};

} // namespace net
