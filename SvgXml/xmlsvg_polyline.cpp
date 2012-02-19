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
#include "xmlsvg_polyline.h"
#include "svgConfig.h"
#include "SvgLine.h"
#include "SvgLineSegStraight.h"
#include "SvgGroup.h"


XmlSvg_polyline::XmlSvg_polyline()
{
}

XmlSvg_polyline::~XmlSvg_polyline()
{
}

bool XmlSvg_polyline::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	bool success=false;
	char *attr;
	char number[256];
	float coords[4];
	int mode;
	int coord;
	int i,j;
	SvgLine *line;
	SvgLineSegStraight *seg;
	char *strokeAttr;
	float width;
	
	
#define MODE_COPYING 0	
#define MODE_SKIPPING 1	

	line=new SvgLine();

	
	if (strcmp(xmlmgr->ElementGetName(element),"polyline")==0)
	{
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
		line->setStrokeWidth(width);

		strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-linecap");
		if (strokeAttr)
		{
			line->setStrokeLineCap(strokeAttr);
		}
		
		strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-dasharray");
		if (strokeAttr)
		{
			line->setStrokeDashArrayFromText(strokeAttr);
		}
		
		attr=xmlmgr->ElementGetAttribute(element,"points");

		if (attr)
		{
			success=true;
			

			mode=MODE_COPYING;
			i=0;
			j=0;
			coord=0;
			
			//skip leading white space
			while(attr[i]!=0 && ((attr[i]<'0' || attr[i]>'9') && attr[i]!='.'))
			{
				i++;
			}
			
			while(true)
			{
				if (mode==MODE_COPYING)
				{
					if ((attr[i]>='0' && attr[i]<='9') || attr[i]=='.')
					{
						number[j]=attr[i];
						j++;
						i++;
					}
					else
					{
						number[j]=0;									//terminate string
						
						if (sscanf(number,"%f",&coords[coord])==1)		//read number
						{
							coord++;
							
							if (coord==4)
							{
								seg=new SvgLineSegStraight();
								seg->addSegment(coords[0],coords[1],coords[2],coords[3]);
								line->addSegment(seg);

								coords[0]=coords[2];					//move end of line to start of next line
								coords[1]=coords[3];
								coord=2;
							}
						}
						else
						{
							success=false;
						}

						mode=MODE_SKIPPING;
					}
				}
				else
				{
					if ((attr[i]<'0' || attr[i]>'9') && attr[i]!='.')
					{
						if (attr[i]==0)
						{
							break;
						}
						
						i++;
					}
					else
					{
						j=0;
						mode=MODE_COPYING;
					}
				}
			}
		}
	}
	
	if (success)
	{
		config->addEntry(line);
	}
	else
	{
		delete line;
	}
	
	return success;
}

