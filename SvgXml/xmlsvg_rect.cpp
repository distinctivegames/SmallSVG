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
#include "xmlsvg_rect.h"
#include "svgConfig.h"
#include "SvgLineSegStraight.h"
#include "SvgGroup.h"
#include "SvgRect.h"

XmlSvg_rect::XmlSvg_rect()
{
}

XmlSvg_rect::~XmlSvg_rect()
{
}

bool XmlSvg_rect::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	bool success=false;
	char *attr1;
	char *attr2;
	char *attr3;
	char *attr4;
	float width,height;
	float x,y;
	char *blank="0";
	
	if (strcmp(xmlmgr->ElementGetName(element),"rect")==0)
	{		
		attr1=xmlmgr->ElementGetAttribute(element,"x");
		attr2=xmlmgr->ElementGetAttribute(element,"y");
		attr3=xmlmgr->ElementGetAttribute(element,"width");
		attr4=xmlmgr->ElementGetAttribute(element,"height");
		
		if (attr1==NULL)
		{
			attr1=blank;
		}
		if (attr2==NULL)
		{
			attr2=blank;
		}
		
		if (sscanf(attr1,"%f",&x)==1 && 
			sscanf(attr2,"%f",&y)==1 &&
			sscanf(attr3,"%f",&width)==1 &&
			sscanf(attr4,"%f",&height)==1)
		{
			SvgRect *rect;
			
			rect=new SvgRect();
			rect->setRect(x,y,width,height);
			
			if (xmlmgr->ElementGetAttribute(element,"stroke")!=NULL)
			{
				rect->setStrokeColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"stroke")));
			}
			else
			{
				rect->setStrokeColour(config->getDefaultStrokeColour());
			}
			
			if (xmlmgr->ElementGetAttribute(element,"fill")!=NULL)
			{
				rect->setFillColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"fill")));
			}
			else
			{
				rect->setFillColour(config->getDefaultFillColour());
			}
			
			config->addEntry(rect);
			
			success=true;
		}
	}
	
	return success;
}

