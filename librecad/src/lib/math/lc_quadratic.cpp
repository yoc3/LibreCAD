/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/

#include "lc_quadratic.h"

#ifdef EMU_C99
#include "emu_c99.h" /* C99 math */
#endif

/**
 * Constructor.
 */
 LC_Quadratic::LC_Quadratic(std::vector<double> ce):
     m_mQuad(2,2),
     m_vLinear(2)
 {
     if(ce.size()==6){
         //quadratic
         m_mQuad(0,0)=ce[0];
         m_mQuad(0,1)=0.5*ce[1];
         m_mQuad(1,0)=m_mQuad(0,1);
         m_mQuad(1,1)=ce[2];
         m_vLinear(0)=ce[3];
         m_vLinear(1)=ce[4];
         m_dConst=ce[5];
         m_bIsQuadratic=true;
         return;
     }
         m_bIsQuadratic=false;
     if(ce.size()==3){
         m_vLinear(0)=ce[0];
         m_vLinear(1)=ce[1];
         m_dConst=ce[2];
     }

 }
