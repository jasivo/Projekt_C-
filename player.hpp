#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
//#include "items.cpp"

class Player
{
    public:
        Player(float x, float y, float v);
        void Draw(sf::RenderWindow& window);
        void Update(float delta_time);
        void get_texture_size(sf::Texture &texture, sf::Vector2u &vector);
        sf::Texture & get_texture();
        void animation(sf::Texture &texture, int &face, float deltaTime, float switchTime);
        int & get_face();
        sf::Vector2f get_position(){return player_shape.getPosition();};
        sf::Vector2f get_center();
        sf::Text & get_state();
        void Update_hp_info();
        sf::Text get_hp_info();
        int & get_strenght();
        int & get_defence();
        int & get_health();
        int & get_maxhealth();
        void set_item(int id);
        bool item(int id);
    private:
        float xpos;
        float ypos;
        const float height;
        const float width;
        float velocity;
        int face;
        sf::Font fonte;
        sf::Text state;
        sf::Text hp_info;
        sf::Texture player_texture;
        sf::RectangleShape player_shape;
        sf::Vector2u texture_size;
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        float totalTime;
        float switchTime;
        int strenght;
        int health;
        int max_health;
        int defense;
        bool sword;
        bool armor;
        bool shield;
};

#endif