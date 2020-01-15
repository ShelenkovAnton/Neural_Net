#include "mnistset.h"

#include <QDebug>
#include <QFile>
#include <filesystem>
#include <string>

constexpr auto testing_labels_path = "/../Sources/DataSet/mnist/t10k-labels.idx1-ubyte";
constexpr auto testing_images_path = "/../Sources/DataSet/mnist/t10k-images.idx3-ubyte";

constexpr auto trainig_labels_path = "/../Sources/DataSet/mnist/train-labels.idx1-ubyte";
constexpr auto trainig_images_path = "/../Sources/DataSet/mnist/train-images.idx3-ubyte";

namespace net
{

MnistSet::MnistSet( )
{
    if ( !load( ) )
    {
        throw std::runtime_error( "Mnist set is corrupted." );
    }
}

auto MnistSet::load( ) -> bool
{
    const auto path = std::filesystem::current_path( ).string( );

    load_testing_labels( path );
    load_testing_images( path );
    load_trainig_images( path );
    load_training_labels( path );

    return check_data_set( );
}

auto MnistSet::load_training_labels( const std::string& path ) -> void
{
    m_trainig_labels = read_mnist_labels( path + trainig_labels_path );
}

auto MnistSet::load_trainig_images( const std::string& path ) -> void
{
    m_trainig_images = read_mnist_images( path + trainig_images_path );
}

auto MnistSet::load_testing_labels( const std::string& path ) -> void
{
    m_testing_labels = read_mnist_labels( path + testing_labels_path );
}

auto MnistSet::load_testing_images( const std::string& path ) -> void
{
    m_testing_images = read_mnist_images( path + testing_images_path );
}

auto MnistSet::reverse_int( int i ) const -> int
{
    unsigned char c1, c2, c3, c4;
    static_cast<void>( c1 = i & 255 ), static_cast<void>( c2 = ( i >> 8 ) & 255 ), static_cast<void>( c3 = ( i >> 16 ) & 255 ), c4 = ( i >> 24 ) & 255;
    return ( static_cast<int>( c1 ) << 24 ) + ( static_cast<int>( c2 ) << 16 ) + ( static_cast<int>( c3 ) << 8 ) + c4;
}

auto MnistSet::read_mnist_labels( const std::string& full_path ) const -> std::vector<size_t>
{
    QFile file( QString::fromStdString( full_path ) );
    QByteArray data;

    if ( file.open( QIODevice::ReadOnly ) )
    {
        data = file.readAll( );
        file.close( );
    }
    else
    {
        throw std::runtime_error( "Mnist file don't open" );
    }

    if ( byts_to_int( data.left( 4 ) ) != 2049 )
    {
        throw std::runtime_error( "Invalid magic number." );
    }

    std::vector<size_t> labels( static_cast<size_t>( byts_to_int( data.mid( 4, 4 ) ) ) );

    std::transform( std::next( data.begin( ), 8 ), data.end( ), labels.begin( ), []( const auto& d ) { return static_cast<uchar>( d ); } );

    return labels;
}

auto MnistSet::read_mnist_images( const std::string& full_path ) const -> std::vector<nType_t>
{
    QFile file( QString::fromStdString( full_path ) );
    QByteArray data;

    if ( file.open( QIODevice::ReadOnly ) )
    {
        data = file.readAll( );
        file.close( );
    }
    else
    {
        throw std::runtime_error( "Mnist set file don't open." );
    }

    if ( byts_to_int( data.left( 4 ) ) != 2051 )
    {
        throw std::runtime_error( "Invalid magic number." );
    }

    const auto dataSize    = byts_to_int( data.mid( 4, 4 ) );
    const auto imageWidth  = byts_to_int( data.mid( 8, 4 ) );
    const auto imageHeight = byts_to_int( data.mid( 12, 4 ) );
    const auto pixelCount  = dataSize * imageHeight * imageWidth;

    std::vector<nType_t> images( static_cast<size_t>( pixelCount ) );

    std::transform( std::next( data.begin( ), 16 ), std::next( data.begin( ), 16 + pixelCount ), images.begin( ),
                    []( const auto& val ) { return static_cast<uchar>( val ); } );

    return images;
}

auto MnistSet::check_data_set( ) const -> bool
{
    constexpr auto testing_images_size  = 7840000;
    constexpr auto training_images_size = 47040000;
    constexpr auto testing_labels_size  = 10000;
    constexpr auto training_labels_size = 60000;

    return ( ( m_testing_images.size( ) == testing_images_size ) && ( m_trainig_images.size( ) == training_images_size ) &&
             ( m_testing_labels.size( ) == testing_labels_size ) && ( m_trainig_labels.size( ) == training_labels_size ) );
}

auto MnistSet::get_learning_count( ) const -> size_t
{
    return m_trainig_labels.size( );
}

auto MnistSet::get_testing_count( ) const -> size_t
{
    return m_testing_labels.size( );
}

auto MnistSet::byts_to_int( const QByteArray& byteArray ) const -> int32_t
{
    if ( byteArray.size( ) != 4 )
    {
        throw std::runtime_error( "Error." );
    }

    auto ok{true};
    auto n = byteArray.toHex( ).toInt( &ok, 16 );

    if ( ok )
    {
        return n;
    }
    else
    {
        throw std::runtime_error( "Ivalid convertion numbers in m_bytsToInt()." );
    }
}

auto MnistSet::get_learning_data( const size_t index ) const -> std::pair<std::vector<nType_t>, size_t>
{
    std::vector<nType_t> out( 784 );

    const auto pos = static_cast<uint32_t>( index * 784 );
    std::transform( std::next( m_trainig_images.begin( ), pos ), std::next( m_trainig_images.begin( ), pos + 784 ), out.begin( ),
                    []( const auto& c ) { return static_cast<nType_t>( c ) / 255; } );

    return {out, m_trainig_labels[index]};
}

auto MnistSet::get_testing_data( const size_t index ) const -> std::pair<std::vector<nType_t>, size_t>
{
    std::vector<nType_t> out( 784 );

    const auto pos = static_cast<uint32_t>( index * 784 );
    std::transform( std::next( m_testing_images.begin( ), pos ), std::next( m_testing_images.begin( ), pos + 784 ), out.begin( ),
                    []( const auto& c ) { return static_cast<nType_t>( c ) / 255; } );

    return {out, m_testing_labels[index]};
}

} // namespace net
