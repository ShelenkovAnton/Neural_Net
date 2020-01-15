#pragma once

#include "Net/activationfunction.h"
#include <stdint.h>

namespace net
{

class DataSet
{
public:
    explicit DataSet( );

    virtual ~DataSet( ) = default;

    virtual auto get_learning_data( const size_t ) const -> std::pair<std::vector<nType_t>, size_t> = 0;
    virtual auto get_testing_data( const size_t ) const -> std::pair<std::vector<nType_t>, size_t>  = 0;

    virtual auto get_learning_count( ) const -> size_t = 0;
    virtual auto get_testing_count( ) const -> size_t  = 0;

protected:
    virtual auto check_data_set( ) const -> bool = 0;
    virtual auto load( ) -> bool                 = 0;

protected:
    std::vector<nType_t> m_trainig_images;
    std::vector<size_t> m_trainig_labels;

    std::vector<nType_t> m_testing_images;
    std::vector<size_t> m_testing_labels;
};

} // namespace net
