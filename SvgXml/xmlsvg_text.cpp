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
#include "xmlsvg_text.h"
#include "svgConfig.h"
#include "xmlsvg_tspan.h"
#include "SvgGroup.h"

XmlSvg_text::XmlSvg_text()
{
}

XmlSvg_text::~XmlSvg_text()
{
}

bool XmlSvg_text::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	bool success=false;
	char *attr;
	XmlNodeList list;
	XmlElement subnode;
	int i;
	int linecount;
	SvgTextEntry *entry;
	int subnodecount;
	

	entry=new SvgTextEntry();
	
	if (strcmp(xmlmgr->ElementGetName(element),"text")==0)
	{
		Svg2DMatrix *matrix;
		
		success=true;
		
		matrix=new Svg2DMatrix();
		attr=xmlmgr->ElementGetAttribute(element,"transform");

		if (attr!=NULL)
		{
			if (!matrix->initFromText(attr))
			{
				delete matrix;
				success=false;
			}
		}
		
		if (success)
		{
			entry->setMatrix(matrix);
			
			linecount=0;
			list=xmlmgr->ElementGetChildList(element);
			subnodecount=xmlmgr->NodelistGetLength(list);
			xmlmgr->FreeChildList(list);			
			
			if (subnodecount==0)
			{
				SvgTextLine *line;
				
				entry->setNumTextLines(1);
				line=new SvgTextLine();
				line->setText(xmlmgr->ElementGetText(element));
				
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
				entry->setTextLine(0,line);
			}
			else
			{
				list=xmlmgr->ElementGetChildList(element);

				for (i=0;i<xmlmgr->NodelistGetLength(list);i++)
				{
					if (success)
					{
						subnode=xmlmgr->NodelistGetElement(list,i);
						if (strcmp(xmlmgr->ElementGetName(subnode),"tspan")==0)
						{
							linecount++;
						}
					}
				}
				
				//allocate number of lines
				entry->setNumTextLines(linecount);
				
				for (i=0;i<xmlmgr->NodelistGetLength(list);i++)
				{
					if (success)
					{
						SvgTextLine *line;
						
						line=new SvgTextLine();
						
						subnode=xmlmgr->NodelistGetElement(list,i);
						if (strcmp(xmlmgr->ElementGetName(subnode),"tspan")==0)
						{
							XmlSvg_tspan tspan;
							
							success=tspan.readFromXML(xmlmgr, line, subnode);
						}

						entry->setTextLine(i,line);
					}
				}
				xmlmgr->FreeChildList(list);			
			}
		}
		
		success=true;
		
	}
	
	if (success)
	{
		config->addEntry(entry);
	}
	else
	{
		delete entry;
	}

	
	return success;
}

