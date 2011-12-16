/**
Copyright (C) 2011 babin philippe

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#include "ImgAnim.hpp"

ImgAnim::ImgAnim(const sf::Texture &Img, const unsigned int &nbFrame, const unsigned int &line,
			const sf::Vector2f &Position, const sf::Vector2f &Scale,float Rotation, const sf::Color &Col)
: sf::Sprite(Img){
    this->SetPosition(Position);
	m_animRow=0;
	//Le constructeur par défaut prend en compte qu'il n'y a aucun offset
	SetSubRect(sf::IntRect(0,0,Img.GetWidth()/nbFrame,Img.GetHeight()/line));
	m_xOffset=0;
	m_yOffset=0;
	m_size=nbFrame;
}


void ImgAnim::setAnimRow(const unsigned int &row){
	m_animRow=row;
	refreshSubRect();
}

int ImgAnim::animRow() const{
	return m_animRow;
}

void ImgAnim::setFrameDim(const unsigned int &w, const unsigned int &h){
	sf::IntRect tRect = GetSubRect();
	SetSubRect(sf::IntRect(tRect.Left,tRect.Top,w,h));
}
//void ImgAnim::setImg(const sf::Texture &Img,)
//{
//	SetSubRect(sf::IntRect(0,0,Img.GetWidth()/nbFrame,Img.GetHeight()/line));
//}

sf::IntRect ImgAnim::frameDim() const{
	sf::IntRect tRect = GetSubRect();
	return sf::IntRect(0,0,tRect.Width,tRect.Height);
}

void ImgAnim::setOffset(const unsigned int &x, const unsigned int &y){
	m_xOffset=x;
	m_yOffset=y;

	refreshSubRect();
}

sf::IntRect ImgAnim::offset() const{
	return sf::IntRect(0,0,m_xOffset,m_yOffset);
}

int unsigned ImgAnim::getSize() const{
	return m_size;
}

void ImgAnim::setSize(const unsigned int &size){
	m_size=size;
}


void ImgAnim::setFrame(const unsigned int &count){
	Anim::setFrame(count);
	refreshSubRect();
}

void ImgAnim::refreshSubRect(){
	sf::IntRect tRect = GetSubRect();
	SetSubRect(sf::IntRect(tRect.Width*currentFrame()+m_xOffset,
							tRect.Height*m_animRow+m_yOffset,
							tRect.Width,
							tRect.Height));
}


void ImgAnim::Render(sf::RenderTarget& Target, sf::Renderer& Renderer) const{
	ImgAnim* th = const_cast<ImgAnim*>(this);
	th->update();
	sf::Sprite::Render(Target,Renderer);
}
