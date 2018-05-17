#include <unordered_map>
#include <utility>
#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "ObserveGroup.hpp"

namespace Fl
{

ObserveGroup::ObserveGroup() :
    visible( true )
{}

void ObserveGroup::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    if ( !visible ) return;
    for ( const auto& drawables : data )
    {
        if ( drawables.second.second )//check if a drawable is visible or not
        {
            target.draw( drawables.second.first, states );
        }
    }
}

void ObserveGroup::setObjectVisibility( const std::string& str, const bool& condition )
{
    data.at( str ).second = condition;
}

const bool& ObserveGroup::getObjectVisibility( const std::string& str ) const
{
    return data.at( str ).second;
}

void ObserveGroup::setVisibility( const bool& condition )
{
    visible = condition;
}

const bool& ObserveGroup::getVisibility() const
{
    return visible;
}

const bool& ObserveGroup::getObjectVisibility() const
{
    return visible;
}

void ObserveGroup::addObject( const std::string& str, sf::Drawable& drawable )
{
    data.insert( std::make_pair( str, std::make_pair( std::reference_wrapper< sf::Drawable >( drawable ), true ) ) );
}

void ObserveGroup::removeObject( const std::string& str )
{
    data.erase( str );
}

}
