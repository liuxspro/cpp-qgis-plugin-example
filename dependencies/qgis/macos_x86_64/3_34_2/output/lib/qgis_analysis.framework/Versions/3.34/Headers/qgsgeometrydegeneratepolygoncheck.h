/***************************************************************************
    qgsgeometrydegeneratepolygoncheck.h
    ---------------------
    begin                : September 2014
    copyright            : (C) 2014 by Sandro Mani / Sourcepole AG
    email                : smani at sourcepole dot ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#define SIP_NO_FILE

#ifndef QGS_GEOMETRY_DEGENERATEPOLYGON_CHECK_H
#define QGS_GEOMETRY_DEGENERATEPOLYGON_CHECK_H

#include "qgsgeometrycheck.h"

/**
 * \ingroup analysis
 * \brief A degenerate polygon check.
 */
class ANALYSIS_EXPORT QgsGeometryDegeneratePolygonCheck : public QgsGeometryCheck
{
    Q_DECLARE_TR_FUNCTIONS( QgsGeometryDegeneratePolygonCheck )
  public:
    enum ResolutionMethod { DeleteRing, NoChange };

    explicit QgsGeometryDegeneratePolygonCheck( QgsGeometryCheckContext *context, const QVariantMap &configuration )
      : QgsGeometryCheck( context, configuration ) {}

    void collectErrors( const QMap<QString, QgsFeaturePool *> &featurePools, QList<QgsGeometryCheckError *> &errors, QStringList &messages, QgsFeedback *feedback, const LayerFeatureIds &ids = LayerFeatureIds() ) const override;
    void fixError( const QMap<QString, QgsFeaturePool *> &featurePools, QgsGeometryCheckError *error, int method, const QMap<QString, int> &mergeAttributeIndices, Changes &changes ) const override;

    QList<Qgis::GeometryType> compatibleGeometryTypes() const override { return factoryCompatibleGeometryTypes(); }
    Q_DECL_DEPRECATED QStringList resolutionMethods() const override;
    QString description() const override { return factoryDescription(); }
    QString id() const override { return factoryId(); }
    QgsGeometryCheck::CheckType checkType() const override { return factoryCheckType(); }

    static QList<Qgis::GeometryType> factoryCompatibleGeometryTypes() {return {Qgis::GeometryType::Polygon}; }
    static bool factoryIsCompatible( QgsVectorLayer *layer ) SIP_SKIP { return factoryCompatibleGeometryTypes().contains( layer->geometryType() ); }
    static QString factoryDescription() { return tr( "Polygon with less than three nodes" ); }
    static QString factoryId() { return QStringLiteral( "QgsGeometryDegeneratePolygonCheck" ); }
    static QgsGeometryCheck::CheckType factoryCheckType() SIP_SKIP;

  private:
};

#endif // QGS_GEOMETRY_DEGENERATEPOLYGON_CHECK_H
