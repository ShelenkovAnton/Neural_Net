#pragma once

#include "layer.h"
#include <memory>

namespace net
{

class DataSet;

class Net
{
public:
    explicit Net( );

    ~Net( );

    auto set_activation_function_type( const ActFunctType = ActFunctType::sigmoid ) -> void;
    auto create_layer( const size_t, const size_t = 0 ) -> void;

    auto propagate( const std::vector<nType_t>& ) -> std::vector<nType_t>;

    auto get_outputs( ) const -> std::vector<nType_t>;

    auto learn( const DataSet& ) -> void;

    auto reset( ) -> void;

    auto current_error( ) const -> nType_t;

    auto set_learning_rate( const float ) -> void;

private:
    auto set_inputs( const std::vector<nType_t>& ) -> void;
    auto create_input_layer( const size_t, const size_t ) -> Layer*;
    auto create_hidden_layer( const size_t ) -> Layer*;

    auto calculate_errors( const std::vector<nType_t>& ) -> void;

    auto back_propagation( const std::vector<nType_t>& ) -> void;

    auto calculate_last_layer_errors( const std::vector<nType_t>& ) -> void;

    auto calculate_delta_weights( ) -> void;

    auto init_weights_errors( const Layer& ) -> void;
    auto get_inputs_ptr( ) -> std::vector<nType_t*>;

    auto test( const DataSet& ) -> size_t;

private:
    ActFunctType m_act_function_type;

    float m_learning_rate{0.01f};

    std::vector<Layer*> m_layers;
    std::vector<nType_t> m_inputs;
    std::vector<nType_t> m_errors;
};

} // namespace net
