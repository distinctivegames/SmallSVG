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

#ifndef __SVG_H__
#define __SVG_H__

#include "SvgConfig.h"
#include "SvgEntity.h"
#include "SvgGroup.h"

#include "SvgColour.h"

#include "SvgRect.h"

#include "SvgLine.h"
#include "SvgLineSeg.h"
#include "SvgLineSegStraight.h"
#include "SvgLineSegCubicBezier.h"
#include "SvgLineSegQuadraticBezier.h"

#include "SvgTextEntry.h"
#include "SvgTextLine.h"

#include "SvgImage.h"



class Svg
{
public:
	Svg();
	~Svg();
	
	bool loadFile(const char *filename);
	
	int getNumGroups();
	SvgGroup *getGroupByIndex(int index);
	SvgGroup *getGroupByName(const char *name);
	
	int getWidth() {return m_config->getWidth();}
	int getHeight() {return m_config->getHeight();}
	
private:
	SvgConfig *m_config;
};	
	

#endif

