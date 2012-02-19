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
#include "xmlsvg_path.h"
#include "svgConfig.h"
#include "SvgLineSegStraight.h"
#include "SvgLineSegCubicBezier.h"
#include "SvgLineSegQuadraticBezier.h"
#include "SvgGroup.h"

XmlSvg_path::XmlSvg_path()
{
}

XmlSvg_path::~XmlSvg_path()
{
}

int XmlSvg_path::dataSkipWhitespace(char *data,int index)
{
	while(data[index]==' ' ||
		  data[index]==',' ||
		  data[index]=='\t' ||
		  data[index]=='\n' ||
		  data[index]=='\r')
	{
		index++;
	}
	
	return index;
}


int XmlSvg_path::dataGetCommand(char *data,int index,char prevCommand,char *command)
{
	char comm;
	
	index=dataSkipWhitespace(data,index);
	
	if (data[index]==0)
	{
		return -1;
	}
	
	comm=data[index];
	
	if (comm=='M' || comm=='m' ||
		comm=='Z' || comm=='z' ||
		comm=='L' || comm=='l' ||
		comm=='H' || comm=='h' ||
		comm=='V' || comm=='v' ||
		comm=='C' || comm=='c' ||
		comm=='S' || comm=='s' ||
		comm=='Q' || comm=='q' ||
		comm=='T' || comm=='t' ||
		comm=='A' || comm=='a')
	{
		*command=comm;
		index++;
	}
	else if ((comm>='0' && comm<='9') || comm=='-')
	{
		*command=prevCommand;
	}
	else
	{
		*command='?';
	}
	
	return index;
}

int XmlSvg_path::dataReadNumber(char *data,int index,float *value)
{
	bool negative=false;
	char number[256];
	int j;
	
	
	index=dataSkipWhitespace(data,index);
	
	if (data[index]=='-')
	{
		negative=true;
		index++;
	}
	
	j=0;
	while((data[index]!=0 && data[index]>='0' && data[index]<='9') || data[index]=='.')
	{
		number[j]=data[index];
		j++;
		index++;
	}
	
	number[j]=0;
	
	if (sscanf(number,"%f",value)!=1)
	{
		*value=-1;
	}
	else
	{
		if (negative)
		{
			*value=-(*value);
		}
	}

	
	return index;
}


bool XmlSvg_path::readFromXML(DDXmlMgr *xmlmgr,SvgGroup *config,XmlElement element)
{
	bool success=false;
	char *attr;
	int index;
	char command;
	float initialX,initialY;
	float currX,currY;
	float endX,endY;
	float control1X,control1Y;
	float control2X,control2Y;
	float prevControlX,prevControlY;
	SvgLine *line;
	SvgLineSegStraight *straightSeg;
	SvgLineSegCubicBezier *cubicSeg;
	SvgLineSegQuadraticBezier *quadSeg;
	char *strokeAttr;
	float width;
	char key[256];
	char value[256];
	
	line=new SvgLine();
	
	if (strcmp(xmlmgr->ElementGetName(element),"path")==0)
	{
		attr=xmlmgr->ElementGetAttribute(element,"style");
        if (attr!=NULL)
		{
            int styleidx=0;
            int stylemode=0;
            int keyidx=0;
            int valueidx=0;
            
            
            line->setStrokeColour(config->getDefaultStrokeColour());
            line->setFillColour(config->getDefaultFillColour());
            
            while(styleidx<strlen(attr))
            {
                if (stylemode==0)
                {
                    if (attr[styleidx]==':')
                    {
                        stylemode=1;
                    }
                    else
                    {
                        key[keyidx]=attr[styleidx];
                        keyidx++;
                        key[keyidx]=0;
                    }
                }
                else if (stylemode==1)
                {
                    if (attr[styleidx]==';')
                    {
                        if (strcmp(key,"stroke")==0)
                        {
                            line->setStrokeColour(config->getColourFromAttribute(value));
                        }
                        
                        if (strcmp(key,"fill")==0)
                        {
                            line->setFillColour(config->getColourFromAttribute(value));
                        }
                        
                        if (strcmp(key,"stroke-width")==0)
                        {
                            if (sscanf(value,"%f",&width)!=1)
                            {
                                width=1.0f;
                            }
                            line->setStrokeWidth(width);
                        }
                        else
                        {
                            width=1.0f;
                        }
                        
                        
                        if (strcmp(key,"stroke-linecap")==0)
                        {
                            line->setStrokeLineCap(value);
                        }
                        
                        if (strcmp(key,"stroke-dasharray")==0)
                        {

                            line->setStrokeDashArrayFromText(value);
                        }
                        
                        keyidx=0;
                        valueidx=0;
                        stylemode=0;
                    }    
                    else
                    {
                        value[valueidx]=attr[styleidx];
                        valueidx++;
                        value[valueidx]=0; 
                    }
                }
 
                styleidx++;    
            }
        
        }
        else
        {
            if (xmlmgr->ElementGetAttribute(element,"stroke")!=NULL)
            {
                line->setStrokeColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"stroke")));
            }
            else
            {
                line->setStrokeColour(config->getDefaultStrokeColour());
            }
            
            if (xmlmgr->ElementGetAttribute(element,"fill")!=NULL)
            {
                line->setFillColour(config->getColourFromAttribute(xmlmgr->ElementGetAttribute(element,"fill")));
            }
            else
            {
                line->setFillColour(config->getDefaultFillColour());
            }
            
            strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-width");
            if (strokeAttr)
            {
                if (sscanf(strokeAttr,"%f",&width)!=1)
                {
                    width=1.0f;
                }
            }
            else
            {
                width=1.0f;
            }
            line->setStrokeWidth(width);
        
            strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-linecap");
            if (strokeAttr)
            {
                line->setStrokeLineCap(strokeAttr);
            }
            
            
            strokeAttr=xmlmgr->ElementGetAttribute(element,"stroke-dasharray");
            if (strokeAttr)
            {
                line->setStrokeDashArrayFromText(strokeAttr);
            }
		}
		
		attr=xmlmgr->ElementGetAttribute(element,"d");
		
		if (attr)
		{
			success=true;
			
			index=0;
			command='?';
			
			while((index=dataGetCommand(attr,index,command,&command))>0)
			{
				
				switch(command)
				{
					case 'M':
						//absolute Move-to
						index=dataReadNumber(attr,index,&currX);
						index=dataReadNumber(attr,index,&currY);
						initialX=currX;
						initialY=currY;
						break;
					case 'm':
						//relative Move-to
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						currX=endX+currX;
						currY=endY+currY;
						initialX=currX;
						initialY=currY;
						break;
					case 'Z':
					case 'z':
						//absolute close-ptah
						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, initialX, initialY);
						line->addSegment(straightSeg);
						break;
					case 'L':
						//absolute Straight line
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);

						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, endX, endY);
						line->addSegment(straightSeg);
						
						currX=endX;
						currY=endY;
						break;
					case 'l':
						//relative Straight line
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						endX+=currX;
						endY+=currY;
						
						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, endX, endY);
						line->addSegment(straightSeg);
						
						currX=endX;
						currY=endY;
						break;
					case 'H':
						//absolute Horizontal line
						index=dataReadNumber(attr,index,&endX);
						
						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, endX, currY);
						line->addSegment(straightSeg);
						
						currX=endX;
						break;
					case 'h':
						//relative Horizontal line
						index=dataReadNumber(attr,index,&endX);
						
						endX+=currX;
						
						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, endX, currY);
						line->addSegment(straightSeg);
						
						currX=endX;
						break;
					case 'V':
						//absolute Vertical line
						index=dataReadNumber(attr,index,&endY);
						
						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, currX, endY);
						line->addSegment(straightSeg);
						
						currY=endY;
						break;
					case 'v':
						//relative Vertical line
						index=dataReadNumber(attr,index,&endY);
						
						endY+=currY;
						
						straightSeg=new SvgLineSegStraight();
						straightSeg->addSegment(currX, currY, currX, endY);
						line->addSegment(straightSeg);
						
						currY=endY;
						break;
					case 'C':
						//absolute cubic bezier line
						index=dataReadNumber(attr,index,&control1X);
						index=dataReadNumber(attr,index,&control1Y);
						index=dataReadNumber(attr,index,&control2X);
						index=dataReadNumber(attr,index,&control2Y);
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						cubicSeg=new SvgLineSegCubicBezier();
						cubicSeg->addSegment(currX,currY,endX,endY,control1X,control1Y,control2X,control2Y);
						line->addSegment(cubicSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control2X;
						prevControlY=control2Y;
						break;
					case 'c':
						//relative cubic bezier line
						index=dataReadNumber(attr,index,&control1X);
						index=dataReadNumber(attr,index,&control1Y);
						index=dataReadNumber(attr,index,&control2X);
						index=dataReadNumber(attr,index,&control2Y);
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
	
						control1X+=currX;
						control1Y+=currY;
						control2X+=currX;
						control2Y+=currY;
						endX+=currX;
						endY+=currY;
						
						cubicSeg=new SvgLineSegCubicBezier();
						cubicSeg->addSegment(currX,currY,endX,endY,control1X,control1Y,control2X,control2Y);
						line->addSegment(cubicSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control2X;
						prevControlY=control2Y;
						break;
					case 'S':
						//absolute smooth cubic bezier line
						index=dataReadNumber(attr,index,&control2X);
						index=dataReadNumber(attr,index,&control2Y);
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						control1X=(-(prevControlX-currX))+currX;
						control1Y=(-(prevControlY-currY))+currY;
						
						cubicSeg=new SvgLineSegCubicBezier();
						cubicSeg->addSegment(currX,currY,endX,endY,control1X,control1Y,control2X,control2Y);
						line->addSegment(cubicSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control2X;
						prevControlY=control2Y;
						
						break;
					case 's':
						//relative smooth cubic bezier line
						index=dataReadNumber(attr,index,&control2X);
						index=dataReadNumber(attr,index,&control2Y);
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						control1X=(-(prevControlX-currX))+currX;
						control1Y=(-(prevControlY-currY))+currY;
						control2X+=currX;
						control2Y+=currY;
						endX+=currX;
						endY+=currY;
						
						cubicSeg=new SvgLineSegCubicBezier();
						cubicSeg->addSegment(currX,currY,endX,endY,control1X,control1Y,control2X,control2Y);
						line->addSegment(cubicSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control2X;
						prevControlY=control2Y;
						break;
					case 'Q':
						//absolute quadratic bezier line
						index=dataReadNumber(attr,index,&control1X);
						index=dataReadNumber(attr,index,&control1Y);
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						quadSeg=new SvgLineSegQuadraticBezier();
						quadSeg->addSegment(currX,currY,endX,endY,control1X,control1Y);
						line->addSegment(quadSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control1X;
						prevControlY=control1Y;						
						break;
					case 'q':
						//relative quadratic bezier line
						index=dataReadNumber(attr,index,&control1X);
						index=dataReadNumber(attr,index,&control1Y);
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						control1X+=currX;
						control1Y+=currY;
						endX+=currX;
						endY+=currY;
						
						quadSeg=new SvgLineSegQuadraticBezier();
						quadSeg->addSegment(currX,currY,endX,endY,control1X,control1Y);
						line->addSegment(quadSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control1X;
						prevControlY=control1Y;							
						break;
					case 'T':
						//absolute smooth quadratic bezier line
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						control1X=(-(prevControlX-currX))+currX;
						control1Y=(-(prevControlY-currY))+currY;
						
						quadSeg=new SvgLineSegQuadraticBezier();
						quadSeg->addSegment(currX,currY,endX,endY,control1X,control1Y);
						line->addSegment(quadSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control1X;
						prevControlY=control1Y;							
						break;
					case 't':
						//relative smooth quadratic bezier line
						index=dataReadNumber(attr,index,&endX);
						index=dataReadNumber(attr,index,&endY);
						
						control1X=(-(prevControlX-currX))+currX;
						control1Y=(-(prevControlY-currY))+currY;
						endX+=currX;
						endY+=currY;
						
						quadSeg=new SvgLineSegQuadraticBezier();
						quadSeg->addSegment(currX,currY,endX,endY,control1X,control1Y);
						line->addSegment(quadSeg);
						
						currX=endX;
						currY=endY;
						prevControlX=control1X;
						prevControlY=control1Y;								
						break;
					case 'A':
						//absolute elliptical arc line
						assert(false);			// ELLIPTICAL ARC NOT SUPPORTED
						break;
					case 'a':
						//relative elliptical arc line
						assert(false);			// ELLIPTICAL ARC NOT SUPPORTED
						break;
					case '?':
						assert(false);			// NOT SUPPORTED
						//UNKNOWN!!
						break;
				}
			
			}
		}
	}
	
	if (success)
	{
		config->addEntry(line);
	}
	else
	{
		delete line;
	}

	
	return success;
}

