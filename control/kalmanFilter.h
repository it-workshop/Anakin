#pragma once
#include <QObject>

/**
 * @file kalmanFilter.h
 *
 * Implementation of KalmanFilter class.
 * This class filters the incoming values by the Kalman's method.
 */

class KalmanFilter
{
public:
    KalmanFilter(qreal measuredNoise, qreal enviromentNoise, qreal prevValueFactor,
                 qreal measuredValueFactor);
    /// Setting the original state of data and covariance of process.
    void setState(qreal state, qreal covariance);
    /// Updating and correcting data.
    void correct(qreal data);
    /// Return mState.
    qreal state();
private:
    qreal mPredicateState;
    qreal mPredicateCovaiance;

    qreal mPrevValueFactor;
    qreal mMeasurementNoise;
    qreal mMeasuredValueFactor;
    qreal mEnviromentNoise;

    qreal mState;
    qreal mCovariance;
};
