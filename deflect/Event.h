/*********************************************************************/
/* Copyright (c) 2013-2016, EPFL/Blue Brain Project                  */
/*                          Raphael Dumusc <raphael.dumusc@epfl.ch>  */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE IS PROVIDED  BY THE  UNIVERSITY OF  TEXAS AT    */
/*    AUSTIN  ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,    */
/*    INCLUDING, BUT  NOT LIMITED  TO, THE IMPLIED  WARRANTIES OF    */
/*    MERCHANTABILITY  AND FITNESS FOR  A PARTICULAR  PURPOSE ARE    */
/*    DISCLAIMED.  IN  NO EVENT SHALL THE UNIVERSITY  OF TEXAS AT    */
/*    AUSTIN OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL,  SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES    */
/*    (INCLUDING, BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE    */
/*    GOODS  OR  SERVICES; LOSS  OF  USE,  DATA,  OR PROFITS;  OR    */
/*    BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON ANY THEORY OF    */
/*    LIABILITY, WHETHER  IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*    (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT    */
/*    OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF ADVISED  OF  THE    */
/*    POSSIBILITY OF SUCH DAMAGE.                                    */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of The University of Texas at Austin.                 */
/*********************************************************************/

#ifndef DEFLECT_EVENT_H
#define DEFLECT_EVENT_H

#ifdef _MSC_VER
#include <stdint.h>
#endif

#include <deflect/api.h>
#include <deflect/types.h>

#define UNICODE_TEXT_SIZE 4

class QDataStream;

namespace deflect
{
/**
 * A user event within a window.
 *
 * Typically used to forward user inputs from a window to classes that
 * generate content for it.
 *
 * Events can be divided into several categories, listed below. Applications can
 * decide to handle all the events or limit themselves to any subset that is
 * appropriate.
 *
 * For example, an application which supports multiple touch points natively may
 * want to use unprocessed touch points, while still assigning some specific
 * actions to high-level gestures such as swipe events.
 *
 * For a concrete code example of basic event processing, users can refer to
 * the simplestreamer demo application.
 *
 * Stream events
 * - EVT_VIEW_SIZE_CHANGED   < remote stream window resized by user
 * - EVT_CLOSE               < remote stream window closed by user
 *
 * Basic interaction
 * - EVT_PRESS               < touch/mouse button press (single touch point)
 * - EVT_MOVE                < touch point/mouse move (single touch point)
 * - EVT_RELEASE             < touch/mouse button release (single touch point)
 * - EVT_WHEEL               < mouse wheel event (no longer sent by Tide >= 1.2,
 *                             replaced by EVT_PINCH)
 *
 * Basic gestures
 * - EVT_CLICK               < tap/click with one or more fingers/buttons (key
 *                             field contains number of points)
 * - EVT_DOUBLECLICK         < double tap/click with one or more fingers/button
 *                             (key field contains number of points)
 * - EVT_TAP_AND_HOLD        < tap and hold with one or more fingers/buttons
 *                             (key field contains number of points)
 *
 * Advanced gestures
 * - EVT_PAN                 < pan with two or more fingers (key field contains
 *                             number of points)
 * - EVT_PINCH               < pinch with two finger
 * - EVT_SWIPE_LEFT          < swipe left with two fingers
 * - EVT_SWIPE_RIGHT         < swipe right with two fingers
 * - EVT_SWIPE_UP            < swipe up with two fingers
 * - EVT_SWIPE_DOWN          < swipe down with two fingers
 *
 * Unprocessed touch points
 * - EVT_TOUCH_ADD           < touch point added (key field contains point id)
 * - EVT_TOUCH_UPDATE        < touch point moved (key field contains point id)
 * - EVT_TOUCH_REMOVE        < touch point removed (key field contains point id)
 *
 * Keybord events
 * - EVT_KEY_PRESS           < key pressed
 * - EVT_KEY_RELEASE         < key released
 *
 * Other:
 * - EVT_NONE                < normally unused
 *
 * @version 1.0
 */
struct Event
{
    /**
     * The EventType enum defines the different types of interaction.
     * @version 1.0
     */
    enum EventType
    {
        EVT_NONE,
        EVT_PRESS,
        EVT_RELEASE,
        EVT_CLICK,
        EVT_DOUBLECLICK,
        EVT_MOVE,
        EVT_WHEEL,
        EVT_SWIPE_LEFT,
        EVT_SWIPE_RIGHT,
        EVT_SWIPE_UP,
        EVT_SWIPE_DOWN,
        EVT_CLOSE,
        EVT_KEY_PRESS,
        EVT_KEY_RELEASE,
        EVT_VIEW_SIZE_CHANGED,
        EVT_TAP_AND_HOLD,
        EVT_PAN,
        EVT_PINCH,
        EVT_TOUCH_ADD,
        EVT_TOUCH_UPDATE,
        EVT_TOUCH_REMOVE
    };

    /** The type of event */
    EventType type;

    /** @name Mouse and touch events */
    //@{
    double mouseX;    /**< Normalized X mouse/touch position relative to the
                         window */
    double mouseY;    /**< Normalized Y mouse/touch position relative to the
                         window */
    double dx;        /**< Normalized horizontal delta for pan/pinch events /
                         delta in pixels for wheel events */
    double dy;        /**< Normalized vertical delta for pan/pinch events /
                         delta in pixels for wheel events */
    bool mouseLeft;   /**< State of the left mouse button (pressed=true) */
    bool mouseRight;  /**< State of the right mouse button (pressed=true) */
    bool mouseMiddle; /**< State of the middle mouse button (pressed=true) */
    //@}

    /** @name Keyboard events */
    //@{
    int key;       /**< The key code, see QKeyEvent::key() / number of fingers
                      for gestures / point id for touch events */
    int modifiers; /**< The keyboard modifiers, see QKeyEvent::modifiers() */
    char text[UNICODE_TEXT_SIZE]; /**< Carries unicode for key, see
                                     QKeyEvent::text() */
    //@}

    /** Construct a new event. @version 1.0 */
    Event()
        : type(EVT_NONE)
        , mouseX(0)
        , mouseY(0)
        , dx(0)
        , dy(0)
        , mouseLeft(false)
        , mouseRight(false)
        , mouseMiddle(false)
        , key(0)
        , modifiers(0)
        , text()
    {
    }

    /** The size of the QDataStream serialized output. */
    static const uint32_t serializedSize;
};

/** Serialization for network, where sizeof(Event) can differ between compilers.
 */
DEFLECT_API QDataStream& operator<<(QDataStream& out, const Event& event);
DEFLECT_API QDataStream& operator>>(QDataStream& in, Event& event);
}

#endif
