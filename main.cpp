
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

bool operator==(const Citizen &S1, const Citizen &S2) {
    return (S1.FullName == S2.FullName);
}

bool operator!=(const Citizen &S1, const Citizen &S2) {
    return !(S1 == S2);
}

bool operator>(const Citizen &S1, const Citizen &S2) {
    return (S1.FullName > S2.FullName);
}

bool operator<(const Citizen &S1, const Citizen &S2) {
    return (S1.FullName < S2.FullName);
}

void FullNameSort(std::vector<Citizen> &vec) {
    std::set<Citizen> SetBase;
    for (auto &VecElement: vec) {
        SetBase.insert(VecElement);
    }
    std::transform(SetBase.begin(), SetBase.end(), vec.begin(), [](const Citizen &Element) { return Element; });
}


void OutputTextBinary(std::vector<Citizen> &vec) {
    std::ofstream outputFile("HMO base binary.txt", std::ios::binary);
    int Size = vec.size();
    outputFile.write(reinterpret_cast<char *>(&Size), sizeof(Size));
    for (auto &BaseElement: vec) {

        int NameSize = BaseElement.FullName.size()+1;
        outputFile.write(reinterpret_cast<char *>(&NameSize), sizeof(NameSize));
        int StreetSize = BaseElement.CitizenAddress.Street.size()+1;
        outputFile.write(reinterpret_cast<char *>(&StreetSize), sizeof(StreetSize));
        int SexSize = BaseElement.Sex.size()+1;
        outputFile.write(reinterpret_cast<char *>(&SexSize), sizeof(SexSize));

        outputFile.write(BaseElement.FullName.c_str(), NameSize);

        outputFile.write(BaseElement.CitizenAddress.Street.c_str(),
                         StreetSize);

        outputFile.write(BaseElement.Sex.c_str(),SexSize);

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
        Citizen Element;

        int NameSize = 0;
        inputFile.read(reinterpret_cast<char *>(&NameSize), sizeof(NameSize));
        int StreetSize = 0;
        inputFile.read(reinterpret_cast<char *>(&StreetSize), sizeof(StreetSize));
        int SexSize = 0;
        inputFile.read(reinterpret_cast<char *>(&SexSize), sizeof(SexSize));

        char* FullName=new char[NameSize];
        inputFile.read(FullName, NameSize);
        Element.FullName=FullName;
        delete [] FullName;

        char* Street=new char[StreetSize];
        inputFile.read(Street, StreetSize);;
        Element.CitizenAddress.Street=Street;
        delete [] Street;

        char* Sex=new char[SexSize];
        inputFile.read(Sex, SexSize);
        Element.Sex=Sex;
        delete [] Sex;

        inputFile.read(reinterpret_cast<char *>(&Element.CitizenAddress.HouseNumber),
                       sizeof(Element.CitizenAddress.HouseNumber));


        inputFile.read(reinterpret_cast<char *>(&Element.CitizenAddress.FlatNumber),
                       sizeof(Element.CitizenAddress.FlatNumber));

        inputFile.read(reinterpret_cast<char *>(&Element.Age), sizeof(Element.Age));
        vec.push_back(Element);
    }
    inputFile.close();
}

void operator<<(const std::string &File, std::vector<Citizen> &vec) {
    std::ofstream outputFile(File);
    outputFile << vec.size() << ' ';
    for (const auto &i: vec) {
        outputFile << i.FullName << '\n' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                   << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    outputFile.close();
}

void operator>>(const std::string &File, std::vector<Citizen> &vec) {
    std::ifstream inputFile(File);
    int Size = 0;
    std::string str;
    inputFile >> str;
    Size = stoi(str);
    int i = 0;
    while ((!inputFile.eof()) && (i < Size)) {
        Citizen Element;
        inputFile.ignore();
        std::getline(inputFile, str);
        Element.FullName = str;
        inputFile >> str;
        Element.CitizenAddress.Street = str;
        inputFile >> str;
        Element.CitizenAddress.HouseNumber = std::stoi(str);
        inputFile >> str;
        Element.CitizenAddress.FlatNumber = std::stoi(str);
        inputFile >> str;
        Element.Age = std::stoi(str);
        inputFile >> str;
        Element.Sex = str;
        vec.push_back(Element);
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
    for (auto &i : HMO) {
        std::cout << i.FullName << std::endl;
    }
    std::cout << "-------------" << std::endl;

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
    std::cout << "-------------" << std::endl;

    std::vector<Citizen> BaseBinaryTest;
    OutputTextBinary(HMO);
    InputTextBinary(BaseBinaryTest);
    for (auto &i:BaseBinaryTest) {
        std::cout << i.FullName << ' ' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                  << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    std::cout << "-------------" << std::endl;
    std::vector<Citizen> BaseTextTest;
    "HMO 123.txt" << HMO;
    "HMO 123.txt" >> BaseTextTest;
    for (auto &i:BaseTextTest) {
        std::cout << i.FullName << ' ' << i.CitizenAddress.Street << ' ' << i.CitizenAddress.HouseNumber << ' '
                  << i.CitizenAddress.FlatNumber << ' ' << i.Age << ' ' << i.Sex << std::endl;
    }
    std::cout << "-------------" << std::endl;
    return 0;
}