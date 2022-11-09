/***************************************************************************
 *   Copyright (C) 2019-2020 by Stefan Kebekus                             *
 *   stefan.kebekus@gmail.com                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "platform/PlatformAdaptor_Linux.h"



Platform::PlatformAdaptor::PlatformAdaptor(QObject *parent)
    : PlatformAdaptor_Abstract(parent)
{
#warning Want reaction to connectivitiy changes
    connect(&networkManagerInterface, SIGNAL(StateChanged(uint)), this, SLOT(onStateChanged(uint)));

}

#include <QDebug>

void Platform::PlatformAdaptor::onStateChanged(uint x)
{
#warning need to implement
    qWarning() << "StateChanged" << x;
}


//
// Methods
//

auto Platform::PlatformAdaptor::currentSSID() -> QString
{
#warning Want to implement
    return QStringLiteral("<unknown ssid>");
}


void Platform::PlatformAdaptor::disableScreenSaver()
{
}


auto Platform::PlatformAdaptor::hasRequiredPermissions() -> bool
{
    return true;
}


void Platform::PlatformAdaptor::lockWifi(bool lock)
{
}


void Platform::PlatformAdaptor::onGUISetupCompleted()
{
}


void Platform::PlatformAdaptor::requestPermissionsSync()
{
}


void Platform::PlatformAdaptor::vibrateBrief()
{
}
