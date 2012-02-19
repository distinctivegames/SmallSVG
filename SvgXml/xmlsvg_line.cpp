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
#include "xmlsvg_line.h"
#include "svgConfig.h"
#include "SvgLineSegStraight.h"
#include "SvgGroup.h"

XmlSvg_line::XmlSvg_line()
{
}

XmlSvg_line::~XmlSvg_line()
{
}

bool XmlSvg_line::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	bool success=false;
	char *attr1;
	char *attr2;
	char *attr3;
	char *attr4;
	char *strokeAttr;
	float width;
	float x1,y1,x2,y2;
	
	if (strcmp(xmlmgr->ElementGetName(element),"line")==0)
	{
		
		strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-width");
		if (strokeAttr)
		{
			if (sscanf(strokeAttr,"%f",&width)!=1)
			{
				width=1.0f;
			}
		}
		else
		{
			width=1.0f;
		}

		
		attr1=xmlmgr->ElementGetAttribute(element,"x1");
		attr2=xmlmgr->ElementGetAttribute(element,"y1");
		attr3=xmlmgr->ElementGetAttribute(element,"x2");
		attr4=xmlmgr->ElementGetAttribute(element,"y2");
		
		if (sscanf(attr1,"%f",&x1)==1 && 
			sscanf(attr2,"%f",&y1)==1 &&
			sscanf(attr3,"%f",&x2)==1 &&
			sscanf(attr4,"%f",&y2)==1)
		{
			SvgLine *line;
			SvgLineSegStraight *seg;
			
			seg=new SvgLineSegStraight();
			seg->addSegment(x1,y1,x2,y2);
			
			line=new SvgLine();
			line->setStrokeWidth(width);
			line->addSegment(seg);
			
			if (xmlmgr->ElementGetAttribute(element,"stroke")!=NULL)
			{
				line->setStrokeColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"stroke")));
			}
			else
			{
				line->setStrokeColour(config->getDefaultStrokeColour());
			}
			
			if (xmlmgr->ElementGetAttribute(element,"fill")!=NULL)
			{
				line->setFillColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"fill")));
			}
			else
			{
				line->setFillColour(config->getDefaultFillColour());
			}
			
			
			strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-dasharray");
			if (strokeAttr)
			{
				line->setStrokeDashArrayFromText(strokeAttr);
			}
			
			strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-linecap");
			if (strokeAttr)
			{
				line->setStrokeLineCap(strokeAttr);
			}
			
			line->setFillColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"fill")));
			
			config->addEntry(line);
			
			success=true;
		}
	}
	
	return success;
}

