#include "growthdata.h"

void GrowthData::addMeasurement(const GrowthMeasurement& measurement) {
    measurements.append(measurement);
}

void GrowthData::removeMeasurement(int index) {
    if (index >= 0 && index < measurements.size()) {
        measurements.removeAt(index);
    }
}

QList<GrowthMeasurement> GrowthData::getAllMeasurements() const {
    return measurements;
}

GrowthMeasurement GrowthData::getMeasurement(int index) const {
    if (index >= 0 && index < measurements.size()) {
        return measurements.at(index);
    } else {
        return GrowthMeasurement(QDate(), -1); // Или throw exception
    }
}

int GrowthData::getSize() const {
    return measurements.size();
}
