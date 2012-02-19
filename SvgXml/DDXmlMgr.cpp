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
#include "DDXmlMgr.h"

DDXmlMgr::DDXmlMgr()
{
	m_XMLDocument=NULL;
}

DDXmlMgr::~DDXmlMgr()
{
	Release();
}

void DDXmlMgr::Release()
{
	if (m_XMLDocument)
	{
		delete m_XMLDocument;
		m_XMLDocument=NULL;
	}
}

bool DDXmlMgr::Initialise()
{
	return true;
}

// document access methods
bool DDXmlMgr::DocLoad(const char *filename)
{
	Release();
	
	
	TiXmlBase::SetCondenseWhiteSpace(false);
	
	m_XMLDocument=new TiXmlDocument(filename);
	
	return m_XMLDocument->LoadFile();
}

XmlElement DDXmlMgr::DocGetRoot()
{
	if (m_XMLDocument)
	{
		return (XmlElement)m_XMLDocument->RootElement();
	}
	else
	{
		return NULL;
	}
}


char *DDXmlMgr::ElementGetName(XmlElement pNode)
{
	return (char *)pNode->Value();
}

char *DDXmlMgr::ElementGetText(XmlElement pElement)
{
	return (char *)pElement->GetText();
}

char *DDXmlMgr::ElementGetAttribute(XmlElement element,char *attr)
{
	return (char *)element->Attribute(attr);
}

XmlNodeList DDXmlMgr::ElementGetChildList(XmlElement pNode)
{
	XmlNodeList list;
	TiXmlNode *pChild;
	int idx;
	
	list=new _ddnodelist;
	list->m_length=0;
	for ( pChild = pNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		if (pChild->Type()==TiXmlNode::ELEMENT)
		{
			list->m_length++;
		}
	}

	if (list->m_length>0)
	{
		list->m_list=new TiXmlNode*[list->m_length];
		
		idx=0;
		for ( pChild = pNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
		{
			if (pChild->Type()==TiXmlNode::ELEMENT)
			{
				list->m_list[idx]=pChild;
				idx++;
			}
		}
	}
	else
	{
		list->m_list=NULL;
	}
	
	
	return list;
}


void DDXmlMgr::FreeChildList(XmlNodeList list)
{
	if (list==NULL)
	{
		return;
	}
	
	if (list->m_list!=NULL)
	{
		delete list->m_list;
	}
	
	delete list;
}

// node list access methods
int DDXmlMgr::NodelistGetLength(XmlNodeList list)
{
	if (list)
	{
		return list->m_length;
	}
	else
	{
		return 0;
	}
}

XmlElement DDXmlMgr::NodelistGetElement(XmlNodeList list,int index)
{
	if (list && list->m_length>0 && index<list->m_length)
	{
		return (TiXmlElement *)list->m_list[index];
	}
	else
	{
		return NULL;
	}
}

void DDXmlMgr::NodelistRelease(XmlNodeList list)
{
	if (list)
	{
		if (list->m_list)
		{
			delete list->m_list;
		}
		delete list;
	}
}

int DDXmlMgr::ElementGetLine(XmlElement pElement)
{
	if (pElement)
	{
		return pElement->Row();
	}
	return 0;
}



