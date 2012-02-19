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
#include "SvgLine.h"
#include "SvgLineSeg.h"
#include "SvgColour.h"


SvgLine::SvgLine()
{
	m_type=SvgEntity::TYPE_PATH;
	
	m_head=NULL;
	m_numSegments=0;
	
	m_strokeWidth=0.5f;
	m_strokeColour=NULL;
	m_fillColour=NULL;
	
	m_strokeDashArray=NULL;
	m_strokeDashArrayLength=0;
	
	m_strokeLineCap=LINECAP_BUTT;
	
	m_next=NULL;
}

SvgLine::~SvgLine()
{
	SvgLineSeg *curr;
	SvgLineSeg *next;
	
	curr=m_head;
	while(curr)
	{
		next=curr->m_next;
		delete curr;
		curr=next;
	}
	
	if (m_strokeColour)
	{
		delete m_strokeColour;
	}
	if (m_fillColour)
	{
		delete m_fillColour;
	}
	
	if (m_strokeDashArray)
	{
		delete m_strokeDashArray;
	}
}

void SvgLine::addSegment(SvgLineSeg *seg)
{
	SvgLineSeg *curr;
	SvgLineSeg *prev;
	
	prev=NULL;
	curr=m_head;
	while(curr)
	{
		prev=curr;
		curr=curr->m_next;
	}
	
	if (prev==NULL)
	{
		m_head=seg;
	}
	else
	{
		prev->m_next=seg;
	}
	
	m_numSegments++;
}

SvgLineSeg *SvgLine::getSegment(int index)
{
	if (index>=0 && index<m_numSegments)
	{
		SvgLineSeg *curr;
		int count;
		
		count=0;
		curr=m_head;
		while(curr)
		{
			if (count==index)
			{
				return curr;
			}
			curr=curr->m_next;
			count++;
		}		
	}
	
	return NULL;
	
}

void SvgLine::setStrokeColour(SvgColour *colour)
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

void SvgLine::setFillColour(SvgColour *colour)
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

void SvgLine::setStrokeDashArrayFromText(const char *text)
{
	if (m_strokeDashArray)
	{
		delete m_strokeDashArray;
		m_strokeDashArray=NULL;
		m_strokeDashArrayLength=0;
	}
	
	if (text)
	{
		char *temp;
		int i,start,end;
		int count;
		
		count=0;
		for (i=0;text[i]!=0;i++)
		{
			if (text[i]==',' || text[i+1]==0)
			{
				count++;
			}
		}
		
		m_strokeDashArrayLength=count;
		m_strokeDashArray=new float[m_strokeDashArrayLength];
		
		count=0;
		for (i=0,start=0;text[i]!=0;i++)
		{
			if (text[i]==',' || text[i+1]==0)
			{
				if (text[i]==',')
				{
					end=i;
				}
				else
				{
					end=i+1;
				}

				temp=new char[(end-start)+1];
				strncpy(temp,text+start,end-start);
				
				sscanf(temp,"%f",&m_strokeDashArray[count]);

				delete temp;
				
				start=i+1;
				count++;
			}
		}		
		
		
		
		
		
	}
}

void SvgLine::setStrokeLineCap(const char *linecap)
{
	if (strcmp(linecap,"butt")==0)
	{
		m_strokeLineCap=LINECAP_BUTT;
	}
	else if (strcmp(linecap,"round")==0)
	{
		m_strokeLineCap=LINECAP_ROUND;
	}
	else if (strcmp(linecap,"square")==0)
	{
		m_strokeLineCap=LINECAP_SQUARE;
	}
}




