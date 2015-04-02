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


#ifndef RS_VECTOR_H
#define RS_VECTOR_H

#include <iostream>
#include <vector>
#include "rs.h"

/**
 * Represents a 3d vector (x/y/z)
 *
 * @author Andrew Mustun
 */
class RS_Vector {
public:
    RS_Vector();
#ifdef  RS_VECTOR2D
    RS_Vector(double vx, double vy);
#else
    RS_Vector(double vx, double vy, double vz=0.0);
#endif
    explicit RS_Vector(double angle);
    //RS_Vector(double v[]);
    explicit RS_Vector(bool valid);
	~RS_Vector()=default;

    void set(double angle); // set to unit vector by the direction of angle
#ifdef  RS_VECTOR2D
    void set(double vx, double vy);
#else
    void set(double vx, double vy, double vz=0.0);
#endif
    void setPolar(double radius, double angle);

    double distanceTo(const RS_Vector& v) const;
    double angle() const;
    double angleTo(const RS_Vector& v) const;
    double angleBetween(const RS_Vector& v1, const RS_Vector& v2) const;
    double magnitude() const;
    double squared() const; //return square of length
    double squaredTo(const RS_Vector& v1) const; //return square of length
    RS_Vector lerp(const RS_Vector& v, double t) const;

    bool isInWindow(const RS_Vector& firstCorner, const RS_Vector& secondCorner) const;
    bool isInWindowOrdered(const RS_Vector& vLow, const RS_Vector& vHigh) const;

    RS_Vector toInteger();

    RS_Vector move(const RS_Vector& offset);
    RS_Vector rotate(const double& ang);
    RS_Vector rotate(const RS_Vector& angleVector);
    RS_Vector rotate(const RS_Vector& center, const double& ang);
    RS_Vector rotate(const RS_Vector& center, const RS_Vector& angleVector);
    RS_Vector scale(const double& factor);
    RS_Vector scale(const RS_Vector& factor);
	RS_Vector scale(const RS_Vector& factor) const;
	RS_Vector scale(const RS_Vector& center, const RS_Vector& factor);
    RS_Vector mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2);
	double dotP(const RS_Vector& v1) const;

    RS_Vector operator + (const RS_Vector& v) const;
    RS_Vector operator - (const RS_Vector& v) const;
	RS_Vector operator * (const RS_Vector& v) const;
	RS_Vector operator / (const RS_Vector& v) const;
    RS_Vector operator * (const double& s) const;
    RS_Vector operator / (const double& s) const;
    RS_Vector operator - () const;

	RS_Vector operator += (const RS_Vector& v);
	RS_Vector operator -= (const RS_Vector& v);
	RS_Vector operator *= (const RS_Vector& v);
	RS_Vector operator /= (const RS_Vector& v);
	RS_Vector operator *= (const double& s);
	RS_Vector operator /= (const double& s);

    bool operator == (const RS_Vector& v) const;
    bool operator != (const RS_Vector& v) const {
        return !operator==(v);
    }

    static RS_Vector minimum(const RS_Vector& v1, const RS_Vector& v2);
    static RS_Vector maximum(const RS_Vector& v1, const RS_Vector& v2);
#ifndef RS_VECTOR2D
//    crossP only defined for 3D
    static RS_Vector crossP(const RS_Vector& v1, const RS_Vector& v2);
#endif
    static double dotP(const RS_Vector& v1, const RS_Vector& v2);

    /** switch x,y for all vectors */
    RS_Vector flipXY(void) const;

    friend std::ostream& operator << (std::ostream&, const RS_Vector& v);

#ifdef RS_TEST

    static bool test();
#endif

public:
    double x;
    double y;
#ifndef RS_VECTOR2D
    double z;
#endif
    bool valid;
};


/**
 * Represents one to 4 vectors. Typically used to return multiple
 * solutions from a function.
 */
class RS_VectorSolutions {
public:
    RS_VectorSolutions();
    RS_VectorSolutions(const RS_VectorSolutions& s);
	RS_VectorSolutions(int num);
	RS_VectorSolutions(std::initializer_list<RS_Vector> l);

    ~RS_VectorSolutions();

	void alloc(size_t num);
	void clean();
    void clear();
	/**
	 * @brief get range safe method of member access
	 * @param i member index
	 * @return indexed member, or invalid vector, if out of range
	 */
	RS_Vector get(size_t i) const;
	const RS_Vector& at(size_t i) const;
	const RS_Vector&  operator [] (const size_t i) const;
	RS_Vector&  operator [] (const size_t i);
	size_t getNumber() const;
	size_t size() const;
    void resize(size_t n);
    bool hasValid() const;
void set(size_t i, const RS_Vector& v);
    void push_back(const RS_Vector& v);
	void removeAt(const size_t i);
    RS_VectorSolutions appendTo(const RS_VectorSolutions& v);
    void setTangent(bool t);
    bool isTangent() const;
    RS_Vector getClosest(const RS_Vector& coord,
						 double* dist=NULL, size_t* index=NULL) const;
    double getClosestDistance(const RS_Vector& coord,
                              int counts = -1); //default to search all
	const std::vector<RS_Vector>& getVector() const;
	std::vector<RS_Vector>::const_iterator begin() const;
	std::vector<RS_Vector>::const_iterator end() const;
	std::vector<RS_Vector>::iterator begin();
	std::vector<RS_Vector>::iterator end();
	void rotate(const double& ang);
    void rotate(const RS_Vector& angleVector);
    void rotate(const RS_Vector& center, const double& ang);
    void rotate(const RS_Vector& center, const RS_Vector& angleVector);
    void move(const RS_Vector& vp);
    void scale(const RS_Vector& center, const RS_Vector& factor);
    void scale(const RS_Vector& factor);

    /** switch x,y for all vectors */
    RS_VectorSolutions flipXY(void) const;

    RS_VectorSolutions operator = (const RS_VectorSolutions& s);

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_VectorSolutions& s);

private:
	std::vector<RS_Vector> vector;
    bool tangent;
};

#endif

// EOF
