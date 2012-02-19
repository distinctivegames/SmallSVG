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
#include "xmlsvg_lineargradient.h"
#include "svgConfig.h"
#include "SvgGroup.h"
#include "SvgColour.h"
#include "SvgDef.h"


XmlSvg_linearGradient::XmlSvg_linearGradient()
{
}

XmlSvg_linearGradient::~XmlSvg_linearGradient()
{
}

bool XmlSvg_linearGradient::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	char *colStr;
	char *attr1;
	char *attr2;
	char *attr3;
	char *attr4;
	char *attr;
	bool success=false;
	float x1,y1,x2,y2;
	XmlNodeList list;
	XmlElement subnode;
	int i;
	int count;
	int stop;
	
	if (strcmp(xmlmgr->ElementGetName(element),"linearGradient")==0)
	{
		attr=xmlmgr->ElementGetAttribute(element,"id");
		if (attr)
		{
			SvgDef *def;
			SvgColour *colour;

			success=true;
			
			def=new SvgDef();
			def->setId(attr);
			
			colour=new SvgColour();
			
			attr1=xmlmgr->ElementGetAttribute(element,"x1");
			attr2=xmlmgr->ElementGetAttribute(element,"y1");
			attr3=xmlmgr->ElementGetAttribute(element,"x2");
			attr4=xmlmgr->ElementGetAttribute(element,"y2");
		
			if (attr1)
			{
				sscanf(attr1,"%f",&x1);
			}
			if (attr2)
			{
				sscanf(attr2,"%f",&y1);
			}
			if (attr3)
			{
				sscanf(attr3,"%f",&x2);
			}
			if (attr4)
			{
				sscanf(attr4,"%f",&y2);
			}
			
			
			count=0;
			list=xmlmgr->ElementGetChildList(element);
			for (i=0;i<xmlmgr->NodelistGetLength(list);i++)
			{
				if (success)
				{
					subnode=xmlmgr->NodelistGetElement(list,i);
					
					if (strcmp(xmlmgr->ElementGetName(subnode),"stop")==0)
					{
						count++;
					}
				}
			}
			xmlmgr->FreeChildList(list);

			colour->setGradient(x1,y1,x2,y2,count);
			
			stop=0;
			list=xmlmgr->ElementGetChildList(element);
			for (i=0;i<xmlmgr->NodelistGetLength(list);i++)
			{
				if (success)
				{
					subnode=xmlmgr->NodelistGetElement(list,i);
					
					if (strcmp(xmlmgr->ElementGetName(subnode),"stop")==0)
					{
						float location=0;
						unsigned int col=0;
						
						
						attr1=xmlmgr->ElementGetAttribute(subnode,"offset");
						attr2=xmlmgr->ElementGetAttribute(subnode,"style");
						
						if (attr1)
						{
							if (sscanf(attr1,"%f",&location)!=1)
							{
								success=false;
							}
						}
						else
						{
							success=false;
						}

						
						if (attr2)
						{
							if (strncmp(attr2,"stop-color:#",strlen("stop-color:#"))==0)
							{
								colStr=new char[(strlen(attr2)-strlen("stop-color:#"))+1+2];
								strcpy(colStr,"0x");
								strcat(colStr,attr2+strlen("stop-color:#"));
								if (sscanf(colStr,"%x",&col)!=1)
								{
									success=false;
								}
								delete colStr;
							}
						}
						else
						{
							success=false;
						}

						if (success)
						{
							colour->setGradientStop(stop,location,col);
						}
						
						stop++;
					}
				}
			}
			xmlmgr->FreeChildList(list);
			
			
			if (success)
			{
				def->setEntity(colour);
				config->addDef(def);
			}
			else
			{
				delete def;
				delete colour;
			}
		}
	}
	
	return success;
}

