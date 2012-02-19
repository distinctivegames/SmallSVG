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
#include "xmlsvg_image.h"
#include "svgConfig.h"
#include "SvgGroup.h"
#include "Svg2DMatrix.h"


XmlSvg_image::XmlSvg_image()
{
}

XmlSvg_image::~XmlSvg_image()
{
}

bool XmlSvg_image::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	char *base64JpegID="data:image/jpeg;base64,";
	char *attr1;
	char *attr2;
	char *attr3;
	char *attrData;
	Svg2DMatrix *matrix;
	int width,height;
	bool success=false;
	
	if (strcmp(xmlmgr->ElementGetName(element),"image")==0)
	{
		attr1=xmlmgr->ElementGetAttribute(element,"width");
		attr2=xmlmgr->ElementGetAttribute(element,"height");
		attrData=xmlmgr->ElementGetAttribute(element,"xlink:href");
		
		if (attr1!=NULL && attr2!=NULL && attrData!=NULL)
		{
			if (sscanf(attr1,"%d",&width)==1 && sscanf(attr2,"%d",&height)==1 && strncmp(attrData,base64JpegID,strlen(base64JpegID))==0)
			{
				SvgImage *svgImage;
				
				success=true;
				
				matrix=new Svg2DMatrix();
				attr3=xmlmgr->ElementGetAttribute(element,"transform");
				
				if (attr3!=NULL)
				{
					if (!matrix->initFromText(attr3))
					{
						delete matrix;
						success=false;
					}
				}
				if (success)
				{
					svgImage=new SvgImage();
					
					svgImage->setMatrix(matrix);
					
					svgImage->setWidth(width);
					svgImage->setHeight(height);
					
					svgImage->setDataFormat(SvgImage::DATAFORMAT_BASE64JPEG);
					svgImage->setData(attrData+strlen(base64JpegID));
					
					config->addEntry(svgImage);
				}
			}
		}
	}
	
	return success;
}

