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
#include <string.h>
#include <stdio.h>
#include "SvgTextLine.h"

SvgTextLine::SvgTextLine()
{
	m_x=0;
	m_y=0;
	m_fontSize=0;
	m_fontName=NULL;
	m_text=NULL;
}

SvgTextLine::~SvgTextLine()
{
	if (m_text)
	{
		delete m_text;
	}
	
	if (m_fontName)
	{
		delete m_fontName;
	}
}

void SvgTextLine::setXFromText(char *text)
{
	if (sscanf(text,"%f",&m_x)!=1)
	{
		m_x=0;
	}
}

void SvgTextLine::setYFromText(char *text)
{
	if (sscanf(text,"%f",&m_y)!=1)
	{
		m_y=0;
	}
}

void SvgTextLine::setFontSizeFromText(char *text)
{
	if (sscanf(text,"%f",&m_fontSize)!=1)
	{
		m_fontSize=0;
	}
}

void SvgTextLine::setX(float x)
{
	m_x=x;
}

void SvgTextLine::setY(float y)
{
	m_y=y;
}

void SvgTextLine::setFontSize(float size)
{
	m_fontSize=size;
}

void SvgTextLine::setText(char *text)
{
	if (m_text)
	{
		delete m_text;
		m_text=NULL;
	}
	if (text!=NULL)
	{
		if (strcmp(text,"ry")==0)
		{
			int i=0;
		}
		
		m_text=strdup(text);
	}
}

void SvgTextLine::setFontName(char *font)
{
	if (m_fontName)
	{
		delete m_fontName;
		m_fontName=NULL;
	}
	
	if (font!=NULL)
	{
		m_fontName=strdup(font);
	}
}
