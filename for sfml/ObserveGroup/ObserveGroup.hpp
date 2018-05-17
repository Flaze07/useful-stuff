#ifndef OBSERVEGROUP_HPP_INCLUDED
#define OBSERVEGROUP_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include <utility>
#include <functional>

namespace Fl
{

//a class to Group objects that can be drawn
class ObserveGroup : public sf::Drawable
{
public :
    //constructor and destructor
    ObserveGroup();
    virtual ~ObserveGroup() = default;
    //make the class non-copyable, and non-moveable
    ObserveGroup( const ObserveGroup& that ) = delete;
    ObserveGroup( ObserveGroup&& that ) = delete;
    ObserveGroup& operator=( const ObserveGroup& that ) = delete;
    ObserveGroup& operator=( ObserveGroup&& that ) = delete;
    //function
    void setObjectVisibility( const std::string& str, const bool& condition );
    const bool& getObjectVisibility( const std::string& str ) const;
    void setVisibility( const bool& condition );
    const bool& getVisibility() const;
    const bool& getObjectVisibility() const;
    void addObject( const std::string& str, sf::Drawable& drawable );
    void removeObject( const std::string& str );
private :
    std::unordered_map< std::string, std::pair< std::reference_wrapper< const sf::Drawable >, bool > > data;
    bool visible;
    //override draw
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
};

}

#endif // GROUP_HPP_INCLUDED
