#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
const float secsperframe = 0.001, ballsize = 50;
float rotation = M_PI, speed = 12; //55.555 cool
int swidth = 1920, sheight = 1080, hitposx, hitposy;
sf::CircleShape ball(ballsize);
sf::Vertex line[2]= {};
sf::RenderTexture maptex;
sf::Sprite mapsprite;
bool displayball = 0;
void display(sf::RenderWindow& window), delay(), physics(), drawline();
int main(){
    std::cout << "rotation: ";
    std::cin >> rotation;
    std::cout << "speed: ";
    std::cin >> speed;
    std::cout << "display ball (0/1): ";
    std::cin >> displayball;
    if(std::cin.fail()){
        std::cout << "\nerror, invalid input. using defaults\n";
        std::cout << "rotation: 55.555\nspeed: 5\ndisplay ball: 1";
        rotation = M_PI; speed = 5; displayball = 1;
    }
    srand(clock());
    maptex.create(swidth, sheight);
    maptex.clear(sf::Color::Black);
    sf::RenderWindow window(sf::VideoMode(swidth, sheight), "balls phys - MrKeviscool", sf::Style::Fullscreen);
    ball.setFillColor(sf::Color(255, 0, 0));
    ball.setPosition(swidth/2-ballsize, sheight/2);
    hitposx = swidth/2-ballsize;
    hitposy = sheight/2;
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        //////LOOP//////
        display(window);
        physics();
        delay();
        /////////////
    }
}
void physics()
{
    float x, y;
    if (ball.getPosition().y < 2)
    {
        if (rotation <= 180)
        {
            rotation = 180 - rotation;
        }
        else
        {
            rotation = 180 + (360 - rotation);
        }
        drawline();
    }
    else if (ball.getPosition().x > swidth - (2 * ballsize))
    {
        if (rotation >= 90)
        {
            rotation = (180 - rotation) + 180;
        }
        else
        {
            rotation = 360 - rotation;
        }
        drawline();
    }
    else if (ball.getPosition().y > sheight - (ballsize * 2))
    {
        if (rotation <= 180)
        {
            rotation = 180 - rotation;
        }
        else
        {
            rotation = 360 - (rotation - 180);
        }
        drawline();
    }
    else if (ball.getPosition().x < 1)
    {
        rotation = 360 - rotation;
        drawline();
    }
    //look, i know i coulda done the bearing stuff esier but i rlly dont care
    x = sin(rotation * (M_PI / 180)) * speed;
    y = cos(rotation * (M_PI / 180)) * -speed;
    ball.move(x, y);
}
void drawline(){
    line[0] = sf::Vertex(sf::Vector2f(hitposx, hitposy));
    line[1] = sf::Vertex(sf::Vector2f(ball.getPosition().x, ball.getPosition().y));
    maptex.draw(line, 2, sf::Lines);
    maptex.display();
    mapsprite.setTexture(maptex.getTexture());
    hitposx = ball.getPosition().x;
    hitposy = ball.getPosition().y;
}

void display(sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    window.draw(mapsprite);
    if(displayball == 1){
    window.draw(ball);
    }
    window.display();
}
void delay()
{ 
    unsigned long tix = (secsperframe * CLOCKS_PER_SEC);
    unsigned long newtix = clock() + tix;
    while (newtix > clock()){}
    return;
}