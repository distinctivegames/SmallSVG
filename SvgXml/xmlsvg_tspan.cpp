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
#include "xmlsvg_tspan.h"
#include "svgConfig.h"


XmlSvg_tspan::XmlSvg_tspan()
{
}

XmlSvg_tspan::~XmlSvg_tspan()
{
}

bool XmlSvg_tspan::readFromXML(DDXmlMgr *xmlmgr,SvgTextLine *line,XmlElement element)
{
	char *attr;
	bool success=false;
	
	if (strcmp(xmlmgr->ElementGetName(element),"tspan")==0)
	{
		success=true;
		
		attr=xmlmgr->ElementGetAttribute(element,"x");
		if (attr)
		{
			line->setXFromText(attr);
		}
		attr=xmlmgr->ElementGetAttribute(element,"y");
		if (attr)
		{
			line->setYFromText(attr);
		}
		attr=xmlmgr->ElementGetAttribute(element,"font-size");
		if (attr)
		{
			line->setFontSizeFromText(attr);
		}
		attr=xmlmgr->ElementGetAttribute(element,"font-family");
		if (attr)
		{
			line->setFontName(attr);
		}		
		
		line->setText(xmlmgr->ElementGetText(element));
	}
	
	return success;
}

