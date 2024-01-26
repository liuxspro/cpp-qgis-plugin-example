/***************************************************************************
    qgsrangewidgetwrapper.h
     --------------------------------------
    Date                 : 5.1.2014
    Copyright            : (C) 2014 Matthias Kuhn
    Email                : matthias at opengis dot ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSRANGEWIDGETWRAPPER_H
#define QGSRANGEWIDGETWRAPPER_H

#include "qgseditorwidgetwrapper.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include "qgis_gui.h"

SIP_NO_FILE

class QAbstractSlider;
class QSlider;
class QDial;
class QgsSlider;
class QgsDial;
class TestQgsRangeWidgetWrapper;

/**
 * \ingroup gui
 * \brief Wraps a range widget.
 *
 * Options:
 * <ul>
 * <li><b>Style</b> <i>Can be "Dial" or "Slider"</i></li>
 * <li><b>Min</b> <i>The minimal allowed value</i></li>
 * <li><b>Max</b> <i>The maximal allowed value</i></li>
 * <li><b>Step</b> <i>The step size when incrementing/decrementing the value</i></li>
 * </ul>
 * \note not available in Python bindings
 */

class GUI_EXPORT QgsRangeWidgetWrapper : public QgsEditorWidgetWrapper
{
    Q_OBJECT
  public:

    /**
     * Constructor for QgsRangeWidgetWrapper.
     *
     * The \a layer and \a fieldIdx arguments specify the vector layer field associated with the wrapper.
     *
     * The \a editor argument indicates the editor widget to use with the wrapper. This can be NULLPTR if a
     * new widget should be autogenerated.
     *
     * A \a parent widget for this widget wrapper and the created widget can also be specified.
     */
    explicit QgsRangeWidgetWrapper( QgsVectorLayer *layer, int fieldIdx, QWidget *editor, QWidget *parent = nullptr );

    // QgsEditorWidgetWrapper interface
  public:
    QVariant value() const override;

  protected:
    QWidget *createWidget( QWidget *parent ) override;
    void initWidget( QWidget *editor ) override;
    bool valid() const override;

  public slots:
    void setEnabled( bool enabled ) override;

  private slots:
    // NOTE - cannot be named "valueChanged", otherwise implicit conversion to QVariant results in
    // infinite recursion
    void valueChangedVariant( const QVariant & );

  private:
    void updateValues( const QVariant &value, const QVariantList & = QVariantList() ) override;

    QSpinBox *mIntSpinBox = nullptr;
    QDoubleSpinBox *mDoubleSpinBox = nullptr;
    QSlider *mSlider = nullptr;
    QDial *mDial = nullptr;
    QgsSlider *mQgsSlider = nullptr;
    QgsDial *mQgsDial = nullptr;

    friend class TestQgsRangeWidgetWrapper;
};

#endif // QGSRANGEWIDGETWRAPPER_H
