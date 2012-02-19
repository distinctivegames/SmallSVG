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
#ifndef __SVGENTITY_H__
#define __SVGENTITY_H__

class SvgEntity
{
	friend class SvgConfig;
	friend class SvgGroup;
	
public:
	static const int TYPE_UNKNOWN	= 0;
	static const int TYPE_GROUP		= 1;
	static const int TYPE_PATH		= 2;
	static const int TYPE_TEXT		= 3;
	static const int TYPE_IMAGE		= 4;
	static const int TYPE_COLOUR	= 5;
	static const int TYPE_DEF		= 6;
	static const int TYPE_RECT		= 7;
	
public:
	SvgEntity();
	virtual ~SvgEntity();
	
	int getType() {return m_type;}
	void setType(int type) {m_type=type;}
	
protected:
	int m_type;
	
protected:
	SvgEntity *m_next;
	
};

#endif

