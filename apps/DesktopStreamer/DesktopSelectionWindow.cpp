/*********************************************************************/
/* Copyright (c) 2011 - 2012, The University of Texas at Austin.     */
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

#include "DesktopSelectionWindow.h"

#include "DesktopSelectionView.h"

DesktopSelectionWindow::DesktopSelectionWindow()
    : _desktopSelectionView( new DesktopSelectionView( this ))
{
    // make window transparent
    setStyleSheet( "background:transparent;" );
    setAttribute( Qt::WA_TranslucentBackground );
    setWindowFlags( Qt::FramelessWindowHint );

    // window stays on top
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags( flags | Qt::CustomizeWindowHint |
                    Qt::WindowStaysOnTopHint );

    // add the view after showing the window to avoid shadow artifacts on Mac
    setCentralWidget( _desktopSelectionView );

    QPushButton* hideWindowButton = new QPushButton( "Exit selection mode" );
    connect( hideWindowButton, SIGNAL( pressed( )), this, SLOT( hide( )));
    // makes the button square so the background doesn't look bad
    hideWindowButton->setFlat( true );

    _desktopSelectionView->scene()->addWidget( hideWindowButton );
}

DesktopSelectionRectangle* DesktopSelectionWindow::getSelectionRectangle()
{
    return _desktopSelectionView->getSelectionRectangle();
}

void DesktopSelectionWindow::hideEvent( QHideEvent* hideEvt )
{
    QWidget::hideEvent( hideEvt );

    emit windowVisible( false );
}
