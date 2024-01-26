/***************************************************************************
    qgsdatetimeeditwrapper.h
     --------------------------------------
    Date                 : 03.2014
    Copyright            : (C) 2014 Denis Rouzaud
    Email                : denis.rouzaud@gmail.com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSDATETIMEEDITWRAPPER_H
#define QGSDATETIMEEDITWRAPPER_H

#include <QDateTimeEdit>

#include "qgseditorwidgetwrapper.h"
#include "qgis_gui.h"

SIP_NO_FILE

class QgsDateTimeEdit;
class TestQgsDateTimeEdit;

/**
 * \ingroup gui
 * \brief Wraps a date time widget. Users will be able to choose date and time from an appropriate dialog.
 *
 * Options:
 * <ul>
 * <li><b>display_format</b> <i>The format used to represent the date/time to the user.</i></li>
 * <li><b>calendar_popup</b> <i>If TRUE, will offer a calendar popup.</i></li>
 * <li><b>allow_null</b> <i>If TRUE, will allow NULL values. Requires QgsDateTimeEdit as widget (Be aware if you work with .ui files).</i></li>
 * <li><b>field_format</b> <i>The format used to save the date/time.</i></li>
 * </ul>
 * \note not available in Python bindings
 */

class GUI_EXPORT QgsDateTimeEditWrapper : public QgsEditorWidgetWrapper
{
    Q_OBJECT
  public:

    /**
     * Constructor for QgsDateTimeEditWrapper.
     *
     * The \a layer and \a fieldIdx arguments specify the vector layer field associated with the wrapper.
     *
     * The \a editor argument indicates the editor widget to use with the wrapper. This can be NULLPTR if a
     * new widget should be autogenerated.
     *
     * A \a parent widget for this widget wrapper and the created widget can also be specified.
     */
    explicit QgsDateTimeEditWrapper( QgsVectorLayer *layer, int fieldIdx, QWidget *editor, QWidget *parent = nullptr );

  private slots:
    void dateTimeChanged( const QDateTime &dateTime );

  private:
    QDateTimeEdit *mQDateTimeEdit = nullptr;
    QgsDateTimeEdit *mQgsDateTimeEdit = nullptr;


    // QgsEditorWidgetWrapper interface
  public:
    QVariant value() const override;
    QWidget *createWidget( QWidget *parent ) override;
    void initWidget( QWidget *editor ) override;
    bool valid() const override;
    void showIndeterminateState() override;

  public slots:
    void setEnabled( bool enabled ) override;

  private:
    void updateValues( const QVariant &value, const QVariantList  & = QVariantList() ) override;


    friend class TestQgsDateTimeEdit;
};

#endif // QGSDATETIMEEDITWRAPPER_H
