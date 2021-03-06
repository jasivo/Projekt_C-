#include "enemy.hpp"
#include <math.h>
#include <ctime>
//#include "player.hpp"
#include "game.hpp"

Enemy::Enemy(float x, float y, float v)
: xpos(x),ypos(y),velocity_x(v),velocity_y(v),height(64),width(64),damage(15),health(20),max_health(20),timer(2000),time_attack(time(NULL)),time_def(time(NULL))
{
    //std::cout << "Utworzono przeciwnika o pozycji " << x << " " << y << " i wymiarach " << height << " " << width << " i predkosci " << velocity_x << std::endl;
    Enemy::enemy_texture.loadFromFile("images/bat_sprite2.png");
    Enemy::enemy_shape.setSize(sf::Vector2f(64.0f,64.0f));
    Enemy::enemy_shape.setTexture(&enemy_texture);
    Enemy::get_texture_size(enemy_texture, texture_size);
    Enemy::enemy_shape.setTextureRect(sf::IntRect(texture_size.x*1, texture_size.y*1, texture_size.x, texture_size.y));
    Enemy::enemy_shape.setPosition(sf::Vector2f(xpos,ypos));
    Enemy::enemy_shape.setOrigin(Enemy::enemy_shape.getSize()/2.0f);
    Enemy::imageCount = sf::Vector2u(4,4);
    Enemy::face = 1;
    Enemy::fonte.loadFromFile("Winter.ttf");
    Enemy::hp_info.setFont(fonte);
    Enemy::hp_info.setCharacterSize(20);
    Enemy::hp_info.setStyle(sf::Text::Bold);
    Enemy::hp_info.setFillColor(sf::Color::White);
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(enemy_shape);
}

int Enemy::get_maxhealth()
{
    return max_health;
}

void Enemy::Update_hp_info()
{
    hp_info.setPosition(get_position()-sf::Vector2f(20.0f,55.0f));
    if(health > 0)
        hp_info.setString(std::to_string(get_health())+" / "+std::to_string(get_maxhealth()));
    else
        hp_info.setString("");
    
}

sf::Text Enemy::get_hp_info()
{
    return hp_info;
}

sf::Texture & Enemy::get_texture()
{
    return enemy_texture;
}

int & Enemy::get_face()
{
    return face;
}

void Enemy::get_texture_size(sf::Texture &texture, sf::Vector2u &vector)
{
    vector = texture.getSize();
    vector.x /= 4;
    vector.y /= 4;
}

void Enemy::animation(sf::Texture &texture, int &face)
{
    if(get_health()>0)
    {
        switch(face)
        {
            // prawo
            case 0:
                Enemy::enemy_shape.setTextureRect(sf::IntRect(texture_size.x, texture_size.y, texture_size.x, texture_size.y));
                break;
            // lewo
            case 1:
                Enemy::enemy_shape.setTextureRect(sf::IntRect(texture_size.x, texture_size.y*3, texture_size.x, texture_size.y));
                break;
        }
    }
    else if(get_health()<=0)
    {
        Enemy::enemy_shape.setTextureRect(sf::IntRect(0, 0, texture_size.x, texture_size.y));           
    }
}

int & Enemy::settimer()
{
    return timer;
}

void Enemy::Update(float delta_time, Player & player, int & c)
{
    // if(get_health()>=0)
    // {
    //     sf::Vector2f pl_pos = player.get_center();
    //     sf::Vector2f en_pos = get_center();

    //     int dx = en_pos.x-pl_pos.x;
    //     int dy = en_pos.y-pl_pos.y;

    //     int r = sqrt(pow(dx,2)+pow(dy,2));

    //     if(r<=60)
    //         {
    //             if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    //             {
    //                 if(time(NULL)-t_d() >= 2)
    //                 {   

    //                     player.get_state().setString("Attacking...");
    //                     player.get_state().setString("");   
    //                 }
    //             //     else
    //             //         player.get_state().setString("");
    //             }
    //             // else
    //             // {
    //             //     player.get_state().setString("");
    //             // }
                
    //         }
    // }

    if(get_health()>0)
        {
        sf::Vector2f pl_pos = player.get_center();
        sf::Vector2f en_pos = get_center();

        int dx = en_pos.x-pl_pos.x;
        int dy = en_pos.y-pl_pos.y;

        int r = sqrt(pow(dx,2)+pow(dy,2));

        if(velocity_x>0)
            face = 0;
        else
            face = 1;
        

        if(r > 250)
            {   
                velocity_y = 0;
                xpos += velocity_x;
                if(settimer()>0)
                {
                    settimer() -= 1;
                }    
                else
                {
                    settimer() = 2000;
                    velocity_x *= -1;
                }
            }
        else
        {
            if(velocity_x>0)
            {
                if(en_pos.x > pl_pos.x+50)
                {
                    velocity_x = -0.1;
                }
            }
            else
            {
                if(en_pos.x < pl_pos.x-50)
                velocity_x = 0.1;
            }
            xpos += velocity_x;
            if(velocity_y>0)
            {
                if(en_pos.y > pl_pos.y+50)
                {
                    velocity_y = -0.1;
                }
            }
            else
            {
                if(en_pos.y < pl_pos.y-50)
                velocity_y = 0.1;
            }
            ypos += velocity_y;
        }

        if(r<=40)
        {
            if(time(NULL)-t_a() >= 2)
            {
                t_a() = time(NULL);
                player.get_health()-=(damage-player.get_defence());
            }
        }

            if(r<=60)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    if(time(NULL)-t_d() >= 2)
                    {    
                        t_d() = time(NULL);
                        get_health() -= player.get_strenght();
                    }
                }
            }

    }
    else if(get_health()<=0)
    {
        if(get_health() == 0)
        {
            c += 1;
            drop_item(player);
            get_health() -= 1;
        }
        velocity_x = 0;
        velocity_y = 0;
    }


            
    enemy_shape.setPosition(xpos,ypos);
}

sf::Vector2f Enemy::get_center()
{
    return sf::Vector2f(xpos+(width/2),ypos+(height/2));
}

int & Enemy::get_health()
{
    return health;
}

time_t & Enemy::t_a()
{
    return time_attack;
}

time_t & Enemy::t_d()
{
    return time_def;
}

void Enemy::drop_item(Player & player)
{
    int randomize = rand() % 11;
    if(randomize==0)
    {
        player.set_item(0);
    }
    else if(randomize==1)
    {
        player.set_item(1);
    }
    else if(randomize==2)
    {
        player.set_item(2);
    }
}