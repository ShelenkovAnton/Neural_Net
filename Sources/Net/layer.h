#pragma once

#include "neuron.h"

#include <vector>

namespace net
{

class Layer
{
public:
    explicit Layer( const size_t, const std::vector<nType_t*>&, ActFunctType, float* const );

    ~Layer( );

    auto propagate( ) -> void;

    auto get_ptr_outputs( ) -> std::vector<nType_t*>;

    auto set_inputs_ptr( const std::vector<nType_t*>& ) -> void;

    auto set_activation_function( const ActFunctType ) -> void;

    auto neuron_count( ) const -> size_t;

    auto set_neurons_errors( std::vector<nType_t>& ) -> void;

    auto calculate_errors( ) -> void;

    auto get_weights_error_ptr( const size_t ) const -> std::vector<std::vector<nType_t*>>;

    auto set_weights_error_ptr( const std::vector<std::vector<nType_t*>>& ) -> void;

    auto calculate_weights_errors_product( ) -> void;

    auto compute_delta_weights( ) -> void;

private:
    auto generate_neurons( const size_t, const size_t, float* const ) -> void;

private:
    std::vector<nType_t*> m_inputs;
    std::vector<Neuron*> m_neurons;
    ActFunctType m_act_function_type;
};
} // namespace net
