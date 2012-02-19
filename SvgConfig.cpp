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
#include "SvgConfig.h"
#include "SvgGroup.h"
#include "SvgColour.h"

SvgConfig::SvgConfig()
{
	m_width=0;
	m_height=0;
	m_numGroups=0;
	m_groupHead=NULL;
}


SvgConfig::~SvgConfig()
{
	//delete group list here
	SvgEntity *curr;
	SvgEntity *next;
	
	curr=m_groupHead;
	while(curr)
	{
		next=curr->m_next;
		delete curr;
		curr=next;
	}
}

void SvgConfig::addGroup(SvgGroup *entry)
{
	SvgEntity *curr;
	SvgEntity *prev;
	
	curr=m_groupHead;
	prev=NULL;
	
	while(curr)
	{
		prev=curr;
		curr=curr->m_next;
	}
	
	if (prev==NULL)
	{
		m_groupHead=entry;
	}
	else
	{
		prev->m_next=entry;
	}
	
	m_numGroups++;
}


SvgGroup *SvgConfig::getGroupByIndex(int index)
{
	SvgEntity *curr;
	int currIndex;
	
	if (index>=0 && index<m_numGroups)
	{
		currIndex=0;
		curr=m_groupHead;
		while(curr)
		{
			if (index==currIndex)
			{
				return (SvgGroup*)curr;
			}
			curr=curr->m_next;
			currIndex++;
		}		
	}
	
	return NULL;
}






