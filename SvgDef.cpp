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
#include "SvgDef.h"

SvgDef::SvgDef()
{
	m_type=TYPE_DEF;
	m_id=NULL;
	m_entity=NULL;
}

SvgDef::~SvgDef()
{
	if (m_id)
	{
		delete m_id;
	}
	if (m_entity)
	{
		delete m_entity;
	}
}

void SvgDef::setId(const char *ident)
{
	if (m_id)
	{
		delete m_id;
		m_id=NULL;
	}
	
	if (ident)
	{
		m_id=strdup(ident);
	}
}

void SvgDef::setEntity(SvgEntity *entity)
{
	if (m_entity)
	{
		delete m_entity;
		m_entity=NULL;
	}
	
	if (entity)
	{
		m_entity=entity;
	}
}



