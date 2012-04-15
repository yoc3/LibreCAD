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

#include <QVector>
#include "rs_hyperbola.h"

#include "rs_graphic.h"
#include "rs_graphicview.h"
#include "rs_painter.h"
#include "rs_information.h"
#include "rs_linetypepattern.h"

#ifdef EMU_C99
#include "emu_c99.h" /* C99 math */
#endif

/**
 * Constructor.
 */
RS_Hyperbola::RS_Hyperbola(RS_EntityContainer* parent,
                       const RS_HyperbolaData& d)
    :RS_AtomicEntity(parent), data(d) {

    //calculateEndpoints();
    calculateBorders();
}


/**
 * Recalculates the endpoints using the angles and the radius.
 */
/*
void RS_Hyperbola::calculateEndpoints() {
   double angle = data.majorP.angle();
   double radius1 = getMajorRadius();
   double radius2 = getMinorRadius();

   startpoint.set(data.center.x + cos(data.angle1) * radius1,
                  data.center.y + sin(data.angle1) * radius2);
   startpoint.rotate(data.center, angle);
   endpoint.set(data.center.x + cos(data.angle2) * radius1,
                data.center.y + sin(data.angle2) * radius2);
   endpoint.rotate(data.center, angle);
}
*/


/**
 * Calculates the boundary box of this ellipse.
 */



/**
  * return the foci of ellipse
  *
  *@Author: Dongxu Li
  */

RS_VectorSolutions RS_Hyperbola::getFoci() const {
    RS_Vector vp(getMajorP()*sqrt(1.-getRatio()*getRatio()));
    return RS_VectorSolutions(getCenter()+vp, getCenter()-vp);
}

RS_VectorSolutions RS_Hyperbola::getRefPoints() {
    RS_VectorSolutions ret;
    ret.push_back(data.center);
    ret.appendTo(getFoci());
    return ret;
}

bool RS_Hyperbola::isPointOnEntity(const RS_Vector& coord,
                             double tolerance) const
{
    double a=data.majorP.magnitude();
    double b=a*data.ratio;
    if(fabs(a)<tolerance || fabs(b)<tolerance) return false;
    RS_Vector vp(coord - data.center);
    vp=vp.rotate(-data.majorP.angle()).scale(1./a,1./b);
    return vp.squared()<tolerance;
}


std::vector<double> RS_Hyperbola::getEquation() const
{
}


/**
 * Dumps the point's data to stdout.
 */
std::ostream& operator << (std::ostream& os, const RS_Hyperbola& a) {
    os << " Hyperbola: " << a.data << "\n";
    return os;
}

