#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "ObserveGroup/ObserveGroup.hpp"

int main()
{
    sf::RenderWindow win{ sf::VideoMode{ 600, 600 }, "ObserveGroup example" };
    Fl::ObserveGroup group;

    sf::RectangleShape rect1{ { 50, 50 } };
    rect1.setFillColor( sf::Color::Blue );
    group.addObject( "blue rectangle", rect1 );
    group.setObjectVisibility( "blue rectangle", false );

    sf::CircleShape circ{ 25 };
    circ.setFillColor( sf::Color::Green );
    circ.setPosition( { 0, 550 } );
    group.addObject( "green circle", circ );

    sf::CircleShape conv;
    conv.setRadius( 25 );
    conv.setFillColor( sf::Color::Red );
    conv.setPosition( 250, 250 );
    conv.setPointCount( 0 );
    group.addObject( "red convex", conv );

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
                case sf::Keyboard::Space :
                    group.setObjectVisibility( "blue rectangle", !group.getObjectVisibility( "blue rectangle" ) );
                    group.setObjectVisibility( "green circle", !group.getObjectVisibility( "green circle" ) );
                    group.setObjectVisibility( "red convex", !group.getObjectVisibility( "red convex" ) );
                    break;
                case sf::Keyboard::LAlt :
                case sf::Keyboard::RAlt :
                    group.setVisibility( !group.getVisibility() );
                    break;
                case sf::Keyboard::A :
                    conv.setPointCount( conv.getPointCount() - 1 );
                    break;
                case sf::Keyboard::D :
                    conv.setPointCount( conv.getPointCount() + 1 );
                default :;
                }
            }
        }

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) //pressing right and space at the same time, space won't work
        {
            rect1.move( 0.1, 0 );
            circ.move( 0.1, 0 );
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
        {
            rect1.move( -0.1, 0 );
            circ.move( -0.1, 0 );
        }

        win.clear();
        win.draw( group );
        win.display();
    }
}
