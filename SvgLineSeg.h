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
#ifndef __SVGLINESEG_H__
#define __SVGLINESEG_H__

class SvgLineSeg
{
	friend class SvgLine;
public:
	static const int TYPE_UNKNOWN			= 0; 
	static const int TYPE_STRAIGHT			= 1; 
	static const int TYPE_CUBICBEZIER		= 2; 
	static const int TYPE_QUADRATICBEZIER	= 3; 
	
public:
	SvgLineSeg();
	virtual ~SvgLineSeg();

	int getType() {return m_type;}
	
protected:
	int	m_type;
	
	SvgLineSeg *m_next;
};

#endif


