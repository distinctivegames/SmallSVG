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
#include "SvgImage.h"
#include "Svg2DMatrix.h"
#include <math.h>

SvgImage::SvgImage()
{
	m_type=SvgEntity::TYPE_IMAGE;
	
	m_dataFormat=DATAFORMAT_UNKNOWN;
	m_width=0;
	m_height=0;
	m_matrix=NULL;
	m_data=NULL;
	m_next=NULL;
}

SvgImage::~SvgImage()
{
	if (m_data)
	{
		delete m_data;
	}
	
	if (m_matrix)
	{
		delete m_matrix;
	}
}

void SvgImage::setMatrix(Svg2DMatrix *matrix)
{
	if (m_matrix)
	{
		delete m_matrix;
	}
	m_matrix=matrix;
}


void SvgImage::setData(char *data)
{
	if (m_data)
	{
		delete m_data;
		m_data=NULL;
	}
	
	if (data)
	{
		m_data=strdup(data);
	}
}


float SvgImage::getImageX()
{
	if (m_matrix)
	{
		return m_matrix->getElement(2,0);
	}
	return 0;
}

float SvgImage::getImageY()
{
	if (m_matrix)
	{
		return m_matrix->getElement(2,1);
	}
	return 0;
}


float SvgImage::getImageXScale()
{
	if (m_matrix)
	{
		float x=m_matrix->getElement(0,0);
		float y=m_matrix->getElement(1,0);
		return sqrt(x*x+y*y);
	}
	return 1.0f;
}

float SvgImage::getImageYScale()
{
	if (m_matrix)
	{
		float x=m_matrix->getElement(0,1);
		float y=m_matrix->getElement(1,1);
		return sqrt(x*x+y*y);
	}
	return 1.0f;
}



