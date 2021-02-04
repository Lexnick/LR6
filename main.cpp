#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Address {
    std::string Street;
    int HouseNumber;
    int FlatNumber;
};
struct Citizen {
    std::string FullName;
    Address CitizenAddress;
    std::string Sex;
    int Age;
};

void FullNameSort(std::vector<Citizen> &vec) {
    bool IsSorted = false;
    while (!IsSorted) {
        IsSorted = true;
        for (int i = 0; i < vec.size() - 1; i++) {
            std::string Surname1 = vec[i].FullName.substr(0, vec[i].FullName.find(' '));
            std::string Surname2 = vec[i + 1].FullName.substr(0, vec[i + 1].FullName.find(' '));
            if (Surname1 == Surname2) {
                std::string Name1 = vec[i].FullName.substr(vec[i].FullName.find(' ') + 1,
                                                           vec[i].FullName.find(' ', vec[i].FullName.find(' ')));
                std::string Name2 = vec[i + 1].FullName.substr(vec[i + 1].FullName.find(' ') + 1,
                                                               vec[i + 1].FullName.find(' ',
                                                                                        vec[i + 1].FullName.find(' ')));
                if (Name1 == Name2) {
                    std::string Patronymic1 = vec[i].FullName.substr(
                            vec[i].FullName.find(' ', vec[i].FullName.find(' ')));
                    std::string Patronymic2 = vec[i + 1].FullName.substr(
                            vec[i + 1].FullName.find(' ', vec[i + 1].FullName.find(' ')));
                    int CountOfIterations;
                    if (Patronymic1.size() > Patronymic2.size())
                        CountOfIterations = Patronymic2.size();
                    else CountOfIterations = Patronymic1.size();
                    bool IsSwapped = false;
                    for (int j = 0; j < CountOfIterations; j++) {
                        if ((Patronymic2[j] < Patronymic1[j]) && (!IsSwapped)) {
                            std::swap(vec[i], vec[i + 1]);
                            IsSorted = false;
                            IsSwapped = true;
                        } else if (Patronymic1[j] < Patronymic2[j]) {
                            IsSwapped = true;
                        }
                    }

                } else {
                    int CountOfIterations;
                    if (Name1.size() > Name2.size())
                        CountOfIterations = Name2.size();
                    else CountOfIterations = Name1.size();
                    bool IsSwapped = false;
                    for (int j = 0; j < CountOfIterations; j++) {
                        if ((Name2[j] < Name1[j]) && (!IsSwapped)) {
                            std::swap(vec[i], vec[i + 1]);
                            IsSorted = false;
                            IsSwapped = true;
                        } else if (Name1[j] < Name2[j]) {
                            IsSwapped = true;
                        }
                    }
                }
            } else {
                int CountOfIterations;
                if (Surname1.size() > Surname2.size())
                    CountOfIterations = Surname2.size();
                else CountOfIterations = Surname1.size();
                bool IsSwapped = false;
                for (int j = 0; j < CountOfIterations; j++) {
                    if ((Surname2[j] < Surname1[j]) && (!IsSwapped)) {
                        std::swap(vec[i], vec[i + 1]);
                        IsSorted = false;
                        IsSwapped = true;
                    } else if (Surname1[j] < Surname2[j]) {
                        IsSwapped = true;
                    }
                }
            }
        }
    }
}

void OutputTextBinary(std::vector<Citizen> &vec){
    std::ofstream outputFile("HMO base binary.txt", std::ios::binary);
    for (auto &i: vec) {
        //writing a Name
        int NameSize=i.FullName.size();
        outputFile.write(reinterpret_cast<char*>(&NameSize),sizeof(NameSize));
        for (int j=0; j<NameSize; j++){
            char LetterOut=i.FullName[j];
            outputFile.write(reinterpret_cast<char*>(&LetterOut),sizeof(LetterOut));
        }
        //writing a Street
        int StreetSize=i.CitizenAddress.Street.size();
        outputFile.write(reinterpret_cast<char*>(&StreetSize),sizeof(StreetSize));
        for (int j=0; j<StreetSize; j++){
            char LetterOut=i.CitizenAddress.Street[j];
            outputFile.write(reinterpret_cast<char*>(&LetterOut),sizeof(LetterOut));
        }
        //writing a House number
        int HouseNumber=i.CitizenAddress.HouseNumber;
        outputFile.write(reinterpret_cast<char*>(&HouseNumber),sizeof(HouseNumber));
        //Flat
        int FlatNumber=i.CitizenAddress.FlatNumber;
        outputFile.write(reinterpret_cast<char*>(&FlatNumber),sizeof(FlatNumber));
        //Sex
        int SexSize=i.Sex.size();
        outputFile.write(reinterpret_cast<char*>(&SexSize),sizeof(SexSize));
        for (int j=0; j<SexSize; j++){
            char LetterOut=i.Sex[j];
            outputFile.write(reinterpret_cast<char*>(&LetterOut),sizeof(LetterOut));
        }
        //age
        int Age=i.Age;
        outputFile.write(reinterpret_cast<char*>(&Age),sizeof(Age));
    }
    outputFile.close();
}

void InputTextBinary(std::vector<Citizen> &vec){
    std::ifstream inputFile("HMO base binary.txt", std::ios::binary);
    for (auto &i: vec) {
        //writing a Name
        int NameSize=0;
        inputFile.read(reinterpret_cast<char*>(&NameSize),sizeof(NameSize));
        for (int j=0; j<NameSize; j++){
            char LetterIn=0;
            inputFile.read(reinterpret_cast<char*>(&LetterIn),sizeof(LetterIn));
            i.FullName.push_back(LetterIn);
        }
        //writing a Street
        int StreetSize=0;
        inputFile.read(reinterpret_cast<char*>(&StreetSize),sizeof(StreetSize));
        for (int j=0; j<StreetSize; j++){
            char LetterIn=0;
            inputFile.read(reinterpret_cast<char*>(&LetterIn),sizeof(LetterIn));
            i.CitizenAddress.Street.push_back(LetterIn);
        }
        //writing a House number
        int HouseNumber=0;
        inputFile.read(reinterpret_cast<char*>(&HouseNumber),sizeof(HouseNumber));
        i.CitizenAddress.HouseNumber=HouseNumber;
        //Flat
        int FlatNumber=0;
        inputFile.read(reinterpret_cast<char*>(&FlatNumber),sizeof(FlatNumber));
        i.CitizenAddress.FlatNumber=FlatNumber;
        int SexSize=0;
        inputFile.read(reinterpret_cast<char*>(&SexSize),sizeof(SexSize));
        for (int j=0; j<SexSize; j++){
            char LetterIn=0;
            inputFile.read(reinterpret_cast<char*>(&LetterIn),sizeof(LetterIn));
            i.Sex.push_back(LetterIn);
        }
        //age
        int Age=0;
        inputFile.read(reinterpret_cast<char*>(&Age),sizeof(Age));
        i.Age=Age;
    }
    inputFile.close();
}

void operator<<(const std::string& File, std::vector<Citizen>& vec)
{
    std::ofstream outputFile(File);
    for (const auto& i: vec) {
        outputFile << i.FullName << ' ' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                   << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    outputFile.close();
}

void operator>>(const std::string& File, std::vector<Citizen>& vec)
{
    std::ifstream inputFile(File);
    int i = 0;
    while ((!inputFile.eof()) && (i < vec.size())) {
        std::string str;
        inputFile >> str;
        vec[i].FullName = str;
        vec[i].FullName += ' ';
        inputFile >> str;
        vec[i].FullName += str;
        vec[i].FullName += ' ';
        inputFile >> str;
        vec[i].FullName += str;
        inputFile >> str;
        vec[i].CitizenAddress.Street = str;
        inputFile >> str;
        vec[i].CitizenAddress.HouseNumber = std::stoi(str);
        inputFile >> str;
        vec[i].CitizenAddress.FlatNumber = std::stoi(str);
        inputFile >> str;
        vec[i].Age = std::stoi(str);
        inputFile >> str;
        vec[i].Sex = str;
        i++;
    }
    inputFile.close();
}

int main() {
    std::vector<Citizen> HMO =
            {{"Zubenko Michail Petrovich",       {"Arbat",       1,  128}, "Male",   48},
             {"Ivanov Ivan Ivanovich",           {"Kolcevaya",   13, 13},  "Male",   20},
             {"Antonov Pavel Maximovich",        {"Kolcevaya",   12, 154}, "Male",   14},
             {"Borisov Artemiy Vsevolodovich",   {"Ryabinivaya", 23, 48},  "Male",   5},
             {"Pavlova Viktoria Pavlovna",       {"Kolcevaya",   3,  18},  "Female", 4},
             {"Konstantinov Ivan Alexandrovich", {"Ryabinivaya", 5,  76},  "Male",   55},
             {"Antonov Daniil Kirillovich",      {"Ryabinivaya", 24, 205}, "Male",   6},
             {"Chernisheva Fatima Markovna",     {"Kolcevaya",   43, 555}, "Female", 7},
             {"Markina Elizaveta Mihailovna",    {"Rabochaya",   1,  128}, "Female", 18},
             {"Vereschagin Roman Andreevich",    {"Arbat",       1,  128}, "Male",   36},
             {"Markina Elizaveta Antonovna",     {"Kolcevaya",   1,  128}, "Female", 3},
             {"Shaposhnikov Mark Serafimovich",  {"Ryabinivaya", 1,  128}, "Male",   1},
             {"Serevryakov Fedor Dmitrievich",   {"Rabochaya",   1,  128}, "Male",   43},
             {"Bogomolova Alina Vladimirovna",   {"Rabochaya",   1,  128}, "Female", 60},
             {"Ryabova Eva Makarovna",           {"Kolcevaya",   1,  128}, "Female", 2}};
    FullNameSort(HMO);
    for (auto & i : HMO) {
        std::cout << i.FullName << std::endl;
    }
    std::cout<<"-------------"<<std::endl;

    std::cout << "Enter the street name" << std::endl;
    std::string InputStreet;
    std::cin >> InputStreet;
    int count = 0;
    for (auto &i: HMO) {
        if ((i.CitizenAddress.Street == InputStreet) && (i.Age < 7))
            count++;
    }
    std::cout << count << " children under 7 live on " << InputStreet << " street:" << std::endl;
    for (auto &i: HMO) {
        if ((i.CitizenAddress.Street == InputStreet) && (i.Age < 7))
            std::cout << i.FullName << std::endl;//printing value and list of objects
    }
    std::cout<<"-------------"<<std::endl;

    std::vector<Citizen> BaseBinaryTest(HMO.size());
    OutputTextBinary(HMO);
    InputTextBinary(BaseBinaryTest);
    for (auto &i:BaseBinaryTest) {
        std::cout << i.FullName << ' ' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                  << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    std::cout<<"-------------"<<std::endl;

    std::vector<Citizen> BaseTextTest(HMO.size());
    "HMO 123.txt"<<HMO;
    "HMO 123.txt">>BaseTextTest;
    for (auto &i:BaseTextTest) {
        std::cout << i.FullName << ' ' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                  << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    std::cout<<"-------------"<<std::endl;

    return 0;
}