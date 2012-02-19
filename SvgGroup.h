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
#ifndef __SVGGROUP_H__
#define __SVGGROUP_H__

#include "Svg2DMatrix.h"
#include "SvgTextEntry.h"
#include "SvgLine.h"
#include "SvgImage.h"
#include "SvgEntity.h"
#include "SvgDef.h"

class SvgGroup : public SvgEntity
{
	friend class SvgConfig;
public:
	SvgGroup();
	~SvgGroup();
	
	void setName(char *name);
	char *getName() {return m_name;} 
	
	void addEntry(SvgEntity *entry);
	
	int getNumEntries() {return m_numEntries;}
	SvgEntity *getEntry(int index);
	
	
	void addDef(SvgDef *def);
	
	int getNumDefs() {return m_numDefs;}
	SvgDef *getDef(int index);
	SvgDef *getDefByName(const char *name);
	
	SvgColour *getColourFromAttribute(const char *attr);
	
	
	void resetDefaults();
	
	void setDefaultStrokeColour(SvgColour *colour);
	void setDefaultFillColour(SvgColour *colour);
	SvgColour *getDefaultStrokeColour();
	SvgColour *getDefaultFillColour();

private:
	SvgColour *m_defaultStrokeColour;
	SvgColour *m_defaultFillColour;
	
	char *m_name;
	
	int m_numEntries;
	SvgEntity *m_entries;
	
	int m_numDefs;
	SvgDef *m_defs;
};



#endif


