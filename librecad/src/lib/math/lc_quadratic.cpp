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

 std::vector<double>  LC_Quadratic::getCoeffficents() const
 {
     std::vector<double> ret(0,0.);
     if(m_bIsQuadratic){
         ret.push_back(m_mQuad(0,0));
         ret.push_back(m_mQuad(0,1)+m_mQuad(1,0));
         ret.push_back(m_mQuad(1,1));
     }
         ret.push_back(m_vLinear(0));
         ret.push_back(m_vLinear(1));
         ret.push_back(m_dConst);
         return ret;
 }

 LC_Quadratic LC_Quadratic::move(const RS_Vector& v)
 {
     if(m_bIsQuadratic){
         m_dConst += m_vLinear(0) * v.x + m_vLinear(1)*v.y;
         m_vLinear(0) += 2.*m_mQuad(0,0)*v.x + (m_mQuad(0,1)+m_mQuad(1,0))*v.y;
         m_vLinear(1) += 2.*m_mQuad(1,1)*v.y + (m_mQuad(0,1)+m_mQuad(1,0))*v.x;
         m_dConst += m_mQuad(0,0)*v.x*v.x + (m_mQuad(0,1)+m_mQuad(1,0))*v.x*v.y+ m_mQuad(1,1)*v.y*v.y ;
     }else{
         m_dConst += m_mQuad(0,0)*v.x*v.x + (m_mQuad(0,1)+m_mQuad(1,0))*v.x*v.y+ m_mQuad(1,1)*v.y*v.y ;
     }
     return *this;
 }


 LC_Quadratic LC_Quadratic::rotate(const double& angle)
 {
     using namespace boost::numeric::ublas;
     auto&& m=rotationMatrix(angle);
     m_vLinear = prod(m, m_vLinear);
     if(m_bIsQuadratic){
         m_mQuad=prod(m_mQuad,m);
         m_mQuad=prod( trans(m), m_mQuad);
     }
     return *this;
 }

 LC_Quadratic LC_Quadratic::rotate(const RS_Vector& center, const double& angle)
 {
     move(-center);
     rotate(angle);
     move(center);
     return *this;
 }

 /**
   rotation matrix:

   cos x, -sin x
   sin x, cos x
   */
boost::numeric::ublas::matrix<double>  LC_Quadratic::rotationMatrix(const double& angle)
{
    boost::numeric::ublas::matrix<double> ret(2,2);
    ret(0,0)=cos(angle);
    ret(1,0)=sin(angle);
    ret(0,1)=-ret(1,0);
    ret(1,1)=ret(0,0);
    return ret;
}
//EOF
