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

#ifndef __SVGIMAGE_H__
#define __SVGIMAGE_H__

#include "SvgEntity.h"

class Svg2DMatrix;

class SvgImage : public SvgEntity
{
public:
	static const int DATAFORMAT_UNKNOWN		=	0;
	static const int DATAFORMAT_BASE64JPEG	=	1;
public:
	SvgImage();
	~SvgImage();
	
	void setMatrix(Svg2DMatrix *matrix);
	Svg2DMatrix *getMatrix() {return m_matrix;}
	
	void setWidth(int width) {m_width=width;}
	void setHeight(int height) {m_height=height;}
	int getWidth() {return m_width;}
	int getHeight() {return m_height;}
	
	void setDataFormat(int format) {m_dataFormat=format;}
	int getDataFormat() {return m_dataFormat;}
	
	void setData(char *data);
	char *getData() {return m_data;}
	
	float getImageX();
	float getImageY();
	float getImageXScale();
	float getImageYScale();

private:
	Svg2DMatrix *m_matrix;
	int m_width;
	int m_height;
	
	int m_dataFormat;
	char *m_data;

};

#endif


