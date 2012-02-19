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
#ifndef __DDXMLMGR_H__
#define __DDXMLMGR_H__

#include "tinyxml.h"

typedef TiXmlElement *XmlElement;

struct _ddnodelist
{
	int m_length;
	TiXmlNode **m_list;
};

typedef _ddnodelist *XmlNodeList;

class DDXmlMgr
{
public:
	DDXmlMgr();
	~DDXmlMgr();
	
	bool Initialise();
	
	// document access methods
	bool DocLoad(const char *filename);
	XmlElement DocGetRoot();
	
	// element access methods
	char *ElementGetName(XmlElement pNode);
	char *ElementGetText(XmlElement pElement);
	char *ElementGetAttribute(XmlElement element,char *attr);
	XmlNodeList ElementGetChildList(XmlElement pNode);
	void FreeChildList(XmlNodeList list);
	
	// node list access methods
	int NodelistGetLength(XmlNodeList list);
	XmlElement NodelistGetElement(XmlNodeList list,int index);
	void NodelistRelease(XmlNodeList list);
	
	int ElementGetLine(XmlElement pElement);
	
private:
	void Release();
	
	TiXmlDocument *m_XMLDocument;


};

#endif



