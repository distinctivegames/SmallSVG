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

#ifndef __SVGTEXTLINE_H__
#define __SVGTEXTLINE_H__

class SvgTextLine
{
public:
	SvgTextLine();
	~SvgTextLine();

	void setXFromText(char *text);
	void setYFromText(char *text);
	void setFontSizeFromText(char *text);
	
	void setX(float x);
	void setY(float y);
	void setFontName(char *font);
	void setFontSize(float size);
	void setText(char *text);
	
	float getX() {return m_x;}
	float getY() {return m_y;}
	char *getFontName() {return m_fontName;}
	float getFontSize() {return m_fontSize;}
	char *getText() {return m_text;}
	
private:
	float m_x;
	float m_y;
	char *m_fontName;
	float m_fontSize;
	char *m_text;
};


#endif

