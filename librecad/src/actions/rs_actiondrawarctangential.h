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

#ifndef RS_ACTIONDRAWARCTANGENTIAL_H
#define RS_ACTIONDRAWARCTANGENTIAL_H

#include "rs_previewactioninterface.h"

class RS_AtomicEntity;
struct RS_ArcData;

/**
 * This action class can handle user events to draw 
 * arcs with three points given.
 *
 * @author Andrew Mustun
 */
class RS_ActionDrawArcTangential : public RS_PreviewActionInterface {
	Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
		SetBaseEntity,   /**< Setting base entity. */
		SetEndAngle      /**< Setting end angle. */
    };

public:
    RS_ActionDrawArcTangential(RS_EntityContainer& container,
                               RS_GraphicView& graphicView);
    ~RS_ActionDrawArcTangential();

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual RS2::ActionType rtti() {
        return RS2::ActionDrawArcTangential;
    }

    void reset();

    virtual void init(int status=0);

    virtual void trigger();
    void preparePreview();

    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    virtual void coordinateEvent(RS_CoordinateEvent* e);
    virtual void commandEvent(RS_CommandEvent* e);
    virtual QStringList getAvailableCommands();
    
    virtual void hideOptions();
    virtual void showOptions();

    virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
//    virtual void updateToolBar();

	void setRadius(double r);

	double getRadius() const;
    void setAngle(double r) {
        angleLength= r;
    }

    double getAngle() const {
        return angleLength;
    }
    virtual void setByRadius(bool status=true);
    virtual bool getByRadius() const {
        return byRadius;
    }

protected:
    /**
     * Base entity.
     */
    RS_AtomicEntity* baseEntity;
    /**
  * Start point of base entity clicked?
  */
    bool isStartPoint;
    /**
     * Point that determines end angle.
     */
    RS_Vector point;
    /**
  * Arc data calculated.
  */
	std::unique_ptr<RS_ArcData> data;
private:
    double angleLength;
    bool byRadius;
};

#endif
