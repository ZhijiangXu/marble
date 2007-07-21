//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2006-2007 Torsten Rahn <tackat@kde.org>"
// Copyright 2007      Inge Wallin  <ingwa@kde.org>"
//

#include "katlasviewinputhandler.h"

#include <cmath>

#include <QtCore/QDebug>

#include "GeoPoint.h"
#include "Quaternion.h"
#include "katlasdirs.h"
#include "MarbleWidget.h"



KAtlasViewInputHandler::KAtlasViewInputHandler(MarbleWidget *marbleWidget,
                                               MarbleModel  *model)
    : m_widget( marbleWidget ),
      m_model( model )
{
    curpmtl.load( KAtlasDirs::path("bitmaps/cursor_tl.xpm") );
    curpmtc.load( KAtlasDirs::path("bitmaps/cursor_tc.xpm") );
    curpmtr.load( KAtlasDirs::path("bitmaps/cursor_tr.xpm") );
    curpmcr.load( KAtlasDirs::path("bitmaps/cursor_cr.xpm") );
    curpmcl.load( KAtlasDirs::path("bitmaps/cursor_cl.xpm") );
    curpmbl.load( KAtlasDirs::path("bitmaps/cursor_bl.xpm") );
    curpmbc.load( KAtlasDirs::path("bitmaps/cursor_bc.xpm") );
    curpmbr.load( KAtlasDirs::path("bitmaps/cursor_br.xpm") );

    arrowcur [0][0] = QCursor(curpmtl,2,2);
    arrowcur [1][0] = QCursor(curpmtc,10,3);
    arrowcur [2][0] = QCursor(curpmtr,19,2);
    arrowcur [0][1] = QCursor(curpmcl,3,10);
    arrowcur [1][1] = QCursor(Qt::PointingHandCursor);
    arrowcur [2][1] = QCursor(curpmcr,18,10);
    arrowcur [0][2] = QCursor(curpmbl,2,19);
    arrowcur [1][2] = QCursor(curpmbc,11,18);
    arrowcur [2][2] = QCursor(curpmbr,19,19);

    m_leftpressed = false;
    m_midpressed  = false;

    m_dragThreshold = 3;

    m_positionSignalConnected = false;
}


bool KAtlasViewInputHandler::eventFilter( QObject* o, QEvent* e )
{
		
    Q_UNUSED( o );

    //	if ( o == marbleWidget ){
    if ( e->type() == QEvent::KeyPress ) {
        QKeyEvent  *k = (QKeyEvent *)e;

        dirx = 0; 
        diry = 0;
        switch ( k->key() ) {
        case 0x01000012: 
            dirx = -1;
            break;
        case 0x01000013: 
            diry = -1;
            break;
        case 0x01000014: 
            dirx = 1;
            break;
        case 0x01000015: 
            diry = 1;
            break;
        case 0x2b:
            m_widget->zoomIn();
            break;
        case 0x2d:
            m_widget->zoomOut();
            break;
        case 0x01000010:
            m_widget->goHome();
            break;
        default:
            break;
        }

        if ( dirx != 0 || diry != 0 ) {
            m_widget->rotateBy( -m_widget->moveStep() * (double)(diry),
                                -m_widget->moveStep() * (double)(dirx) );
            m_widget->repaint();
        }

        return true;
    } 
    else if ( e->type() == QEvent::MouseMove
              || e->type() == QEvent::MouseButtonPress 
              || e->type() == QEvent::MouseButtonRelease ) {

        QMouseEvent  *event        = static_cast<QMouseEvent*>(e);
        QRegion       activeRegion = m_widget->activeRegion();

        dirx = 0; 
        diry = 0;

        // emit the position string only if the signal got attached
        if ( m_positionSignalConnected )
        {
            double  lat;
            double  lng;
            m_widget->globeSphericals( event->x(), event->y(), lng, lat );
            QString position = GeoPoint( lng, lat ).toString();
            emit mouseGeoPosition( position );
        }


        if ( activeRegion.contains( event->pos() ) ) {
            if ( e->type() == QEvent::MouseButtonDblClick) {
                qDebug("check");
            }

            // Regarding mouse button presses:
            if ( e->type() == QEvent::MouseButtonPress
                 && event->button() == Qt::LeftButton ) {

                m_dragtimer.restart();					

                m_leftpressed = true;
                m_midpressed  = false;

                // On the single event of a mouse button press these 
                // values get stored, to enable us to e.g. calculate the 
                // distance of a mouse drag while the mouse button is 
                // still down. 
                m_leftpressedx = event->x();
                m_leftpressedy = event->y();

                // m_leftpresseda: screen center latitude  during mouse press
                // m_leftpressedb: screen center longitude during mouse press
                m_widget->globeSphericals( m_widget->width() / 2,
                                           m_widget->height() / 2,
                                           m_leftpresseda, m_leftpressedb );

                if ( m_widget->northPoleY() > 0 ) {
                    m_leftpressedb = M_PI - m_leftpressedb;
                    m_leftpresseda = M_PI + m_leftpresseda;	 
                }
            }

            if ( e->type() == QEvent::MouseButtonPress
                 && event->button() == Qt::MidButton) {
                m_midpressed  = true;
                m_leftpressed = false;
                m_midpressedy = event->y();
            }

            if ( e->type() == QEvent::MouseButtonPress
                 && event->button() == Qt::RightButton ) {
                emit rmbRequest( event->x(), event->y() );
            }

            // Regarding mouse button releases:
            if ( e->type() == QEvent::MouseButtonRelease
                 && event->button() == Qt::LeftButton) {
                
                //emit current gps coordinates to be be interpreted 
                //as requested
                emit gpsCoordinates( m_leftpressedx, m_leftpressedy );

                // Show menu if mouse cursor position remains unchanged
                // the click takes less than 250 ms
                if ( m_dragtimer.elapsed() <= 250
		     || ( m_leftpressedx == event->x()
			  && m_leftpressedy == event->y() ) ) {
                    emit lmbRequest( m_leftpressedx, m_leftpressedy );
                }

                m_leftpressed = false;
            }

            if ( e->type() == QEvent::MouseButtonRelease
                 && event->button() == Qt::MidButton) {
                m_midpressed = false;
            }

            if ( e->type() == QEvent::MouseButtonRelease
                 && event->button() == Qt::RightButton) {
            }

            // Regarding all kinds of mouse moves:
            if ( m_leftpressed == true ) {
                double  radius = (double)(m_widget->radius());
                int    deltax = event->x() - m_leftpressedx;
                int    deltay = event->y() - m_leftpressedy;

                if (abs(deltax) <= m_dragThreshold
                    && abs(deltay) <= m_dragThreshold)
                    return true; 

                double direction = 1;
                if ( m_widget->northPoleZ() > 0 ) {	
                    if ( event->y() < ( m_widget->northPoleY()
                                        + m_widget->height() / 2 ) )
                        direction = -1;
                }
                else {
                    if (event->y() > ( -m_widget->northPoleY() 
                                       + m_widget->height() / 2 ) )
                        direction = -1;
                }

                m_widget->rotateTo( 180 / M_PI * (double)(-m_leftpressedb)
                                    + 90 * deltay / radius, 
                                    -180 / M_PI * (double)(m_leftpresseda)
                                    + 90 * direction * deltax / radius );

                m_widget->repaint();
            }


            if ( m_midpressed == true ) {
                int  eventy = event->y();
                int  dy     = m_midpressedy - eventy;
                m_midpressed = eventy;
                m_widget->zoomViewBy( (int)( 2 * dy / 3 ) );
                m_widget->repaint();
            }
        }
        else {
            m_leftpressed = false;

            dirx = (int)( 3 * event->x() / m_widget->width() ) - 1;
            if ( dirx > 1 ) 
                dirx = 1;
            if ( dirx < -1 )
                dirx = -1;

            diry = (int)( 3 * event->y() / m_widget->height() ) - 1;
            if ( diry > 1 ) 
                diry = 1;
            if ( diry < -1 )
                diry = -1;
#ifdef FLAT_PROJ
            //Dirty hack to make properly behavior for the arrow
            int     radius        = m_widget->radius();
            double  centerLat     = m_widget->planetAxis().pitch();
            int     yCenterOffset = (int)((float)(2*radius / M_PI) * centerLat);
            int     yTop          =  m_widget->height() / 2 - radius + yCenterOffset;
            int     yBottom       = yTop + 2*radius;
            yTop = ( yTop > 0 ) ? yTop : 0;
            if ( dirx == 0 && event->y() < yTop)
                 diry=-1;
            if ( dirx == 0 && event->y() > yBottom )
                diry=1;
#endif
            if ( event->button() == Qt::LeftButton
                 && e->type() == QEvent::MouseButtonPress ) {

                m_widget->rotateBy( -m_widget->moveStep() * (double)(diry),
                                    -m_widget->moveStep() * (double)(dirx) );
                m_widget->repaint();

            }				
        }

        m_widget->setCursor(arrowcur[dirx+1][diry+1]);

        return true;
    }
    else {
        if ( e->type() == QEvent::Wheel ) {
            QWheelEvent  *wheelevt = static_cast<QWheelEvent*>(e);
            m_widget->zoomViewBy((int)(wheelevt->delta()/3));

            return true;
        }
        else
            return false;
    }
}

#include "katlasviewinputhandler.moc"

