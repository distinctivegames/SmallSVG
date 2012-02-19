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

#ifndef __SVGCONFIG_H__
#define __SVGCONFIG_H__

#include "SvgGroup.h"
#include "SvgEntity.h"

class SvgColour;

class SvgConfig
{
public:
	SvgConfig();
	~SvgConfig();

	void addGroup(SvgGroup *group);
	
	int getNumGroups() {return m_numGroups;}
	SvgGroup *getGroupByIndex(int index);
	
	void setWidth(int width) {m_width=width;}
	void setHeight(int height) {m_height=height;}
	int getWidth() {return m_width;}
	int getHeight() {return m_height;}
	
private:
	int m_width;
	int m_height;
	
	int m_numGroups;
	SvgEntity *m_groupHead;
};



#endif


