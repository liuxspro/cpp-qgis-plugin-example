/***************************************************************************
                             qgsabstractsensor.h
                             ---------------------------
    begin                : March 2023
    copyright            : (C) 2023 by Mathieu Pellerin
    email                : mathieu at opengis dot ch
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSABSTRACTSENSOR_H
#define QGSABSTRACTSENSOR_H

#include "qgis_core.h"
#include "qgis_sip.h"
#include "qgis.h"

#include <QDateTime>
#include <QDomElement>
#include <QVariant>

/**
 * \ingroup core
 * \class QgsAbstractSensor
 * \brief An abstract base class for sensor classes
 * \since QGIS 3.32
 */
class CORE_EXPORT QgsAbstractSensor : public QObject
{
#ifdef SIP_RUN
#include "qgsiodevicesensor.h"
#include "qgssensorregistry.h"
#endif


#ifdef SIP_RUN
    SIP_CONVERT_TO_SUBCLASS_CODE
    if ( QgsAbstractSensor *item = qobject_cast< QgsAbstractSensor * >( sipCpp ) )
    {
      if ( item->type() == QLatin1String( "tcp_socket" ) && dynamic_cast<QgsTcpSocketSensor *>( item ) != NULL )
      {
        sipType = sipType_QgsTcpSocketSensor;
      }
      else if ( item->type() == QLatin1String( "udp_socket" ) && dynamic_cast<QgsUdpSocketSensor *>( item ) != NULL )
      {
        sipType = sipType_QgsUdpSocketSensor;
      }
#if defined( HAVE_QTSERIALPORT )
      else if ( item->type() == QLatin1String( "serial_port" ) && dynamic_cast<QgsSerialPortSensor *>( item ) != NULL )
      {
        sipType = sipType_QgsSerialPortSensor;
      }
#endif
      else
      {
        sipType = sipType_QgsAbstractSensor;
      }
    }
    else
    {
      sipType = NULL;
    }
    SIP_END
#endif

    Q_OBJECT

  public:

    /**
     * Contains details of a sensor data capture
     */
    struct CORE_EXPORT SensorData
    {

      /**
       * Last captured sensor value stored as a QVariant.
       * \note The member can store multiple values if the sensor passes on a QVariantMap.
       */
      QVariant lastValue;

      //! Timestamp of last captured sensor value
      QDateTime lastTimestamp;
    };

    /**
     * Constructor for an abstract sensor, bound to the specified \a parent.
     */
    explicit QgsAbstractSensor( QObject *parent SIP_TRANSFERTHIS = nullptr );
    virtual ~QgsAbstractSensor() = default;

    /**
     * Returns the sensor ID.
     * \note This is a autogenerated unique string identifying an individual sensor.
     */
    QString id() const { return mId; }

    /**
     * Returns the sensor type. This will match the type string of the sensor class, as used by QgsSensorRegistry.
     */
    virtual QString type() const { return QString(); }

    /**
     * Returns the user-friendly name identifying the sensor.
     */
    QString name() const;

    /**
     * Sets the  user-friendly name identfying the sensor.
     */
    void setName( const QString &name );

    /**
     * Returns the current sensor status.
     */
    Qgis::DeviceConnectionStatus status() const;

    /**
     * Sets the current sensor \a status.
     */
    void setStatus( Qgis::DeviceConnectionStatus status );

    /**
     * Connects the sensor to its source.
     */
    void connectSensor();

    /**
     * Disconnects the sensor from its source.
     */
    void disconnectSensor();

    /**
     * Returns the latest captured data from the sensor.
     */
    QgsAbstractSensor::SensorData data() const;

    /**
     * Sets the latest captured data from the sensor.
     */
    void setData( const QgsAbstractSensor::SensorData &data );

    /**
     * Returns the last error message.
     */
    QString errorString() const;

    /**
     * Write generic sensor properties into a DOM element.
     * \param parentElement parent DOM element (e.g 'Sensors' element)
     * \param document DOM document
     */
    bool writeXml( QDomElement &parentElement, QDomDocument &document ) const;

    /**
     * Restores generic sensor details from a DOM element.
     * \param element DOM node corresponding to item (e.g. 'Sensor' element)
     * \param document DOM document
     */
    bool readXml( const QDomElement &element, const QDomDocument &document );

    /**
     * Write specific sensor type properties into a DOM element.
     * \param element  DOM node corresponding to item (e.g. 'Sensor' element)
     * \param document DOM document
     */
    virtual bool writePropertiesToElement( QDomElement &element, QDomDocument &document ) const;

    /**
     * Restores specific sensor type properties from a DOM element.
     * \param element  DOM node corresponding to item (e.g. 'Sensor' element)
     * \param document DOM document
     */
    virtual bool readPropertiesFromElement( const QDomElement &element, const QDomDocument &document );

  signals:

    //! Emitted when the sensor name has changed.
    void nameChanged();

    //! Emitted when the sensor status has changed.
    void statusChanged();

    //! Emitted when the captured sensor data has changed.
    void dataChanged();

    //! Emitted when an error has occurred. The \a errorString describes the error.
    void errorOccurred( const QString &errorString );

  protected:

    /**
     * Handles the connection to the sensor.
     * \note Triggered by calling connectSensor()
     */
    virtual void handleConnect() = 0;

    /**
     * Handles the disconnection from the sensor.
     * \note Triggered by calling disconnectSensor()
     */
    virtual void handleDisconnect() = 0;

    QgsAbstractSensor::SensorData mData;
    QString mErrorString;

  private:

    QString mId;
    QString mName;
    Qgis::DeviceConnectionStatus mStatus = Qgis::DeviceConnectionStatus::Disconnected;

};

Q_DECLARE_METATYPE( QgsAbstractSensor * )

#endif //QGSABSTRACTSENSOR_H
