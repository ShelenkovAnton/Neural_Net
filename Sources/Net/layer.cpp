#include "layer.h"

#include <QDebug>
#include <cassert>
#include <iostream>
#include <math.h>

namespace net
{

Layer::Layer( const size_t neuron_count, const std::vector<nType_t*>& ptr_inputs, ActFunctType act_function_type, float* const learning_rate )
    : m_act_function_type{act_function_type}
{
    if ( !neuron_count )
    {
        std::cout << "Invalid neurons count." << std::endl;
        return;
    }

    generate_neurons( neuron_count, ptr_inputs.size( ), learning_rate );

    set_inputs_ptr( ptr_inputs );
}

Layer::~Layer( )
{
    for ( auto& neuron : m_neurons )
    {
        delete neuron;
    }
}

auto Layer::generate_neurons( const size_t neuron_count, const size_t w_count, float* const learning_rate ) -> void
{
    std::generate_n( std::back_inserter( m_neurons ), neuron_count, [&]( ) { return new Neuron{w_count, learning_rate, m_act_function_type}; } );
}

auto Layer::set_inputs_ptr( const std::vector<nType_t*>& inputs ) -> void
{
    m_inputs = inputs;
}

auto Layer::propagate( ) -> void
{
    std::for_each( m_neurons.begin( ), m_neurons.end( ), [&]( auto& neuron ) { neuron->propagate( m_inputs ); } );
}

auto Layer::get_ptr_outputs( ) -> std::vector<nType_t*>
{
    std::vector<nType_t*> outputs{m_neurons.size( )};
    std::transform( m_neurons.begin( ), m_neurons.end( ), outputs.begin( ), []( auto& neuron ) { return neuron->get_ptr_output( ); } );
    return outputs;
}

auto Layer::set_activation_function( const ActFunctType activation_function_type ) -> void
{
    std::for_each( m_neurons.begin( ), m_neurons.end( ), [&]( const auto& neuron ) { neuron->set_act_func_type( activation_function_type ); } );
}

auto Layer::neuron_count( ) const -> size_t
{
    return m_neurons.size( );
}

auto Layer::set_neurons_errors( std::vector<nType_t>& errors ) -> void
{
    for ( size_t i = 0; i < m_neurons.size( ); ++i )
    {
        m_neurons[i]->set_error( errors[i] );
    }
}

auto Layer::get_weights_error_ptr( const size_t prev_neurons_count ) const -> std::vector<std::vector<nType_t*>>
{
    std::vector<std::vector<nType_t*>> out( m_neurons.size( ) );
    std::transform( m_neurons.begin( ), m_neurons.end( ), out.begin( ),
                    [&]( const auto& neuron ) { return neuron->get_ptr_weight_errors( prev_neurons_count ); } );
    return out;
}

auto Layer::set_weights_error_ptr( const std::vector<std::vector<nType_t*>>& ptr_weights_error ) -> void
{
    const auto w_count = ptr_weights_error.size( );

    std::vector<nType_t*> out( w_count );

    for ( size_t n = 0; n < m_neurons.size( ); ++n )
    {
        for ( size_t w = 0; w < w_count; ++w )
        {
            out[w] = ptr_weights_error.at( w ).at( n );
        }
        m_neurons[n]->set_weights_error_ptr( out );
    }
}

auto Layer::calculate_errors( ) -> void
{
    std::for_each( m_neurons.begin( ), m_neurons.end( ), []( const auto& neuron ) { neuron->calculate_errors( ); } );
}

auto Layer::calculate_weights_errors_product( ) -> void
{
    std::for_each( m_neurons.begin( ), m_neurons.end( ), []( const auto& neuron ) { neuron->calculate_weights_error_product( ); } );
}

auto Layer::compute_delta_weights( ) -> void
{
    std::for_each( m_neurons.begin( ), m_neurons.end( ), [&]( const auto& neuron ) { neuron->compute_delta_weights( m_inputs ); } );
}

} // namespace net
