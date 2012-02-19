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
#include "xmlsvg_g.h"
#include "svgConfig.h"
#include "xmlsvg_image.h"
#include "xmlsvg_text.h"
#include "xmlsvg_line.h"
#include "xmlsvg_path.h"
#include "xmlsvg_rect.h"
#include "xmlsvg_polyline.h"
#include "xmlsvg_lineargradient.h"
#include "SvgGroup.h"

XmlSvg_g::XmlSvg_g()
{
}

XmlSvg_g::~XmlSvg_g()
{
}

bool XmlSvg_g::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	bool success=false;
	XmlNodeList list;
	XmlElement subnode;
	char *attr;
	int i;
	
	
	if (strcmp(xmlmgr->ElementGetName(element),"g")==0)
	{
		
		attr=xmlmgr->ElementGetAttribute(element,"id");
		if (attr)
		{
			config->setName(attr);
		}
		
		success=true;
		list=xmlmgr->ElementGetChildList(element);
		for (i=0;i<xmlmgr->NodelistGetLength(list);i++)
		{
			if (success)
			{
				subnode=xmlmgr->NodelistGetElement(list,i);
				
				if (strcmp(xmlmgr->ElementGetName(subnode),"g")==0)
				{
					XmlSvg_g group;
					
					config->resetDefaults();
					success=group.readFromXML(xmlmgr, config,subnode);
				}		
				else if (strcmp(xmlmgr->ElementGetName(subnode),"image")==0)
				{
					XmlSvg_image image;
					
					success=image.readFromXML(xmlmgr, config, subnode);
				}
				else if (strcmp(xmlmgr->ElementGetName(subnode),"text")==0)
				{
					XmlSvg_text text;
					
					success=text.readFromXML(xmlmgr, config, subnode);
				}
				else if (strcmp(xmlmgr->ElementGetName(subnode),"line")==0)
				{
					XmlSvg_line line;
					
					success=line.readFromXML(xmlmgr, config, subnode);
				}
				else if (strcmp(xmlmgr->ElementGetName(subnode),"path")==0)
				{
					XmlSvg_path path;
					
					success=path.readFromXML(xmlmgr, config, subnode);
				}
				else if (strcmp(xmlmgr->ElementGetName(subnode),"polyline")==0)
				{
					XmlSvg_polyline polyline;
					
					success=polyline.readFromXML(xmlmgr, config, subnode);
				}
				else if (strcmp(xmlmgr->ElementGetName(subnode),"linearGradient")==0)
				{
					XmlSvg_linearGradient gradient;
					
					success=gradient.readFromXML(xmlmgr,config,subnode);
				}
				else if (strcmp(xmlmgr->ElementGetName(subnode),"rect")==0)
				{
					XmlSvg_rect rect;
					
					success=rect.readFromXML(xmlmgr, config, subnode);
				}
			}
		}	
		xmlmgr->FreeChildList(list);

	}
	
	return success;
}

