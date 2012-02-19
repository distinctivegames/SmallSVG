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

#ifndef __SVGDEF_H__
#define __SVGDEF_H__

#include "SvgEntity.h"

class SvgDef : public SvgEntity
{
public:
	SvgDef();
	~SvgDef();
	
	void setId(const char *ident);
	char *getId() {return m_id;}
	
	void setEntity(SvgEntity *entity);
	SvgEntity *getEntity() {return m_entity;}
	
private:
	char *m_id;
	
	SvgEntity *m_entity;
};


#endif

