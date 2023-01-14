#include <iostream>
#include <string>
using namespace std;

//Prototypes.
int stringToInteger(string s);

//Constants.
int INVALID_COORDINATE = -1;

int main()
{
    string name;
    cout << "Test place-strings function stringToInteger - Start" << endl;

    cout << "Test Case 1: " << endl;
    cout << "stringToInteger(""'5'"") = " << stringToInteger ("5") << endl;

    cout << "Test Case 2: " << endl;
    cout << "stringToInteger(""'55'"") = " << stringToInteger("55") << endl;

    cout << "Test Case 3: " << endl;
    cout << "stringToInteger(""'555'"") = " << stringToInteger("555") << endl;

    cout << "Test Case 4: " << endl;
    cout << "stringToInteger(""'5555'"") = " << stringToInteger("5555") << endl;

    cout << "Test Case 5: " << endl;
    cout << "stringToInteger(""'55557'"") = " << stringToInteger("55557") << endl;

    cout << "Test Case 6: " << endl;
    cout << "stringToInteger(""'a'"") = " << stringToInteger("a") << endl;

    cout << "Test Case 7: " << endl;
    cout << "stringToInteger(""-55557"") = " << stringToInteger("-55557") << endl;

    cout << "Test place-strings function stringToInteger - End" << endl;

    return 0;
}

int stringToInteger(string s){

    int result = 0;
    int sign = 1;
    int startIndex = 0;

    //Check if string is empty
    if (s.empty())
    {
        return INVALID_COORDINATE;
    }

    if (s[0] == '-') {
        sign = -1;
        startIndex = 1;
    }

    //Check if string contains only numbers
    for (int i = startIndex; i < s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return INVALID_COORDINATE;
        }
    }

    for(int i = startIndex; i < s.length(); i++){
        result = result*10 + s[i] - '0';
    }
    return result * sign;
}

