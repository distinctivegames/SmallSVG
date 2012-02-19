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
#ifndef __SVGLINE_H__
#define __SVGLINE_H__

#include "SvgLineSeg.h"
#include "SvgEntity.h"

class SvgColour;

class SvgLine : public SvgEntity
{
public:
	static const int LINECAP_BUTT		= 0;
	static const int LINECAP_ROUND		= 1;
	static const int LINECAP_SQUARE		= 2;
	
public:
	SvgLine();
	~SvgLine();
	
	void addSegment(SvgLineSeg *seg);
	
	void setStrokeWidth(float width) {m_strokeWidth=width;}
	float getStrokeWidth() {return m_strokeWidth;}
	
	int getNumSegments() {return m_numSegments;}
	SvgLineSeg *getSegment(int index);
	
	void setStrokeColour(SvgColour *colour);
	SvgColour *getStrokeColour() {return m_strokeColour;}
	
	void setFillColour(SvgColour *colour);
	SvgColour *getFillColour() {return m_fillColour;}
	
	void setStrokeDashArrayFromText(const char *text);
	int getStrokeDashArrayLength() {return m_strokeDashArrayLength;}
	float *getStrokeDashArray() {return m_strokeDashArray;}
	
	void setStrokeLineCap(const char *linecap);
	int getStrokeLineCap() {return m_strokeLineCap;}
	
	
private:
	int m_numSegments;
	SvgLineSeg *m_head;

	float m_strokeWidth;
	
	SvgColour *m_strokeColour;
	SvgColour *m_fillColour;
	
	int	m_strokeLineCap;
	
	int m_strokeDashArrayLength;
	float *m_strokeDashArray;
};

#endif

