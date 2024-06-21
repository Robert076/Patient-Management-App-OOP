#include <string>
using namespace std;

class Patient
{
private:
    string name, diagnosis, specialisationNeeded, currentDoctor, admissionDate;
public:
    Patient(string _name, string _diagnosis, string _specialisationNeeded, string _currentDoctor, string _addmisionDate)
    {
        name = _name;
        diagnosis = _diagnosis;
        specialisationNeeded = _specialisationNeeded;
        currentDoctor = _currentDoctor;
        admissionDate = _addmisionDate;
    }
    string getName()
    {
        return name;
    }
    string getDiagnosis()
    {
        return diagnosis;
    }
    string getSpecialisationNeeded()
    {
        return specialisationNeeded;
    }
    string getCurrentDoctor()
    {
        return currentDoctor;
    }
    string getAdmissionDate()
    {
        return admissionDate;
    }
    void setDiagnosis(string d)
    {
        diagnosis = d;
    }
    void setSpecialisationNeeded(string s)
    {
        specialisationNeeded = s;
    }
};