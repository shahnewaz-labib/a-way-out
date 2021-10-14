#include "game_drawable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Item : public Game_Drawable {
public:
    RectangleShape boundary;
    Sprite sprite;
    Texture texture;
    Item(RenderWindow *window,Vector2f pos,Vector2f size,Texture T);
    void setTextureRect(bool hover=0);
    void draw();
};
