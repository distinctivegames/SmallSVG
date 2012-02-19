/*
 Project Home:
 http://github.com/distinctivegames/SmallSVG
 
 Copyright 2011 Distinctive Developments Ltd
 http://www.distinctivegames.com 
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any
 damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any
 purpose, including commercial applications, and to alter it and
 redistribute it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must
 not claim that you wrote the original software. If you use this
 software in a product, an acknowledgment in the product documentation
 would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and
 must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 */
#include "SvgLineSegStraight.h"


SvgLineSegStraight::SvgLineSegStraight()
{
	m_type=TYPE_STRAIGHT;
}

SvgLineSegStraight::~SvgLineSegStraight()
{
}

void SvgLineSegStraight::addSegment(float x1,float y1,float x2,float y2)
{
	m_x1=x1;
	m_y1=y1;
	m_x2=x2;
	m_y2=y2;
}


