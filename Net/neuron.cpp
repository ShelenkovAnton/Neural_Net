#include "neuron.h"
#include "activationfunction.h"

#include <QDebug>
#include <cassert>
#include <math.h>
#include <random>

namespace net
{

Neuron::Neuron( const uint64_t weights_count, float* const learning_rate_ptr, ActFunctType act_funct_type )
    : m_act_function_type{act_funct_type}
    , m_learning_rate{learning_rate_ptr}
{
    init_weights( weights_count );
    init_weights_errors( weights_count );
}

auto Neuron::init_weights( const uint64_t w_count ) -> void
{
    m_weights.resize( w_count );
    std::generate_n( m_weights.begin( ), w_count, &Neuron::weight_generator );
}

auto Neuron::init_weights_errors( const size_t w_count ) -> void
{
    m_weights_errors.resize( w_count );
}

auto Neuron::weight_generator( ) -> nType_t
{
    srand( time( NULL ) );
    return 1.f / static_cast<nType_t>( rand( ) % 1000 + 1.f );
}

auto Neuron::get_ptr_output( ) -> nType_t*
{
    return &m_output;
}

auto Neuron::propagate( const std::vector<nType_t*>& inputs ) -> void
{
    auto res{static_cast<nType_t>( 0 )};
    for ( size_t i = 0; i < inputs.size( ); ++i )
    {
        res += m_weights[i] * static_cast<nType_t>( *( inputs[i] ) );
    }

    m_output = ActivationFunction::get_result( m_act_function_type, res );
}

auto Neuron::set_act_func_type( const ActFunctType activation_funcion_type ) -> void
{
    m_act_function_type = activation_funcion_type;
}

auto Neuron::set_error( nType_t error ) -> void
{
    m_error = error;
}

auto Neuron::calculate_errors( ) -> void
{
    nType_t sum{0};
    for ( size_t i = 0; i < m_weights_errors_second.size( ); ++i )
    {
        sum += *( m_weights_errors_second[i] );
    }

    m_error = sum;
}

auto Neuron::calculate_weights_error_product( ) -> void
{
    std::transform( m_weights.begin( ), m_weights.end( ), m_weights_errors.begin( ), [&]( const auto& weight ) { return weight * m_error; } );
}

auto Neuron::get_ptr_weight_errors( const size_t w_count ) -> std::vector<nType_t*>
{
    std::vector<nType_t*> out( w_count );

    std::transform( m_weights_errors.begin( ), m_weights_errors.end( ), out.begin( ), []( auto& weight_error ) { return &weight_error; } );

    return out;
}

auto Neuron::set_weights_error_ptr( const std::vector<nType_t*>& weight_error ) -> void
{
    m_weights_errors_second = weight_error;
}

auto Neuron::compute_delta_weights( const std::vector<nType_t*>& prev_layer_outputs_ptr ) -> void
{
    const auto delta = m_error * ActivationFunction::get_derivate( m_act_function_type, m_output ) * *m_learning_rate;

    for ( size_t i = 0; i < prev_layer_outputs_ptr.size( ); ++i )
    {
        m_weights[i] -= delta * ( *prev_layer_outputs_ptr[i] );
    }
}

} // namespace net
