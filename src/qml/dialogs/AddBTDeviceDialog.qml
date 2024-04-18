/***************************************************************************
 *   Copyright (C) 2024 by Stefan Kebekus                                  *
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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import akaflieg_freiburg.enroute
import "../items"

CenteringDialog {
    id: dlg

    modal: true
    title: qsTr("Add Device: Classic Bluetooth")
    standardButtons: Dialog.Ok

    property BTScanner btScanner: TrafficDataProvider.btScanner
    
    DecoratedScrollView{
        anchors.fill: parent
        contentWidth: availableWidth // Disable horizontal scrolling

        clip: true

        ColumnLayout {
            width: dlg.availableWidth

            Label {
                Layout.fillWidth: true

                text: btScanner.error
                wrapMode: Text.Wrap
            }

            BusyIndicator {
                Layout.alignment: Qt.AlignHCenter

                running: true
                visible: btScanner.isScanning
            }

            Label {
                Layout.fillWidth: true

                horizontalAlignment: Text.AlignHCenter
                text: qsTr("Standby. Searching for Bluetooth devices.")
                wrapMode: Text.Wrap
                visible: btScanner.isScanning
            }

            Label {
                Layout.fillWidth: true

                text: "Placeholder for the list of devices."
                wrapMode: Text.Wrap
            }

        }
    }

}
