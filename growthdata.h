#ifndef GROWTHDATA_H
#define GROWTHDATA_H

#include <QList>
#include <QDate>

struct GrowthMeasurement {
    QDate date;
    double height;

    GrowthMeasurement(const QDate& d, double h) : date(d), height(h) {}
};

class GrowthData {
public:
    QList<GrowthMeasurement> measurements;

    void addMeasurement(const GrowthMeasurement& measurement);
    void removeMeasurement(int index);
    QList<GrowthMeasurement> getAllMeasurements() const;
    GrowthMeasurement getMeasurement(int index) const;
    int getSize() const;
};

#endif
