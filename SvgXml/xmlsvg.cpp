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
#include "xmlsvg.h"
#include "svgConfig.h"
#include "xmlsvg_g.h"
#include "xmlsvg_path.h"

XmlSvg::XmlSvg()
{
}

XmlSvg::~XmlSvg()
{
}

bool XmlSvg::readFromXML(DDXmlMgr *xmlmgr,SvgConfig *config,XmlElement element)
{
	bool success=false;
	XmlNodeList list;
	XmlElement subnode;
	XmlNodeList sublist;
	XmlElement subsubnode;
	char *attr;
	int i,j;
    SvgGroup *svgDefaultGroup=NULL;
    
	
	if (strcmp(xmlmgr->ElementGetName(element),"svg")==0)
	{
		attr=xmlmgr->ElementGetAttribute(element,"width");
		if (attr)
		{		
			int width;
			if (sscanf(attr,"%dpx",&width)==1)
			{
				config->setWidth(width);
			}
		}

		attr=xmlmgr->ElementGetAttribute(element,"height");
		if (attr)
		{		
			int height;
			if (sscanf(attr,"%dpx",&height)==1)
			{
				config->setHeight(height);
			}
		}
		
		success=true;
		list=xmlmgr->ElementGetChildList(element);
		for (i=0;i<xmlmgr->NodelistGetLength(list);i++)
		{
			if (success)
			{
				subnode=xmlmgr->NodelistGetElement(list,i);
				
				
				/*
				if (strcmp(xmlmgr->ElementGetName(subnode),"switch")==0)
				{
					sublist=xmlmgr->ElementGetChildList(subnode);
					for (j=0;j<xmlmgr->NodelistGetLength(sublist);j++)
					{
						subsubnode=xmlmgr->NodelistGetElement(sublist,j);
					
						if (strcmp(xmlmgr->ElementGetName(subsubnode),"g")==0)
						{
							XmlSvg_g group;
							SvgGroup *svgGroup=new SvgGroup();
							
							success=group.readFromXML(xmlmgr, svgGroup,subsubnode);
							
							if (success)
							{
								config->addGroup(svgGroup);
							}
							else
							{
								delete svgGroup;
							}

						}									
					}
				}
				else 
					*/
					
					if (strcmp(xmlmgr->ElementGetName(subnode),"g")==0)
				{
					XmlSvg_g group;
					SvgGroup *svgGroup=new SvgGroup();
					
					success=group.readFromXML(xmlmgr, svgGroup,subnode);
					
					if (success)
					{
						config->addGroup(svgGroup);
					}
					else
					{
						delete svgGroup;
					}

				}	
                else if (strcmp(xmlmgr->ElementGetName(subnode),"path")==0)
                {
					XmlSvg_path path;
					
                    if (svgDefaultGroup==NULL)
                    {
                        svgDefaultGroup=new SvgGroup();
                        config->addGroup(svgDefaultGroup);
                    }
					
					success=path.readFromXML(xmlmgr, svgDefaultGroup, subnode);
                }
			}
		}
		xmlmgr->FreeChildList(list);

	}
	
	return success;
}

