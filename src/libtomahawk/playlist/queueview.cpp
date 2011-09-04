/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "queueview.h"
#include "ui_queueview.h"

#include <QVBoxLayout>

#include "widgets/HeaderLabel.h"
#include "playlist/queueproxymodel.h"
#include "widgets/overlaywidget.h"
#include "utils/logger.h"

using namespace Tomahawk;


QueueView::QueueView( AnimatedSplitter* parent )
    : AnimatedWidget( parent )
    , ui( new Ui::QueueView )
{
    ui->setupUi( this );
    TomahawkUtils::unmarginLayout( layout() );
    setContentsMargins( 0, 0, 0, 0 );

    setHiddenSize( QSize( 0, 22 ) );

    ui->queue->setProxyModel( new QueueProxyModel( this ) );
    ui->queue->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Ignored );
    ui->queue->setFrameShape( QFrame::NoFrame );
    ui->queue->setAttribute( Qt::WA_MacShowFocusRect, 0 );
    ui->queue->overlay()->setEnabled( false );

    connect( ui->toggleButton, SIGNAL( clicked() ), SLOT( show() ) );
}


QueueView::~QueueView()
{
    qDebug() << Q_FUNC_INFO;
}


PlaylistView*
QueueView::queue() const
{
    return ui->queue;
}


void
QueueView::hide()
{
    disconnect( ui->toggleButton, SIGNAL( clicked() ), this, SLOT( hide() ) );
    connect( ui->toggleButton, SIGNAL( clicked() ), SLOT( show() ) );
    ui->toggleButton->setText( tr( "Show Queue" ) );
    emit hideWidget();
}


void
QueueView::show()
{
    disconnect( ui->toggleButton, SIGNAL( clicked() ), this, SLOT( show() ) );
    connect( ui->toggleButton, SIGNAL( clicked() ), SLOT( hide() ) );
    ui->toggleButton->setText( tr( "Hide Queue" ) );
    emit showWidget();
}


void
QueueView::onShown( QWidget* widget, bool animated )
{
    if ( widget != this )
        return;

    AnimatedWidget::onShown( widget, animated );
}


void
QueueView::onHidden( QWidget* widget, bool animated )
{
    if ( widget != this )
        return;

    AnimatedWidget::onHidden( widget, animated );
}
