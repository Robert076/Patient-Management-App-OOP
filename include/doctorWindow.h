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

public:
    DoctorWindow(Services &_services, Doctor _doctor) : services{_services}, doctor{_doctor}
    {
        services.registerObserver(this);
        layout = new QVBoxLayout{};

        patientList = new QListWidget();

        undiagnosedPatientList = new QListWidget();
        checkBox = new QCheckBox();

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
        QObject::connect(addPatientButton, &QPushButton::clicked, [this]()
                         {
            if(newPatientName->text().toStdString() == "")
            {
                QMessageBox::warning(this, "Warning", "Name cannot be empty!");
                return;
            }
            string date = newPatientAdmissionDate->text().toStdString();
            if(!services.checkDate(date))
            {
                QMessageBox::warning(this, "Warning", "Date cannot be in the past!");
                return;
            }
            Patient newPatient(newPatientName->text().toStdString(), newPatientDiagnosis->text().toStdString(), newPatientSpecialisationNeeded->text().toStdString(), newPatientCurrentDoctor->text().toStdString(), newPatientAdmissionDate->text().toStdString());
            services.addPatient(newPatient);
            services.notify(); });
        QLabel *editPatientLabel = new QLabel("Edit patient");
        QLabel *nameToChange = new QLabel("What patient do you want to change?");
        nameToChangeLineEdit = new QLineEdit();
        QLabel *newDiagnosis = new QLabel("New Diagnosis");
        editDiagnosis = new QLineEdit();
        QLabel *newSpecialisation = new QLabel("New specialisation");
        editSpecialisation = new QLineEdit();
        changePatientButton = new QPushButton("Edit patient!");
        QObject::connect(changePatientButton, &QPushButton::clicked, [this]()
                         {
            if(editDiagnosis->text().toStdString() == "Undiagnosed")
                return;
            services.modifyPatient(nameToChangeLineEdit->text().toStdString(), editDiagnosis->text().toStdString(), editSpecialisation->text().toStdString());
            services.notify(); });

        layout->addWidget(checkBox);
        layout->addWidget(patientList);
        layout->addWidget(undiagnosedPatientList);
        layout->addWidget(newPatientLabel);
        layout->addWidget(n);
        layout->addWidget(newPatientName);
        layout->addWidget(d);
        layout->addWidget(newPatientDiagnosis);
        layout->addWidget(s);
        layout->addWidget(newPatientSpecialisationNeeded);
        layout->addWidget(cd);
        layout->addWidget(newPatientCurrentDoctor);
        layout->addWidget(ad);
        layout->addWidget(newPatientAdmissionDate);
        layout->addWidget(addPatientButton);
        layout->addWidget(editPatientLabel);
        layout->addWidget(nameToChange);
        layout->addWidget(nameToChangeLineEdit);
        layout->addWidget(newDiagnosis);
        layout->addWidget(editDiagnosis);
        layout->addWidget(newSpecialisation);
        layout->addWidget(editSpecialisation);
        layout->addWidget(changePatientButton);

        QObject::connect(checkBox, &QCheckBox::stateChanged, [this]()
                         {
            if (checkBox->isChecked())
            {
                undiagnosedPatientList->hide();
            }
            else
            {
                undiagnosedPatientList->show();
            } });

        setLayout(layout);
        populate();
        populateUndiagnosed();
        this->setWindowTitle(QString::fromStdString(doctor.getName()));
        this->resize(500, 500);
    }
    void update()
    {
        populate();
        populateUndiagnosed();
    }
    void populate()
    {
        patientList->clear();
        vector<Patient> patients = this->services.getPatientsByDate();
        for (auto patient : patients)
            if (patient.getSpecialisationNeeded() == doctor.getSpecialisation())
            {
                QListWidgetItem *item = new QListWidgetItem{QString::fromStdString(patient.getName() + " | " + patient.getDiagnosis() + " | " + patient.getCurrentDoctor() + " | " + patient.getSpecialisationNeeded() + " | " + patient.getAdmissionDate())};

                patientList->addItem(item);
            }
    }
    void populateUndiagnosed()
    {
        undiagnosedPatientList->clear();
        vector<Patient> patients = this->services.getPatientsByDate();
        for (auto patient : patients)
        {
            if (patient.getDiagnosis() == "Undiagnosed")
            {
                QListWidgetItem *item = new QListWidgetItem{QString::fromStdString(patient.getName() + " | " + patient.getDiagnosis() + " | " + patient.getCurrentDoctor() + " | " + patient.getSpecialisationNeeded() + " | " + patient.getAdmissionDate())};

                undiagnosedPatientList->addItem(item);
            }
        }
    }
};