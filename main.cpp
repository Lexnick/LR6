#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

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
    std::set<std::string> SetBase;
    for (auto &VecElement: vec) {
        SetBase.insert(VecElement.FullName);
    }
    auto iter = SetBase.begin();
    for (int i = 0; i < vec.size(); i++) {
        for (int j = i + 1; j < vec.size(); j++) {
            if (*iter == vec[j].FullName) std::swap(vec[i], vec[j]);
        }
        ++iter;
    }
}


void OutputTextBinary(std::vector<Citizen> &vec) {
    std::ofstream outputFile("HMO base binary.txt", std::ios::binary);
    int Size = vec.size();
    outputFile.write(reinterpret_cast<char *>(&Size), sizeof(Size));
    for (auto &BaseElement: vec) {

        int NameSize = BaseElement.FullName.size() + 1;
        outputFile.write(reinterpret_cast<char *>(&NameSize), sizeof(NameSize));
        int StreetSize = BaseElement.CitizenAddress.Street.size() + 1;
        outputFile.write(reinterpret_cast<char *>(&StreetSize), sizeof(StreetSize));
        int SexSize = BaseElement.Sex.size() + 1;
        outputFile.write(reinterpret_cast<char *>(&SexSize), sizeof(SexSize));

        outputFile.write(reinterpret_cast<char *>(&BaseElement.FullName), NameSize);

        outputFile.write(reinterpret_cast<char *>(&BaseElement.CitizenAddress.Street), StreetSize);

        outputFile.write(reinterpret_cast<char *>(&BaseElement.Sex), SexSize);

        int HouseNumber = BaseElement.CitizenAddress.HouseNumber;
        outputFile.write(reinterpret_cast<char *>(&HouseNumber), sizeof(HouseNumber));

        int FlatNumber = BaseElement.CitizenAddress.FlatNumber;
        outputFile.write(reinterpret_cast<char *>(&FlatNumber), sizeof(FlatNumber));

        int Age = BaseElement.Age;
        outputFile.write(reinterpret_cast<char *>(&Age), sizeof(Age));

    }
    outputFile.close();
}

void InputTextBinary(std::vector<Citizen> &vec) {

    std::ifstream inputFile("HMO base binary.txt", std::ios::binary);
    int Size = 0;
    inputFile.read(reinterpret_cast<char *>(&Size), sizeof(Size));
    for (int i = 0; i < Size; i++) {
        Citizen Person;

        int NameSize = 0;
        inputFile.read(reinterpret_cast<char *>(&NameSize), sizeof(NameSize));
        int StreetSize = 0;
        inputFile.read(reinterpret_cast<char *>(&StreetSize), sizeof(StreetSize));
        int SexSize = 0;
        inputFile.read(reinterpret_cast<char *>(&SexSize), sizeof(SexSize));

        char *FullName = new char[NameSize];
        inputFile.read(reinterpret_cast<char *>(&FullName), NameSize);
        std::string PersonFullName(FullName);
        Person.FullName = PersonFullName;

        char *Street = new char[StreetSize];
        inputFile.read(reinterpret_cast<char *>(&Street), StreetSize);
        std::string PersonStreet(Street);
        Person.CitizenAddress.Street = PersonStreet;

        char *Sex = new char[SexSize];
        inputFile.read(reinterpret_cast<char *>(&Sex), SexSize);
        std::string ThisSex(Sex);
        Person.Sex = ThisSex;

        int HouseNumber = 0;
        inputFile.read(reinterpret_cast<char *>(&HouseNumber), sizeof(HouseNumber));
        Person.CitizenAddress.HouseNumber = HouseNumber;

        int FlatNumber = 0;
        inputFile.read(reinterpret_cast<char *>(&FlatNumber), sizeof(FlatNumber));
        Person.CitizenAddress.FlatNumber = FlatNumber;

        int Age = 0;
        inputFile.read(reinterpret_cast<char *>(&Age), sizeof(Age));
        Person.Age = Age;
        vec.push_back(Person);
        delete[]FullName;
        delete[]Street;
        delete[]Sex;
    }
    inputFile.close();
}

void operator<<(const std::string &File, std::vector<Citizen> &vec) {
    std::ofstream outputFile(File);
    for (const auto &i: vec) {
        outputFile << i.FullName << '\n' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                   << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    outputFile.close();
}

void operator>>(const std::string &File, std::vector<Citizen> &vec) {
    std::ifstream inputFile(File);
    int i = 0;
    while ((!inputFile.eof()) && (i < vec.size())) {
        std::string str;
        std::getline(inputFile, str);
        vec[i].FullName = str;
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
        inputFile.ignore();
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

    std::vector<Citizen> BaseBinaryTest;
    OutputTextBinary(HMO);
    InputTextBinary(BaseBinaryTest);
    for (auto &i:BaseBinaryTest) {
        std::cout << i.FullName << ' ' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                  << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    std::cout << "-------------" << std::endl;
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
