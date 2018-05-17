#ifndef OWNGROUP_HPP_INCLUDED
#define OWNGROUP_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <unordered_map>
#include <utility>
#include <string>
#include <memory>

namespace Fl
{
    struct Type : public sf::Drawable
    {
        Type(){}
        Type( const Type& that )
        {
            vertex_buffer = that.vertex_buffer;
            vertex_array = that.vertex_array;
            text = that.text;
            sprite = that.sprite;
            rectangle_shape = that.rectangle_shape;
            convex_shape = that.convex_shape;
            circle_shape = that.circle_shape;
        }
        virtual ~Type() = default;
        sf::VertexBuffer vertex_buffer;
        sf::VertexArray vertex_array;
        sf::Text text;
        sf::Sprite sprite;
        sf::RectangleShape rectangle_shape;
        sf::ConvexShape convex_shape;
        sf::CircleShape circle_shape;
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
        {
            target.draw( vertex_buffer, states );
            target.draw( vertex_array, states );
            target.draw( text, states );
            target.draw( sprite, states );
            target.draw( rectangle_shape, states );
            target.draw( convex_shape, states );
            target.draw( circle_shape, states );
        }
    };

    template < typename T >
    class OwnGroup : public sf::Drawable
    {
    public :
        OwnGroup() : visible( true ) {}
        OwnGroup( const OwnGroup& that ) = delete;
        OwnGroup( OwnGroup&& that ) = delete;
        OwnGroup& operator=( const OwnGroup& that ) = delete;
        OwnGroup& operator=( OwnGroup&& that ) = delete;

        void addItem( const std::string& name, const T& item )
        {
            this->item.insert( std::make_pair( name, std::make_pair( std::make_unique< T >( item ), true ) ) );
        }
        void addItem( const std::string&& name, const T& item )
        {
            this->item.insert( std::make_pair( name, std::make_pair( std::make_unique< T >( item ), true ) ) );
        }
        T& getItem( const std::string& name )
        {
            return *( item.at( name ).first );
        }
        void removeItem( const std::string& name )
        {
            item.erase( name );
        }

        void setItemVisibility( const std::string& name, const bool& condition)
        {
            item.at( name ).second = condition;
        }
        const bool& getItemVisibility( const std::string& name ) const
        {
            return item.at( name ).second;
        }

        void setVisibility( const bool& condition )
        {
            visible = condition;
        }
        const bool& getVisibility() const
        {
            return visible;
        }
    private :
        virtual void draw( sf::RenderTarget& target, sf::RenderStates state ) const
        {
            if ( !visible ) return;
            for ( auto& a : item )
            {
                if ( !a.second.second ) continue;
                target.draw( *( a.second.first ) );
            }
        }
        std::unordered_map< std::string, std::pair< std::unique_ptr< T >, bool > > item;
        bool visible;
    };
}

#endif // OWNGROUP_HPP_INCLUDED
