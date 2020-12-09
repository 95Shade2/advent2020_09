#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>    //min and max

using namespace std;

double Double(string num) {
    double num_i = 0;

    while (num.size() > 0) {
        num_i *= 10;
        num_i += num[0] - '0';
        num = num.substr(1);
    }

    return num_i;
}

vector<double> Get_Numbers() {
    vector<double> numbers;
    ifstream file;
    string line;
    double num;

    file.open("numbers.txt");
    getline(file, line);
    while (file) {
        num = Double(line);
        numbers.push_back(num);
        getline(file, line);
    }

    return numbers;
}

double Get_First_Invalid(vector<double> numbers, int backwards) {
    double invalid_number;
    double sum;
    double cur_num;
    bool valid;

    for (int i = backwards; i < numbers.size(); i++) {
        cur_num = numbers[i];
        valid = false;

        for (int b = i - backwards; b < i; b++) {
            for (int n = b+1; n < i; n++) {
                sum = numbers[b] + numbers[n];

                if (sum == cur_num) {
                    valid = true;
                    b = n = numbers.size();  //break out of the inner loops because this is valid
                }
            }
        }

        if (!valid) {
            return cur_num;
        }
    }

    //no number was invalid
    return -1;
}

vector<double> Get_Range(vector<double> numbers, double invalid_number) {
    vector<double> range;
    double sum = 0;

    for (int i = 0; i < numbers.size(); i++) {
        sum = numbers[i];
        range.push_back(numbers[i]);

        for (int n = i+1; n < numbers.size(); n++) {
            sum += numbers[n];
            range.push_back(numbers[n]);

            if (sum == invalid_number) {
                i = n = numbers.size();
            }
            else if (sum > invalid_number) {
                range.clear();
                sum = 0;
                n = numbers.size(); //break out of the inner loop
            }
        }
    }

    return range;
}

int main()
{
    vector<double> numbers;
    double invalid_number;
    vector<double> range;

    numbers = Get_Numbers();

    invalid_number = Get_First_Invalid(numbers, 25);

    cout << "First invalid number is " << fixed << setprecision(0) << invalid_number << endl;

    range = Get_Range(numbers, invalid_number);

    cout << "Range: " << range[0] << " " << range[range.size()-1] << "\t(size: " << range.size() << ")\n";

    cout << "Sum of least and max is " << *max_element(range.begin(), range.end()) + *min_element(range.begin(), range.end()) << endl;

    return 0;
}
