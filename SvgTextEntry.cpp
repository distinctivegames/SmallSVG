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
#include "svg_common.h"
#include "SvgTextEntry.h"
#include "Svg2DMatrix.h"
#include "Svg2DVector.h"

SvgTextEntry::SvgTextEntry()
{
	m_type=SvgEntity::TYPE_TEXT;
	
	m_matrix=NULL;
	m_numTextLines=0;
	m_textLines=NULL;
	
	m_next=NULL;
}

SvgTextEntry::~SvgTextEntry()
{
	int i;
	if (m_matrix)
	{
		delete m_matrix;
	}
	
	if (m_textLines)
	{
		for (i=0;i<m_numTextLines;i++)
		{
			delete m_textLines[i];
		}
		delete m_textLines;
	}
}

void SvgTextEntry::setMatrix(Svg2DMatrix *matrix)
{
	if (m_matrix)
	{
		delete m_matrix;
	}
	m_matrix=matrix;
}


void SvgTextEntry::setNumTextLines(int num)
{
	int i;
	
	if (m_textLines!=NULL)
	{
		delete m_textLines;
	}
	m_textLines=new SvgTextLine*[num];
	m_numTextLines=num;
	
	for (i=0;i<num;i++)
	{
		m_textLines[i]=NULL;
	}
}

void SvgTextEntry::setTextLine(int index,SvgTextLine *line)
{
	if (index>=0 && index<m_numTextLines)
	{
		if (m_textLines[index]!=NULL)
		{
			delete m_textLines[index];
		}
		
		m_textLines[index]=line;
	}
}


SvgTextLine *SvgTextEntry::getTextLine(int index)
{
	if (index>=0 && index<m_numTextLines)
	{
		return m_textLines[index];
	}
	return NULL;
}


float SvgTextEntry::getTextLineX(int index)
{
	SvgTextLine *line;
	
	line=getTextLine(index);
	if (line)
	{
		Svg2DVector vec;
		
		vec.setX(line->getX());
		vec.setY(line->getY());
		m_matrix->transformVector(&vec);

		return vec.getX();
	}
	
	return 0;
}

float SvgTextEntry::getTextLineY(int index)
{
	SvgTextLine *line;
	
	line=getTextLine(index);
	if (line)
	{
		Svg2DVector vec;
		
		vec.setX(line->getX());
		vec.setY(line->getY());
		m_matrix->transformVector(&vec);
		
		return vec.getY();
	}
	
	return 0;
	
}

