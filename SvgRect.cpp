/*
 Orignally wirttend by Distinctive Developments Ltd
 http://www.distinctivegames.com
 
 Project Home:
 http://github.com/distinctivegames/SmallSVG
 
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
#include "svg_common.h"
#include "SvgRect.h"
#include "SvgColour.h"

SvgRect::SvgRect()
{
	m_type=TYPE_RECT;

	m_x=0;
	m_y=0;
	m_width=0;
	m_height=0;

	m_strokeColour=NULL;
	m_fillColour=NULL;
	
	m_next=NULL;
}

SvgRect::~SvgRect()
{
	if (m_strokeColour)
	{
		delete m_strokeColour;
	}
	if (m_fillColour)
	{
		delete m_fillColour;
	}	
}


void SvgRect::setRect(float x,float y,float width,float height)
{
	m_x=x;
	m_y=y;
	m_width=width;
	m_height=height;
}


void SvgRect::setStrokeColour(SvgColour *colour)
{
	if (m_strokeColour)
	{
		delete m_strokeColour;
		m_strokeColour=NULL;
	}
	if (colour)
	{
		m_strokeColour=colour;
	}
}

void SvgRect::setFillColour(SvgColour *colour)
{
	if (m_fillColour)
	{
		delete m_fillColour;
		m_fillColour=NULL;
	}
	if (colour)
	{
		m_fillColour=colour;
	}
}

