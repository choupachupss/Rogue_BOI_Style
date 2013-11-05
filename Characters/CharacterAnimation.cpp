#include "CharacterAnimation.h"
#include <fstream>

CharacterAnimation::CharacterAnimation(const KiroGame::Image& sprite_sheet, 
                                       const AnimationState a):
m_etat(a),
in_animation(false),
m_tick_counter(0),
m_loop(false)
{
    if(!m_texture.loadFromImage(sprite_sheet.image))
    {
    	//Handle Eror
    	infos::log(RENDERING_PATH,"Texture not loaded");
    }
    m_sprite.setTexture(m_texture);
    std::ifstream info_file(sprite_sheet.info_path.c_str());
    
    if(info_file.fail())
    {
    	infos::log(RENDERING_PATH,"Infos path not found : " + sprite_sheet.info_path);
    }
    std::string item,item2;
    
    std::getline(info_file,item, ' ');
    std::getline(info_file,item2);
    
    infos::log(RENDERING_PATH,"Creating Sprite : " + item + ", " + item2);
    m_sprite_size = std::make_pair(std::stoi(item),std::stoi(item2));
    m_sprite.setTextureRect(sf::IntRect(0,0,m_sprite_size.first,m_sprite_size.second));

    for(int j = 0; j < 2; ++j)
    {
        for(int i = 0; i < 3; ++i)
        {
            std::getline(info_file,item, ' ');
             m_animation_length.push_back(std::stoi(item));
        }
        std::getline(info_file,item);
        m_animation_length.push_back(std::stoi(item));
    }
}

CharacterAnimation& CharacterAnimation::operator++()
{
	auto pos = m_sprite.getTextureRect();
    int max = m_etat.state.movement;

    if(++m_tick_counter >= m_animation_length[max])
    {
        m_tick_counter = 0;
        if(!m_loop)
            in_animation = false;
    }

    pos.left = m_tick_counter * m_sprite_size.second;

    m_sprite.setTextureRect(pos);
}

void CharacterAnimation::update()
{
    if(in_animation)
        ++(*this);
}

void CharacterAnimation::setAnimationState(const State& a)
{
    m_etat.state = a;
    m_etat.animation_cpt = 0;
}

 void CharacterAnimation::AdjustAnimation(State a)
 {
    // First we need to adjust our sprite on the sprite sheet
    if(a != m_etat.state)
    {
        int correct_line = a.movement * 4 + a.dir;
        m_sprite.setTextureRect(sf::IntRect(0,correct_line * m_sprite_size.second,m_sprite_size.first,m_sprite_size.second));
        m_etat.state = a;
        m_etat.animation_cpt = 0;
    }
    else
    {
        m_etat.animation_cpt++;
    }
 }

sf::Sprite CharacterAnimation::getSprite() const
{
    return m_sprite;
}
