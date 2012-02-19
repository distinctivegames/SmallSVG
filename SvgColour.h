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

#ifndef __SVGCOLOUR_H__
#define __SVGCOLOUR_H__

#include "SvgEntity.h"

class SvgColour : public SvgEntity
{
public:
	static const int COLOURTYPE_SOLID			=	0;
	static const int COLOURTYPE_LINEARGRADIENT	=	1;
	static const int COLOURTYPE_RADIALGRADIENT	=	2;
	
public:
	SvgColour();
	~SvgColour();
	
	int getColourType() {return m_colourType;}
	
	void setSolid(unsigned int rgb);
	float getFloatRed();
	float getFloatGreen();
	float getFloatBlue();
	
	void setGradient(float x1,float y1,float x2,float y2,int numStops);
	void setGradientStop(int stop,float location,unsigned int colour);
	
	float getGradientX1() {return m_x1;}
	float getGradientY1() {return m_y1;}
	float getGradientX2() {return m_x2;}
	float getGradientY2() {return m_y2;}
	int getGradientStops() {return m_numStops;}
	
	float getGradientLocationForStop(int index);
	float getGradientRedForStop(int index);
	float getGradientGreenForStop(int index);
	float getGradientBlueForStop(int index);
	
	SvgColour *copy();
	
private:
	int m_colourType;
	
	unsigned int m_rgb;
	
	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	
	int m_numStops;
	float *m_stops;
	unsigned int *m_colours;
};


#endif

