#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "OwnGroup/OwnGroup.hpp"

class Ex : public sf::Drawable
{
public :
    Ex(){} //when initialized with default constructor, your class must not be able to be seen when it is drawn
    Ex( const Ex& that ) : rect( that.rect ) {} //copy constructor is a must
    sf::RectangleShape& getRect()
    {
        return rect;
    }
private :
    sf::RectangleShape rect;
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        target.draw( rect, states );
    }
};

struct TypeExt : Fl::Type //you can declare this inside main, also, I used TypeExt as the name because it implies it is extended. Any name can be used
{
    TypeExt() : Fl::Type() {}
    TypeExt( const TypeExt& that ) : Fl::Type( that ), ex( that.ex ) {} //copy constructor is a must
    //add your type
    Ex ex;
    //override base class draw
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        Fl::Type::draw( target, states ); //call base class draw is a must
        target.draw( ex, states );
    }

};

int main()
{
    sf::RenderWindow win{ sf::VideoMode{ 600, 600 }, "OwnGroup with self made type" };

    Fl::OwnGroup< TypeExt > group;
    {
        TypeExt ex_rect;
        ex_rect.ex.getRect().setSize( { 50, 50 } );
        ex_rect.ex.getRect().setFillColor( sf::Color::Blue );
        group.addItem( "self defined", ex_rect );

        TypeExt circle;
        circle.circle_shape.setRadius( 25 );
        circle.circle_shape.setFillColor( sf::Color::Yellow );
        circle.circle_shape.setPosition( 300, 300 );
        circle.circle_shape.setPointCount( 0 );
        group.addItem( "built in", circle );
    }

    while( win.isOpen() )
    {
        sf::Event event;
        while( win.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed ) win.close();
            if ( event.type == sf::Event::KeyPressed )
            {
                switch( event.key.code )
                {
                case sf::Keyboard::Escape :
                    win.close();
                    break;
                case sf::Keyboard::Left :
                    group.getItem( "self defined" ).ex.getRect().move( -5, 0 );
                    group.getItem( "built in" ).circle_shape.setPointCount( group.getItem( "built in" ).circle_shape.getPointCount() - 1 );
                    break;
                case sf::Keyboard::Right :
                    group.getItem( "self defined" ).ex.getRect().move( 5, 0 );
                    group.getItem( "built in" ).circle_shape.setPointCount( group.getItem( "built in" ).circle_shape.getPointCount() + 1 );
                    break;
                default :;
                }
            }
        }

        win.clear();
        win.draw( group );
        win.display();
    }
}
