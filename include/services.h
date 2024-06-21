#include "repository.h"
#include "observerManager.h"

class Services : public ObserverManager
{
private:
    Repository repository;

public:
    Services()
    {
        repository = Repository();
    }
    vector<Patient> getPatients()
    {
        return repository.getPatients();
    }
    vector<Doctor> getDoctors()
    {
        return repository.getDoctors();
    }
    vector<Patient> getPatientsByDate()
    {
        vector<Patient> patients = repository.getPatients();
        // #TODO

        return patients;
    }
    void addPatient(Patient p)
    {
        repository.addPatient(p);
    }
    void modifyPatient(string name, string d, string s)
    {
        vector<Patient> v;
        for(auto p : repository.getPatients())
        {
            if(p.getName() != name)
                v.push_back(p);
        }
        for(auto p : repository.getPatients())
        {
            if(p.getName() == name)
            {   
                v.push_back(Patient(name, d, s, p.getCurrentDoctor(), p.getAdmissionDate()));
            }
        }
        repository.setPatients(v);
    }
    bool checkDate(string date)
    {
        int day = (date[0] - '0') * 10 + date[1] - '0';
        int month = (date[3] - '0') * 10 + date[4] - '0';
        int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + date[9] - '0';
        if(day < 21 && month < 6 && year < 2024 || year < 2024 || month < 6 && year < 2024 || day < 21 && month == 6 && year < 2024 || month < 6 && year == 2024)
            return false;
        return true;
    }
};
