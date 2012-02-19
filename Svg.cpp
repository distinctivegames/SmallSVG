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

#include "Svg.h"
#include "DDXmlMgr.h"
#include "SvgConfig.h"
#include "xmlsvg.h"


// DONE Add fill & stroke to path/line
// DONE add stroke width to line
// DONE Add 'defs' element
// DONE add linear gradient as implicit def
// Add 'rect' element


Svg::Svg()
{
	m_config=NULL;
}

Svg::~Svg()
{
	if (m_config)
	{
		delete m_config;
	}
}

bool Svg::loadFile(const char *filename)
{
	DDXmlMgr xmlmgr;
	XmlSvg parser;
	bool success=false;
	
	if (xmlmgr.Initialise())
	{
		if (xmlmgr.DocLoad(filename))
		{
			SvgConfig *config=new SvgConfig();
			
			if (parser.readFromXML(&xmlmgr, config, xmlmgr.DocGetRoot()))
			{
				m_config=config;
				success=true;
			}
			else
			{
				delete config;
			}
		}
	}
	
	return success;
}


int Svg::getNumGroups()
{
	return m_config->getNumGroups();
}

SvgGroup *Svg::getGroupByIndex(int index)
{
	if (index>=0 && index<m_config->getNumGroups())
	{
		return m_config->getGroupByIndex(index);
	}
	return NULL;
}

	

SvgGroup *Svg::getGroupByName(const char *name)
{
	SvgGroup *group;
	int num;
	int i;
	
	num=m_config->getNumGroups();
	for (i=0;i<num;i++)
	{
		group=m_config->getGroupByIndex(i);
		
		if (strcmp(group->getName(),name)==0)
		{
			return group;
		}
	}

	return NULL;
}


