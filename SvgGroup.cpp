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

#include "svg_common.h"
#include "SvgGroup.h"
#include "SvgColour.h"

SvgGroup::SvgGroup()
{
	m_type=SvgEntity::TYPE_GROUP;
	m_name=NULL;
	
	m_numEntries=0;
	m_entries=NULL;
	
	m_numDefs=0;
	m_defs=NULL;
	
	m_next=NULL;
	
	m_defaultStrokeColour=NULL;
	m_defaultFillColour=getColourFromAttribute("#000000");
}


SvgGroup::~SvgGroup()
{
	SvgEntity *tcurr;
	SvgEntity *tnext;
	SvgDef *dcurr;
	SvgDef *dnext;

	if (m_name)
	{
		delete m_name;
	}
	
	tcurr=m_entries;
	while(tcurr)
	{
		tnext=tcurr->m_next;
		delete tcurr;
		tcurr=tnext;
	}
	dcurr=m_defs;
	while(dcurr)
	{
		dnext=(SvgDef *)dcurr->m_next;
		delete dcurr;
		dcurr=dnext;
	}	
	
	if (m_defaultStrokeColour)
	{
		delete m_defaultStrokeColour;
	}
	if (m_defaultFillColour)
	{
		delete m_defaultFillColour;
	}
}



void SvgGroup::resetDefaults()
{
	
	if (m_defaultStrokeColour)
	{
		delete m_defaultStrokeColour;
	}
	if (m_defaultFillColour)
	{
		delete m_defaultFillColour;
	}
	
	
	m_defaultStrokeColour=NULL;
	m_defaultFillColour=getColourFromAttribute("#000000");
	
	
}

void SvgGroup::setName(char *name)
{
	if (m_name)
	{
		delete m_name;
		m_name=NULL;
	}
	
	if (name)
	{
		m_name=strdup(name);
	}
}


void SvgGroup::addEntry(SvgEntity *entry)
{
	SvgEntity *curr;
	SvgEntity *prev;
	
	curr=m_entries;
	prev=NULL;
	
	while(curr)
	{
		prev=curr;
		curr=curr->m_next;
	}
	
	if (prev==NULL)
	{
		m_entries=entry;
	}
	else
	{
		prev->m_next=entry;
	}
	
	m_numEntries++;
}


SvgEntity *SvgGroup::getEntry(int index)
{
	if (index>=0 && index<m_numEntries)
	{
		SvgEntity *curr;
		int count;
		
		count=0;
		curr=m_entries;
		while(curr)
		{
			if (count==index)
			{
				return curr;
			}
			curr=curr->m_next;
			count++;
		}
	}
	
	return NULL;
}

void SvgGroup::addDef(SvgDef *def)
{
	SvgDef *curr;
	SvgDef *prev;
	
	curr=m_defs;
	prev=NULL;
	
	while(curr)
	{
		prev=curr;
		curr=(SvgDef *)curr->m_next;
	}
	
	if (prev==NULL)
	{
		m_defs=def;
	}
	else
	{
		prev->m_next=def;
	}
	
	m_numDefs++;
}


SvgDef *SvgGroup::getDef(int index)
{
	if (index>=0 && index<m_numDefs)
	{
		SvgDef *curr;
		int count;
		
		count=0;
		curr=m_defs;
		while(curr)
		{
			if (count==index)
			{
				return curr;
			}
			curr=(SvgDef *)curr->m_next;
			count++;
		}
	}
	
	return NULL;
}


SvgDef *SvgGroup::getDefByName(const char *name)
{
	int i;
	
	for (i=0;i<m_numDefs;i++)
	{
		SvgDef *def;
		
		def=getDef(i);
		
		if (strcmp(def->getId(),name)==0)
		{
			return def;
		}
	}
	
	return NULL;
}



SvgColour *SvgGroup::getColourFromAttribute(const char *attr)
{
	SvgColour *col=NULL;
	char *colString;
	unsigned int rgb;
	
	if (attr)
	{
		if (strcmp(attr,"none")!=0)
		{
			if (attr[0]=='#')
			{
				colString=new char[strlen(attr)+1+1];
				strcpy(colString,"0x");
				strcat(colString,attr+1);
				
				if (sscanf(colString,"%x",&rgb)==1)
				{
					col=new SvgColour();
					col->setSolid(rgb);
				}
				
				delete colString;
			}
			else
			{
				if (strncmp(attr,"url(#",strlen("url(#"))==0)
				{
					char *end=strrchr(attr,')');
					int len;
					
					if (end)
					{
						len=(end-(attr+strlen("url(#")));
						colString=new char[len+1];
						
						strncpy(colString,attr+strlen("url(#"),len);
						colString[len]=0;
						
						SvgDef *def;
						
						def=getDefByName(colString);
						
						if (def)
						{
							if (def->getEntity()->getType()==SvgEntity::TYPE_COLOUR)
							{
								col=((SvgColour*)def->getEntity())->copy();
							}
						}
						
						delete colString;
					}
				}
			}
		}
	}
	
	return col;
}


void SvgGroup::setDefaultStrokeColour(SvgColour *colour)
{
	if (m_defaultStrokeColour)
	{
		delete m_defaultStrokeColour;
		m_defaultStrokeColour=NULL;
	}
	
	if (colour)
	{
		m_defaultStrokeColour=colour->copy();
	}
}


void SvgGroup::setDefaultFillColour(SvgColour *colour)
{
	if (m_defaultFillColour)
	{
		delete m_defaultFillColour;
		m_defaultFillColour=NULL;
	}
	
	if (colour)
	{
		m_defaultFillColour=colour->copy();
	}
}

SvgColour *SvgGroup::getDefaultStrokeColour()
{
	if (m_defaultStrokeColour)
	{
		return m_defaultStrokeColour->copy();
	}
	
	return NULL;
}

SvgColour *SvgGroup::getDefaultFillColour()
{
	if (m_defaultFillColour)
	{
		return m_defaultFillColour->copy();
	}
	
	return NULL;	
}


