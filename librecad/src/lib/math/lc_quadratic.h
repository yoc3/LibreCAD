/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2011-2012 Dongxu Li (dongxuli2011@gmail.com)

Copyright (C) 2012 Dongxu Li (dongxuli2011@gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

**********************************************************************/


#ifndef LC_QUADRATIC_H
#define LC_QUADRATIC_H


#include "rs_vector.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>



/**
 * Class for generic linear and quadratic equation
 * supports translation and rotation of an equation
 *
 * @author Dongxu Li
 */
class LC_Quadratic {
public:
    LC_Quadratic(std::vector<double> ce);
    std::vector<double> getCoeffficents() const;
    LC_Quadratic move(const RS_Vector& v);
    LC_Quadratic rotate(const double& a);

    private:
    boost::numeric::ublas::matrix<double> m_mQuad;
    boost::numeric::ublas::vector<double> m_vLinear;
    double m_dConst;
    bool m_bIsQuadratic;
};



#endif
//EOF
