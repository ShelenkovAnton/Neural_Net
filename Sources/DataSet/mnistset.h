#pragma once

#include "DataSet/dataset.h"
#include <QByteArray>

namespace net
{

class string;

class MnistSet final : public DataSet
{
public:
    explicit MnistSet( );

    auto check_data_set( ) const -> bool override;

    auto load( ) -> bool override;

    auto get_learning_count( ) const -> size_t override;
    auto get_testing_count( ) const -> size_t override;

    auto get_learning_data( const size_t ) const -> std::pair<std::vector<nType_t>, size_t> override;
    auto get_testing_data( const size_t ) const -> std::pair<std::vector<nType_t>, size_t> override;

private:
    auto read_mnist_labels( const std::string& ) const -> std::vector<size_t>;
    auto read_mnist_images( const std::string& ) const -> std::vector<nType_t>;

    auto reverse_int( int ) const -> int;
    auto byts_to_int( const QByteArray& _byteArray ) const -> int32_t;

    auto load_training_labels( const std::string& ) -> void;
    auto load_trainig_images( const std::string& ) -> void;
    auto load_testing_labels( const std::string& ) -> void;
    auto load_testing_images( const std::string& ) -> void;
};

} // namespace net
