#include "doctor.h"
#include "patient.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repository
{
private:
    vector<Doctor> doctors;
    vector<Patient> patients;

public:
    Repository()
    {
        doctors = getDoctors();
        patients = getPatients();
    }
    vector<Doctor> getDoctors()
    {
        doctors.clear();
        string line;
        ifstream fin("../doctors.txt");
        while (getline(fin, line))
        {
            stringstream ss(line);
            string name, specialisation;
            getline(ss, name, ';');
            getline(ss, specialisation);
            Doctor newDoctor(name, specialisation);
            doctors.push_back(newDoctor);
        }
        return doctors;
    }
    vector<Patient> getPatients()
    {
        patients.clear();
        string line;
        ifstream fin("../patients.txt");
        while (getline(fin, line))
        {
            stringstream ss(line);
            string name, diagnosis, specialisationNeeded, currentDoctor, admissionDate;
            getline(ss, name, ';');
            getline(ss, diagnosis, ';');
            getline(ss, specialisationNeeded, ';');
            getline(ss, currentDoctor, ';');
            getline(ss, admissionDate, ';');
            Patient newPatient(name, diagnosis, specialisationNeeded, currentDoctor, admissionDate);
            patients.push_back(newPatient);
        }
        return patients;
    }
    void setPatients(vector<Patient> patients)
    {
        ofstream fout("../patients.txt");
        for(auto pat : patients)
        {
            fout << pat.getName() << ";" << pat.getDiagnosis() << ";" << pat.getSpecialisationNeeded() << ";" << pat.getCurrentDoctor() << ";" << pat.getAdmissionDate() << "\n";
        }
    }
    void addPatient(Patient p)
    {
        patients.push_back(p);
        ofstream fout("../patients.txt");
        for(auto pat : patients)
        {
            fout << pat.getName() << ";" << pat.getDiagnosis() << ";" << pat.getSpecialisationNeeded() << ";" << pat.getCurrentDoctor() << ";" << pat.getAdmissionDate() << "\n";
        }
    }
};