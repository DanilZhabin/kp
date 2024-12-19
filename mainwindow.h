#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QDate>
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include "growthdata.h"

class AddMeasurementDialog : public QDialog {
    Q_OBJECT
public:
    AddMeasurementDialog(QWidget *parent = nullptr);

    QDate getDate() const;
    double getHeight() const;

private:
    QDateEdit *dateEdit;
    QDoubleSpinBox *heightSpinBox;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void addMeasurement();
    void removeMeasurement();
    void selectionChanged();

private:
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    GrowthData data;

    void loadInitialData();
    void updateTable();
};
#endif
