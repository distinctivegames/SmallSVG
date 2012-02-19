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
#include "SvgColour.h"

SvgColour::SvgColour()
{
	m_type=SvgEntity::TYPE_COLOUR;

	m_colourType=COLOURTYPE_SOLID;
	
	m_rgb=0;
	
	m_stops=NULL;
	m_colours=NULL;
	m_numStops=0;
}

SvgColour::~SvgColour()
{
	if (m_stops)
	{
		delete m_stops;
	}
	if (m_colours)
	{
		delete m_colours;
	}
}

void SvgColour::setSolid(unsigned int rgb)
{
	m_colourType=COLOURTYPE_SOLID;
	
	m_rgb=rgb;
}

void SvgColour::setGradient(float x1,float y1,float x2,float y2,int numStops)
{
	m_colourType=COLOURTYPE_LINEARGRADIENT;
	
	m_x1=x1;
	m_y1=y1;
	m_x2=x2;
	m_y2=y2;

	if (m_stops)
	{
		delete m_stops;
	}
	if (m_colours)
	{
		delete m_colours;
	}
	
	m_stops=new float[numStops];
	m_colours=new unsigned int[numStops];
	
	m_numStops=numStops;
}

void SvgColour::setGradientStop(int stop,float location,unsigned int colour)
{
	if (stop>=0 && stop<m_numStops)
	{
		m_stops[stop]=location;
		m_colours[stop]=colour;
	}
}


float SvgColour::getFloatRed()
{
	return ((float)((m_rgb>>16)&255))/255;
}

float SvgColour::getFloatGreen()
{
	return ((float)((m_rgb>>8)&255))/255;
}

float SvgColour::getFloatBlue()
{
	return ((float)((m_rgb>>0)&255))/255;
}


SvgColour *SvgColour::copy()
{
	SvgColour *newCol;
	int i;
	
	newCol=new SvgColour();
	newCol->m_colourType=m_colourType;
	newCol->m_rgb=m_rgb;
	newCol->m_numStops=m_numStops;
	newCol->m_x1=m_x1;
	newCol->m_y1=m_y1;
	newCol->m_x2=m_x2;
	newCol->m_y2=m_y2;
	
	if (m_numStops>0)
	{
		newCol->m_stops=new float[m_numStops];
		newCol->m_colours=new unsigned int[m_numStops];
		
		for (i=0;i<m_numStops;i++)
		{
			newCol->m_stops[i]=m_stops[i];
			newCol->m_colours[i]=m_colours[i];
		}
	}
	
	return newCol;
}


float SvgColour::getGradientLocationForStop(int index)
{
	if (index>=0 && index<m_numStops)
	{
		return m_stops[index];
	}
	return 0;
}

float SvgColour::getGradientRedForStop(int index)
{
	if (index>=0 && index<m_numStops)
	{
		return ((float)((m_colours[index]>>16)&255))/255;	
	}
	return 0;
}

float SvgColour::getGradientGreenForStop(int index)
{
	if (index>=0 && index<m_numStops)
	{
		return ((float)((m_colours[index]>>8)&255))/255;	
	}
	return 0;
}

float SvgColour::getGradientBlueForStop(int index)
{
	if (index>=0 && index<m_numStops)
	{
		return ((float)((m_colours[index]>>0)&255))/255;	
	}
	return 0;
}


