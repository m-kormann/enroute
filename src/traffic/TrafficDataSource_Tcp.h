/***************************************************************************
 *   Copyright (C) 2021 by Stefan Kebekus                                  *
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

#pragma once

#include <QGeoPositionInfo>
#include <QTcpSocket>
#include <QTimer>
#include <QObject>
#include <QQmlListProperty>

#include "GlobalSettings.h"
#include "traffic/TrafficFactor.h"
#include "traffic/TrafficDataSource_Abstract.h"

namespace Traffic {

/*! \brief Traffic receiver
 *
 *  This class connects to a traffic receiver via the network. It expects to
 *  find a receiver at the IP-Address 192.168.1.1, port 2000.  Once connected,
 *  it continuously reads data from the device, and exposes position and traffic
 *  information to the user, as well as barometric altitude.
 *
 *  By modifying the source code, developers can also start the class in a mode
 *  where it connects to a file with simulator data.
 */
class TrafficDataSource_Tcp : public TrafficDataSource_Abstract {
    Q_OBJECT

public:
    /*! \brief Default constructor
     *
     * @param parent The standard QObject parent pointer
     */
    explicit TrafficDataSource_Tcp(QString hostName, quint16 port, QObject *parent = nullptr);

    // Standard destructor
    ~TrafficDataSource_Tcp() override;

    /*! \brief Getter function for the property with the same name
     *
     * @returns Property sourceName
     */
    QString sourceName() const override
    {
        return tr("TCP connection to %1 port %2").arg(_hostName).arg(_port);
    }

public slots:
    /*! \brief Start attempt to connect to traffic receiver
     *
     * If this class is connected to a traffic receiver, this method does nothing.
     * Otherwise, it stops any ongoing connection attempt and starts a new attempt
     * to connect to a potential receiver.
     */
    void connectToTrafficReceiver() override;

    /*! \brief Disconnect from traffic receiver
     *
     * This method stops any ongoing connection or connection attempt.
     */
    void disconnectFromTrafficReceiver() override;

private slots:
    // Handle socket errors.
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

    // Read one line from the socket's text stream and passes the string on to
    // processFLARMMessage.
    void readFromStream();

    // Update the property "errorString" and "connectivityStatus" and emit notification signals
    void onStateChanged();

    void onHasHeartbeatChanged();

private:
    QPointer<QTcpSocket> socket;
    QTextStream textStream;
    QString _hostName;
    quint16 _port;
};

}