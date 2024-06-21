#include "services.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

class DoctorWindow : public QWidget, public Observer
{
private:
    Services &services;
    Doctor doctor;
    QVBoxLayout *layout;
    QCheckBox *checkBox;
    QLabel *doctorName;
    QListWidget *patientList;
    QListWidget *undiagnosedPatientList;
    QLineEdit *newPatientName;
    QLineEdit *newPatientDiagnosis;
    QLineEdit *newPatientSpecialisationNeeded;
    QLineEdit *newPatientCurrentDoctor;
    QLineEdit *newPatientAdmissionDate;
    QPushButton *addPatientButton;
    QLineEdit *nameToChangeLineEdit;
    QLineEdit *editDiagnosis;
    QLineEdit *editSpecialisation;
    QPushButton *changePatientButton;
    
    // Additional private helper methods
    void setupLayout();
    void setupConnections();
    void populate();
    void populateUndiagnosed();

public:
    DoctorWindow(Services &_services, Doctor _doctor);
    void update() override;
};

DoctorWindow::DoctorWindow(Services &_services, Doctor _doctor) 
    : services{_services}, doctor{_doctor}
{
    services.registerObserver(this);
    layout = new QVBoxLayout{};

    patientList = new QListWidget();
    undiagnosedPatientList = new QListWidget();
    checkBox = new QCheckBox();

    doctorName = new QLabel(QString::fromStdString(doctor.getName()));

    QLabel *newPatientLabel = new QLabel("Add a new patient");
    QLabel *n = new QLabel("Name");
    newPatientName = new QLineEdit();
    QLabel *d = new QLabel("Diagnosis");
    newPatientDiagnosis = new QLineEdit();
    QLabel *s = new QLabel("Specialisation needed");
    newPatientSpecialisationNeeded = new QLineEdit("");
    QLabel *cd = new QLabel("Current doctor");
    newPatientCurrentDoctor = new QLineEdit();
    QLabel *ad = new QLabel("Admission date");
    newPatientAdmissionDate = new QLineEdit();
    addPatientButton = new QPushButton("Add new patient!");

    nameToChangeLineEdit = new QLineEdit();
    editDiagnosis = new QLineEdit();
    editSpecialisation = new QLineEdit();
    changePatientButton = new QPushButton("Edit patient!");

    setupLayout();
    setupConnections();
    populate();
    populateUndiagnosed();

    this->setWindowTitle(QString::fromStdString(doctor.getName()));
    this->resize(500, 500);
}

void DoctorWindow::setupLayout()
{
    layout->addWidget(checkBox);
    layout->addWidget(patientList);
    layout->addWidget(undiagnosedPatientList);
    layout->addWidget(new QLabel("Add a new patient"));
    layout->addWidget(new QLabel("Name"));
    layout->addWidget(newPatientName);
    layout->addWidget(new QLabel("Diagnosis"));
    layout->addWidget(newPatientDiagnosis);
    layout->addWidget(new QLabel("Specialisation needed"));
    layout->addWidget(newPatientSpecialisationNeeded);
    layout->addWidget(new QLabel("Current doctor"));
    layout->addWidget(newPatientCurrentDoctor);
    layout->addWidget(new QLabel("Admission date"));
    layout->addWidget(newPatientAdmissionDate);
    layout->addWidget(addPatientButton);
    layout->addWidget(new QLabel("Edit patient"));
    layout->addWidget(new QLabel("What patient do you want to change?"));
    layout->addWidget(nameToChangeLineEdit);
    layout->addWidget(new QLabel("New Diagnosis"));
    layout->addWidget(editDiagnosis);
    layout->addWidget(new QLabel("New specialisation"));
    layout->addWidget(editSpecialisation);
    layout->addWidget(changePatientButton);
    setLayout(layout);
}

void DoctorWindow::setupConnections()
{
    QObject::connect(addPatientButton, &QPushButton::clicked, [this]()
    {
        if(newPatientName->text().isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Name cannot be empty!");
            return;
        }
        QString date = newPatientAdmissionDate->text();
        if(!services.checkDate(date.toStdString()))
        {
            QMessageBox::warning(this, "Warning", "Date cannot be in the past!");
            return;
        }
        Patient newPatient(newPatientName->text().toStdString(), newPatientDiagnosis->text().toStdString(), newPatientSpecialisationNeeded->text().toStdString(), newPatientCurrentDoctor->text().toStdString(), newPatientAdmissionDate->text().toStdString());
        services.addPatient(newPatient);
        services.notify();
    });

    QObject::connect(changePatientButton, &QPushButton::clicked, [this]()
    {
        if(editDiagnosis->text().toStdString() == "Undiagnosed")
            return;
        services.modifyPatient(nameToChangeLineEdit->text().toStdString(), editDiagnosis->text().toStdString(), editSpecialisation->text().toStdString());
        services.notify();
    });

    QObject::connect(checkBox, &QCheckBox::stateChanged, [this]()
    {
        if (checkBox->isChecked())
        {
            undiagnosedPatientList->hide();
        }
        else
        {
            undiagnosedPatientList->show();
        }
    });
}

void DoctorWindow::populate()
{
    patientList->clear();
    auto patients = services.getPatientsByDate();
    for (auto patient : patients)
    {
        if (patient.getSpecialisationNeeded() == doctor.getSpecialisation())
        {
            QListWidgetItem *item = new QListWidgetItem{QString::fromStdString(patient.getName() + " | " + patient.getDiagnosis() + " | " + patient.getCurrentDoctor() + " | " + patient.getSpecialisationNeeded() + " | " + patient.getAdmissionDate())};
            patientList->addItem(item);
        }
    }
}

void DoctorWindow::populateUndiagnosed()
{
    undiagnosedPatientList->clear();
    auto patients = services.getPatientsByDate();
    for (auto patient : patients)
    {
        if (patient.getDiagnosis() == "Undiagnosed")
        {
            QListWidgetItem *item = new QListWidgetItem{QString::fromStdString(patient.getName() + " | " + patient.getDiagnosis() + " | " + patient.getCurrentDoctor() + " | " + patient.getSpecialisationNeeded() + " | " + patient.getAdmissionDate())};
            undiagnosedPatientList->addItem(item);
        }
    }
}

void DoctorWindow::update()
{
    populate();
    populateUndiagnosed();
}
