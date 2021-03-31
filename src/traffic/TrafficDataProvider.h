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
#include <QTimer>
#include <QObject>
#include <QQmlListProperty>

#include "GlobalSettings.h"
#include "traffic/Factor.h"
#include "traffic/FLARMWarning.h"
#include "traffic/AbstractTrafficDataSource.h"


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
class TrafficDataProvider : public Positioning::AbstractPositionInfoSource {
    Q_OBJECT

public:
    /*! \brief Default constructor
     *
     * @param parent The standard QObject parent pointer
     */
    explicit TrafficDataProvider(QObject *parent = nullptr);

    // Standard destructor
    ~TrafficDataProvider() = default;

    //
    // Methods
    //

    /*! \brief Pointer to static instance of this class
     *
     *  @returns Pointer to global instance
     */
    static TrafficDataProvider *globalInstance();

    //
    // Properties
    //


    Q_PROPERTY(Traffic::FLARMWarning* flarmWarning READ flarmWarning CONSTANT)

    Traffic::FLARMWarning* flarmWarning() const
    {
        return _flarmWarning;
    }

    /*! \brief Receiving data from one data source*/
    Q_PROPERTY(bool receiving READ receiving NOTIFY receivingChanged)

    /*! \brief Getter method for property with the same name
     *
     *  @returns Property receiving
     */
    bool receiving() const;

    /*! \brief Receiving data from one data source*/
    Q_PROPERTY(QString statusString READ statusString NOTIFY statusStringChanged)

    /*! \brief Getter method for property with the same name
     *
     *  @returns Property statusString
     */
    QString statusString() const;

    /*! \brief Traffic objects whose position is known
     *
     *  This property holds a list of the most relevant traffic objects, as a
     *  QQmlListProperty for better cooperation with QML. Note that only the
     *  valid items in this list pertain to actual traffic. Invalid items should
     *  be ignored. The list is not sorted in any way. The items themselves are
     *  owned by this class.
     */
    Q_PROPERTY(QQmlListProperty<Traffic::Factor> trafficObjects4QML READ trafficObjects4QML CONSTANT)

    /*! \brief Getter method for property with the same name
     *
     *  @returns Property trafficObjects4QML
     */
    QQmlListProperty<Traffic::Factor> trafficObjects4QML()
    {
        return QQmlListProperty(this, &_trafficObjects);
    }

    /*! \brief Most relevant traffic object whose position is not known
     *
     *  This property holds a pointer to the most relevant traffic object whose
     *  position is not known.  This item should be ignored if invalid. The item
     *  is owned by this class.
     */
    Q_PROPERTY(Traffic::Factor *trafficObjectWithoutPosition READ trafficObjectWithoutPosition CONSTANT)

    /*! \brief Getter method for property with the same name
     *
     *  @returns Property trafficObjectWithoutPosition
     */
    Traffic::Factor *trafficObjectWithoutPosition()
    {
        return _trafficObjectWithoutPosition;
    }

public slots:
    /*! \brief Start attempt to connect to traffic receiver
     *
     * If this class is connected to a traffic receiver, this method does nothing.
     * Otherwise, it stops any ongoing connection attempt and starts a new attempt
     * to connect to a potential receiver.
     */
    void connectToTrafficReceiver();

    /*! \brief Disconnect from traffic receiver
     *
     * This method stops any ongoing connection or connection attempt.
     */
    void disconnectFromTrafficReceiver();

private slots:
    void onSourceHeartbeatChanged();

    void onFactorWithPosition(const Traffic::Factor &factor);

    void onFactorWithoutPosition(const Traffic::Factor &factor);

private:
    // Targets
    QList<Traffic::Factor *> _trafficObjects;
    QPointer<Traffic::Factor> _trafficObjectWithoutPosition;

    // Warnings
    QPointer<Traffic::FLARMWarning> _flarmWarning;

    QList<QPointer<Traffic::AbstractTrafficDataSource>> _dataSources;

    // Reconnect
    QTimer reconnectionTimer;

    // Property Cache
    bool _receiving {false};
};

}
