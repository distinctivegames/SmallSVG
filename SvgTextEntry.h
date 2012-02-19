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
#ifndef __SVGTEXTENTRY_H__
#define __SVGTEXTENTRY_H__

#include "Svg2DMatrix.h"
#include "SvgTextLine.h"
#include "SvgEntity.h"

class SvgTextEntry : public SvgEntity
{
public:
	SvgTextEntry();
	~SvgTextEntry();

	void setMatrix(Svg2DMatrix *matrix);
	Svg2DMatrix *getMatrix() {return m_matrix;}

	void setNumTextLines(int num);
	int getNumTextLines() {return m_numTextLines;}
	
	void setTextLine(int index,SvgTextLine *line);
	SvgTextLine *getTextLine(int index);

	float getTextLineX(int lineIndex);
	float getTextLineY(int lineIndex);
	
private:
	Svg2DMatrix *m_matrix;
	
	int m_numTextLines;
	SvgTextLine **m_textLines;
};


#endif


