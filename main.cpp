#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <list>
#include <vector>

using namespace std;

enum Sex
{
    Male,
    Female
};

enum Color
{
    White,
    Brown,
    Black,
    Spotted
};

const vector<string> names = {"John", "Tonny", "Jack", "Robbin", "Charls"};
const int MAX_AGE = 10;
const int MAX_VAMPIRE_AGE = 50;

class Bunny
{
private:
    string sex;
    string color;
    int age;
    string name;
    bool is_vampire = false;

public:
    Bunny()
    {
        random_device rd;
        default_random_engine e1(rd());
        uniform_int_distribution<int> uniform_dist_vampire(0, 99);
        uniform_int_distribution<int> uniform_dist_sex(0, 1);
        uniform_int_distribution<int> uniform_dist_color(0, 3);
        uniform_int_distribution<int> uniform_dist_name(0, 4);

        if (uniform_dist_sex(e1) == Male) sex = "male";
        else sex = "female";

        if (uniform_dist_vampire(e1) < 2) is_vampire = true;

        switch (uniform_dist_color(e1)) {
            case White: color = "white";
                break;
            case Brown: color = "brown";
                break;
            case Black: color = "black";
                break;
            case Spotted: color = "spotted";
                break;
            default: color = "white";
                break;
        }

        name = names[uniform_dist_name(e1)];

        age = 0;
    }

    void showInfo()
    {
        cout << "This bunny's name is " << name << endl;
        cout << "Sex: " << sex << endl;
        cout << "Color: " << color << endl;
        cout << "Age: " << age << endl;
        cout << "Is vampire: " << (is_vampire ? "ture" : "false") << endl;
    }

    int getAge() const
    {
        return age;
    }

    void incrementAge()
    {
        age++;
    }

    string getSex() const
    {
        return sex;
    }

    string getColor() const
    {
        return color;
    }

    void setColor(const string& color)
    {
        this->color = color;
    }

    bool isVampire() const
    {
        return is_vampire;
    }

    void beVampire()
    {
        is_vampire = true;
    }
};

void showDetails(const list<Bunny>& bunnies, const int i);

int main() {
    list<Bunny> bunnies;
    int num_adult_male = 0;
    int num_vampire = 0;
    for (int i = 0; i < 5; i++) {
        Bunny bunny;
        bunnies.push_back(bunny);
        if (bunny.isVampire()) num_vampire++;
    }

    int i = 0;
    while (true) {
        cout << "Turn " << i << endl;
        list<Bunny> baby_bunnies;

        for (auto p = bunnies.begin(); p != bunnies.end(); p++) {
            p->incrementAge();

            if (!p->isVampire()) {
                if (p->getAge() >= 2) {
                    if (num_adult_male > 0 && p->getSex() == "female") {
                        Bunny baby_bunny;
                        baby_bunny.setColor(p->getColor());
                        if (baby_bunny.isVampire()) {
                            num_vampire++;
                        }
                        baby_bunnies.push_back(baby_bunny);
                    }
                    if (p->getAge() == 2 && p->getSex() == "male") {
                        num_adult_male++;
                    }
                }
            }

            if (!p->isVampire() && p->getAge() > MAX_AGE) {
                if (p->getSex() == "male") num_adult_male--;
                bunnies.erase(p);
            }
            else if (p->isVampire() && p->getAge() > MAX_VAMPIRE_AGE) {
                num_vampire--;
                bunnies.erase(p);
            }
        }

        bunnies.splice(bunnies.end(), baby_bunnies);

        int num_new_vampire = 0;
        for (auto& bunny : bunnies) {
            if (num_new_vampire == num_vampire) break;
            if (!bunny.isVampire()) {
                bunny.beVampire();
                num_new_vampire++;
            }
        }
        num_vampire += num_new_vampire;

        if (bunnies.empty()) break;

        showDetails(bunnies, i++);
        if (i == 100) break;
    }

    return 0;
}


void showDetails(const list<Bunny>& bunnies, const int i)
{
    ofstream outfile;
    outfile.open("base_info.log", ios_base::app);

    int num_baby_bunnies = 0;
    int num_adult_male_bunnies = 0;
    int num_adult_female_bunnies = 0;
    int num_vampire = 0;
    for (const auto& bunny : bunnies) {
        if (bunny.isVampire()) num_vampire++;
        else {
            if (bunny.getAge() < 2) num_baby_bunnies++;
            else {
                if (bunny.getSex() == "male") num_adult_male_bunnies++;
                else num_adult_female_bunnies++;
            }
        }
    }
    outfile << "-----------------------------\nRound " << i << endl;
    outfile << "Baby num: " << num_baby_bunnies << endl;
    outfile << "Male adult num: " << num_adult_male_bunnies << endl;
    outfile << "Female adult num: " << num_adult_female_bunnies << endl;
    outfile << "Vampire num: " << num_vampire << endl;

    outfile << "Total num: " << bunnies.size() << endl;
}