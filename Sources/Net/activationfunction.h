#pragma once

#include <functional>

namespace net
{

using nType_t    = float;
using act_func_t = std::function<nType_t( nType_t )>;

enum class ActFunctType
{
    sigmoid = 0,
    tanh    = 1,
    softsin = 2,
    relu    = 3,
};

class ActivationFunction
{
public:
    static auto get_result( const ActFunctType, nType_t ) -> nType_t;
    static auto get_derivate( const ActFunctType, nType_t ) -> nType_t;

private:
    static auto sigmoid( const nType_t ) -> nType_t;
    static auto tanh( const nType_t ) -> nType_t;
    static auto softsin( const nType_t ) -> nType_t;
    static auto relu( const nType_t ) -> nType_t;

    static auto sigmoid_derivate( const nType_t ) -> nType_t;
    static auto tanh_derivate( const nType_t ) -> nType_t;
    static auto softsin_derivate( const nType_t ) -> nType_t;
    static auto relu_derivate( const nType_t ) -> nType_t;
};

} // namespace net
