#include "activationfunction.h"

#include <QDebug>
#include <math.h>

#include <cassert>

namespace net
{

auto ActivationFunction::sigmoid( const nType_t input ) -> nType_t
{
    return ( static_cast<nType_t>( 1 ) / ( static_cast<nType_t>( 1 ) + exp( -input ) ) );
}

auto ActivationFunction::tanh( const nType_t input ) -> nType_t
{
    const auto e  = expf( input );
    const auto _e = expf( -input );
    return ( e - _e ) / ( e + _e );
}

auto ActivationFunction::softsin( const nType_t input ) -> nType_t
{
    return ( input / ( 1 + fabs( input ) ) );
}

auto ActivationFunction::relu( const nType_t input ) -> nType_t
{
    return ( input < 0 ) ? 0 : input;
}

auto ActivationFunction::sigmoid_derivate( const nType_t input ) -> nType_t
{
    auto fAct = sigmoid( input );
    return fAct * ( 1 - fAct );
}

auto ActivationFunction::tanh_derivate( const nType_t input ) -> nType_t
{
    const auto th = tanh( input );
    return ( 1 - ( th * th ) );
}

auto ActivationFunction::softsin_derivate( const nType_t input ) -> nType_t
{
    return ( 1 / powf( ( 1 + std::abs( input ) ), 2 ) );
}

auto ActivationFunction::relu_derivate( const nType_t input ) -> nType_t
{
    return ( input < 0 ) ? 0 : 1;
}

auto ActivationFunction::get_result( const ActFunctType type, nType_t input ) -> nType_t
{
    switch ( type )
    {
    case net::ActFunctType::sigmoid:
        return ActivationFunction::sigmoid( input );
    case net::ActFunctType::tanh:
        return ActivationFunction::tanh( input );
    case net::ActFunctType::softsin:
        return ActivationFunction::softsin( input );
    case net::ActFunctType::relu:
        return ActivationFunction::relu( input );
    }
}

auto ActivationFunction::get_derivate( const ActFunctType type, nType_t input ) -> nType_t
{
    switch ( type )
    {
    case net::ActFunctType::sigmoid:
        return ActivationFunction::sigmoid_derivate( input );
    case net::ActFunctType::tanh:
        return ActivationFunction::tanh_derivate( input );
    case net::ActFunctType::softsin:
        return ActivationFunction::softsin_derivate( input );
    case net::ActFunctType::relu:
        return ActivationFunction::relu_derivate( input );
    }
}

} // namespace net
