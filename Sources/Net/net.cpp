#include "net.h"
#include "DataSet/mnistset.h"

#include <QDebug>
#include <cmath>

#include <cassert>

#include <iostream>
#include <math.h>

namespace net
{

Net::Net( )
{
    set_activation_function_type( ActFunctType::sigmoid );
}

Net::~Net( )
{
    for ( auto& layer : m_layers )
    {
        delete layer;
    }
}

auto Net::set_activation_function_type( const ActFunctType type ) -> void
{
    m_act_function_type = type;
    std::for_each( m_layers.begin( ), m_layers.end( ), [&]( const auto& layer ) { layer->set_activation_function( type ); } );
}

auto Net::create_layer( const size_t neuron_count, const size_t inputs_count ) -> void
{
    if ( m_layers.empty( ) )
    {
        if ( inputs_count == 0 )
        {
            throw std::runtime_error( "Input layer requires you to specify the number of inputs." );
        }
        m_layers.push_back( create_input_layer( neuron_count, inputs_count ) );
    }
    else
    {
        m_layers.push_back( create_hidden_layer( neuron_count ) );
    }
}

auto Net::set_inputs( const std::vector<nType_t>& inputs ) -> void
{
    m_inputs = inputs;
}

auto Net::set_learning_rate( const float learning_rate ) -> void
{
    m_learning_rate = learning_rate;
}

auto Net::create_input_layer( const size_t neuron_count, const size_t inputs_count ) -> Layer*
{
    std::vector<nType_t*> ptr_inputs{inputs_count};
    m_inputs.resize( inputs_count );

    std::transform( m_inputs.begin( ), m_inputs.end( ), ptr_inputs.begin( ), []( auto& input ) { return &input; } );

    const auto layer = new Layer{neuron_count, ptr_inputs, m_act_function_type, &m_learning_rate};
    return layer;
}

auto Net::create_hidden_layer( const size_t neuron_count ) -> Layer*
{
    const auto ptr_inputs = m_layers.back( )->get_ptr_outputs( );
    const auto layer      = new Layer{neuron_count, ptr_inputs, m_act_function_type, &m_learning_rate};

    init_weights_errors( *layer );

    return layer;
}

auto Net::init_weights_errors( const Layer& layer ) -> void
{
    const auto prev_layer_n_count = m_layers.back( )->neuron_count( );
    const auto weights_error_ptr  = layer.get_weights_error_ptr( prev_layer_n_count );

    m_layers.back( )->set_weights_error_ptr( weights_error_ptr );
}

auto Net::propagate( const std::vector<nType_t>& inputs ) -> std::vector<nType_t>
{
    set_inputs( inputs );

    std::for_each( m_layers.begin( ), m_layers.end( ), [&]( const auto& layer ) { layer->propagate( ); } );

    return get_outputs( );
}

auto Net::get_outputs( ) const -> std::vector<nType_t>
{
    const auto ptr_outputs = m_layers.back( )->get_ptr_outputs( );
    std::vector<nType_t> outputs( ptr_outputs.size( ) );

    std::transform( ptr_outputs.begin( ), ptr_outputs.end( ), outputs.begin( ), []( auto& output ) { return *output; } );

    return outputs;
}

auto Net::learn( const DataSet& data_set ) -> void
{
    auto expected = []( const auto& index ) {
        std::vector<nType_t> vec( 10, 0.f );
        vec[index] = 1.f;
        return vec;
    };

    m_errors.resize( m_layers.back( )->neuron_count( ) );

    // const auto data_set_size = data_set.get_learning_count( );
    const auto data_set_size = 100;

    for ( size_t i = 0; i < data_set_size; ++i )
    {
        const auto learning_data = data_set.get_learning_data( i );
        propagate( learning_data.first );
        back_propagation( expected( learning_data.second ) );

        const auto percent = data_set_size / 100;

        if ( i % percent == 0 )
        {
            qDebug( ) << i / percent << "%";
            qDebug( ) << current_error( );
        }
        if ( i % ( percent * 10 ) == 0 )
        {
            test( data_set );
        }
    }

    qDebug( ) << "************************ learning ended *******************************************";
}

auto Net::test( const DataSet& data_set ) -> size_t
{
    size_t test{0};

    for ( size_t i = 0; i < 10000; ++i )
    {
        const auto data = data_set.get_testing_data( i );

        const auto out = propagate( data.first );

        const auto out_index = std::distance( out.begin( ), std::max_element( out.begin( ), out.end( ) ) );

        if ( static_cast<size_t>( out_index ) != data.second )
        {
            test++;
        }
    }

    qDebug( ) << "error is = " << test / 100 << "%";
    return test;
}

auto Net::back_propagation( const std::vector<nType_t>& expected ) -> void
{
    calculate_errors( expected );
    calculate_delta_weights( );
}

auto Net::calculate_delta_weights( ) -> void
{
    std::for_each( m_layers.begin( ), m_layers.end( ), [&]( const auto& layer ) { layer->compute_delta_weights( ); } );
}

auto Net::calculate_last_layer_errors( const std::vector<nType_t>& expected ) -> void
{
    const auto last_layer             = m_layers.back( );
    const auto last_layer_ptr_outputs = last_layer->get_ptr_outputs( );

    const auto neuron_count = last_layer->neuron_count( );

    for ( size_t i = 0; i < neuron_count; ++i )
    {
        m_errors[i] = *( last_layer_ptr_outputs[i] ) - expected[i];
    }

    last_layer->set_neurons_errors( m_errors );
    last_layer->calculate_weights_errors_product( );
}

auto Net::calculate_errors( const std::vector<nType_t>& expected ) -> void
{
    calculate_last_layer_errors( expected );

    std::for_each( std::next( m_layers.rbegin( ) ), m_layers.rend( ), [&]( const auto& layer ) {
        layer->calculate_errors( );
        if ( layer != m_layers.front( ) )
        {
            layer->calculate_weights_errors_product( );
        }
    } );
}

auto Net::get_inputs_ptr( ) -> std::vector<nType_t*>
{
    std::vector<nType_t*> out( m_inputs.size( ) );
    std::transform( m_inputs.begin( ), m_inputs.end( ), out.begin( ), []( auto& input ) { return &input; } );
    return out;
}

auto Net::current_error( ) const -> nType_t
{
    return std::sqrt( std::inner_product( m_errors.begin( ), m_errors.end( ), m_errors.begin( ), static_cast<nType_t>( 0 ) ) ) / static_cast<nType_t>( 2 );
}

auto Net::reset( ) -> void
{
    // TODO: need impl

    // generate new weights
}

} // namespace net
