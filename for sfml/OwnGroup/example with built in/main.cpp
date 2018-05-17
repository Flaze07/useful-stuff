#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "OwnGroup/OwnGroup.hpp"

int main()
{
    sf::RenderWindow win{ sf::VideoMode{ 600, 600 }, "OwnGroup example with built-in types" };

    Fl::OwnGroup< Fl::Type > group;
    {
        Fl::Type rect1;
        rect1.rectangle_shape.setSize( { 50, 50 } ); //implicitly declare Vector2f
        rect1.rectangle_shape.setFillColor( sf::Color::Blue );
        group.addItem( "blue rectangle", rect1 );
        group.setItemVisibility( "blue rectangle", false );

        Fl::Type circ;
        circ.circle_shape.setRadius( 25 );
        circ.circle_shape.setFillColor( sf::Color::Green );
        circ.circle_shape.setPosition( 0, 550 );
        group.addItem( "green circle", circ );

        Fl::Type conv;
        conv.circle_shape.setRadius( 25 );
        conv.circle_shape.setFillColor( sf::Color::Red );
        conv.circle_shape.setPosition( 250, 250 );
        conv.circle_shape.setPointCount( 0 );
        group.addItem( "red convex", conv );
    }

    while( win.isOpen() )
    {
        sf::Event event;
        while ( win.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed ) win.close();
            if ( event.type == sf::Event::KeyPressed )
            {
                switch( event.key.code )
                {
                case sf::Keyboard::Escape :
                    win.close();
                    break;
                case sf::Keyboard::Space :
                    group.setItemVisibility( "blue rectangle", !group.getItemVisibility( "blue rectangle" ) );
                    group.setItemVisibility( "green circle", !group.getItemVisibility( "green circle" ) );
                    group.setItemVisibility( "red convex", !group.getItemVisibility( "red convex" ) );
                    break;
                case sf::Keyboard::A :
                    group.getItem( "red convex" ).circle_shape.setPointCount( group.getItem( "red convex" ).circle_shape.getPointCount() - 1 );
                    break;
                case sf::Keyboard::D :
                    group.getItem( "red convex" ).circle_shape.setPointCount( group.getItem( "red convex" ).circle_shape.getPointCount() + 1 );
                    break;
                default :
                    break;
                }
            }
        }

        win.clear();
        win.draw( group );
        win.display();
    }
}
