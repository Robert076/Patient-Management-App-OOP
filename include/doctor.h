#include <string>
using namespace std;

class Doctor
{
private:
    string name, specialisation;
public:
    Doctor(string _name, string _specialisation)
    {
        name = _name;
        specialisation = _specialisation;
    }
    string getName()
    {
        return name;
    }
    string getSpecialisation()
    {
        return specialisation;
    }
    
};