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
#ifndef __SVG2DVECTOR_H__
#define __SVG2DVECTOR_H__

class Svg2DVector
{
	friend class Svg2DMatrix;
public:
	Svg2DVector();
	~Svg2DVector();

	void setX(float x) {m_x=x;}
	void setY(float y) {m_y=y;}
	float getX() {return m_x;}
	float getY() {return m_y;}
	
private:
	float m_x;
	float m_y;
};

#endif

