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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Svg2DMatrix.h"
#include "Svg2DVector.h"

Svg2DMatrix::Svg2DMatrix()
{
	m_matrix[0][0]=1;
	m_matrix[0][1]=0;
	m_matrix[1][0]=0;
	m_matrix[1][1]=1;
	m_matrix[2][0]=0;
	m_matrix[2][1]=0;
}

Svg2DMatrix::~Svg2DMatrix()
{
}

bool Svg2DMatrix::initFromText(char *text)
{
	bool success=false;
	
	if (sscanf(text,"matrix(%f %f %f %f %f %f)",&m_matrix[0][0],
												&m_matrix[0][1],
												&m_matrix[1][0],
												&m_matrix[1][1],
												&m_matrix[2][0],
												&m_matrix[2][1])==6)
	{
		success=true;
	}
	
	return success;
}


void Svg2DMatrix::transformVector(Svg2DVector *vec)
{
	Svg2DVector res;
	
	res.m_x=vec->m_x*m_matrix[0][0]+vec->m_y*m_matrix[1][0]+m_matrix[2][0];
	res.m_y=vec->m_x*m_matrix[0][1]+vec->m_y*m_matrix[1][1]+m_matrix[2][1];
	
	vec->m_x=res.m_x;
	vec->m_y=res.m_y;
}

float Svg2DMatrix::getElement(int row,int column)
{
	if (row>=0 && row<3 && column>=0 && column<2)
	{
		return m_matrix[row][column];
	}
	return 0;
}


bool Svg2DMatrix::hasRotation()
{
	
	
	
	if (fabs(m_matrix[0][0]-1.0f)<0.001f && fabs(m_matrix[0][1]-0.0f)<0.001f &&
		fabs(m_matrix[1][0]-0.0f)<0.001f && fabs(m_matrix[1][1]-1.0f)<0.001f)
	{
		return false;
	}

	return true;
}
