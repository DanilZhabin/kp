#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFormLayout>

AddMeasurementDialog::AddMeasurementDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Добавить измерение");

    dateEdit = new QDateEdit(QDate::currentDate());
    heightSpinBox = new QDoubleSpinBox();
    heightSpinBox->setRange(0, 250);
    heightSpinBox->setSuffix(" см");

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Дата:", dateEdit);
    formLayout->addRow("Рост:", heightSpinBox);

    QPushButton *addButton = new QPushButton("Добавить");
    connect(addButton, &QPushButton::clicked, this, &AddMeasurementDialog::accept);
    QPushButton *cancelButton = new QPushButton("Отмена");
    connect(cancelButton, &QPushButton::clicked, this, &AddMeasurementDialog::reject);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

QDate AddMeasurementDialog::getDate() const { return dateEdit->date(); }
double AddMeasurementDialog::getHeight() const { return heightSpinBox->value(); }

MainWindow::MainWindow() {
    setWindowTitle("Журнал наблюдений за ростом ребенка");

    // Инициализация виджетов
    tableWidget = new QTableWidget(0, 2); // 2 колонки: дата и рост
    tableWidget->setHorizontalHeaderLabels({"Дата", "Рост"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Растягивать колонки

    addButton = new QPushButton("Добавить");
    removeButton = new QPushButton("Удалить");
    removeButton->setEnabled(false);

    // Компоновка виджетов
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);


    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Подключение сигналов и слотов
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addMeasurement);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeMeasurement);
    connect(tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::selectionChanged);

    // Загрузка начальных данных (можно заполнить при желании)
    loadInitialData();
    updateTable(); // Обновляем таблицу после загрузки
}

void MainWindow::addMeasurement() {
    AddMeasurementDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QDate date = dialog.getDate();
        double height = dialog.getHeight();

        data.addMeasurement(GrowthMeasurement(date, height));

        updateTable();
        qDebug() << "Trying to add measurement"; // debugging
        data.addMeasurement(GrowthMeasurement(date, height));

    }
}


void MainWindow::removeMeasurement() {
    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        int row = selectedItems.first()->row();
        data.removeMeasurement(row);
        updateTable();
    } else {
        QMessageBox::information(this, "Внимание", "Необходимо выбрать строку для удаления");
    }
}

void MainWindow::selectionChanged() {
    removeButton->setEnabled(tableWidget->selectionModel()->hasSelection());
}

void MainWindow::loadInitialData() {
    // Пример добавления начальных данных
    data.addMeasurement(GrowthMeasurement(QDate(2022, 1, 1), 50.0));
    data.addMeasurement(GrowthMeasurement(QDate(2022, 2, 1), 52.0));
    data.addMeasurement(GrowthMeasurement(QDate(2022, 3, 1), 54.5));
    data.addMeasurement(GrowthMeasurement(QDate(2022, 4, 1), 56.5));
    data.addMeasurement(GrowthMeasurement(QDate(2022, 5, 1), 58.5));
    data.addMeasurement(GrowthMeasurement(QDate(2022, 6, 1), 60.0));

}

void MainWindow::updateTable() {
    tableWidget->clearContents();
    tableWidget->setRowCount(data.getSize());

    for (int i = 0; i < data.getSize(); ++i) {
        GrowthMeasurement measurement = data.getMeasurement(i);
        QTableWidgetItem *dateItem = new QTableWidgetItem(measurement.date.toString("dd.MM.yyyy"));
        QTableWidgetItem *heightItem = new QTableWidgetItem(QString::number(measurement.height));

        tableWidget->setItem(i, 0, dateItem);
        tableWidget->setItem(i, 1, heightItem);
    }
}
