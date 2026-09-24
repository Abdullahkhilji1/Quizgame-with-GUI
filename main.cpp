#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void printHeader() {
    cout << "\n==================================================\n";
    cout << "            🧠 BRAIN WARRIOR 🧠\n";
    cout << "        💥 Battle Your Brain. Beat the Clock! ⏰\n";
    cout << "==================================================\n";
}

void printLine() {
    cout << "--------------------------------------------------\n";
}

void printFinalMessage(int score) {
    if (score >= 9)
        cout << "🏆 Excellent performance! You're a genius!\n";
    else if (score >= 7)
        cout << "🌟 Very Good! Keep up the great work!\n";
    else if (score >= 5)
        cout << "👍 Good effort! You're getting there!\n";
    else
        cout << "💡 Fair. Keep practicing and you'll improve!\n";
}

class Question {
public:
    string text;
    vector<string> options;
    int correctOption;

    Question(string t, vector<string> opts, int correct) {
        text = t;
        options = opts;
        correctOption = correct;
    }

    void display() {
        printLine();
        cout << "📘 " << text << "\n";

        for (int i = 0; i < (int)options.size(); ++i) {
            cout << "  " << i + 1 << ". " << options[i] << endl;
        }

        printLine();
    }

    bool checkAnswer(int choice) {
        return choice == correctOption;
    }
};

class Quiz {
protected:
    vector<Question> questions;
    int score;

public:
    Quiz() {
        score = 0;
    }

    virtual void loadQuestions() = 0;

    int start() {

        for (int i = 0; i < 10; ++i) {

            Question& q = questions[i];

            q.display();

            cout << "🎯 Your answer (1-4): ";

            int choice = 0;
            bool answered = false;

            DWORD startTime = GetTickCount();

            while (true) {

                if (_kbhit()) {

                    char key = _getch();

                    if (key >= '1' && key <= '4') {

                        choice = key - '0';

                        cout << key << endl;

                        answered = true;

                        break;
                    }
                }

                DWORD elapsed = GetTickCount() - startTime;

                int remaining = 10 - (int)(elapsed / 1000);

                if (remaining < 0)
                    remaining = 0;

                cout << "\r⏰ Time remaining: "
                     << remaining
                     << " seconds   ";

                if (elapsed >= 10000) {

                    cout << "\n⏰ Time's up! Moving to next question.\n";

                    break;
                }

                Sleep(100);
            }

            if (answered && q.checkAnswer(choice)) {

                cout << "✔ Correct!\n";
                score++;

            }
            else if (answered) {

                cout << "✖ Wrong! Correct answer was: "
                     << q.correctOption << "\n";
            }

            Sleep(500);
        }

        printLine();

        cout << "🎓 Final Score: "
             << score
             << "/10\n";

        printFinalMessage(score);

        printLine();

        return score;
    }
};

class MathQuiz : public Quiz {
public:

    void loadQuestions() override {

        questions = {

            {"2 + 2 = ?", {"3", "4", "5", "6"}, 2},

            {"12 * 12 = ?", {"144", "154", "124", "134"}, 1},

            {"Derivative of x^2?", {"x", "2x", "x^2", "None"}, 2},

            {"Square root of 81?", {"7", "8", "9", "10"}, 3},

            {"What is 15% of 200?", {"20", "25", "30", "35"}, 3},

            {"5 + 3 * 2 = ?", {"16", "11", "10", "8"}, 2},

            {"What is 10 squared?", {"100", "20", "30", "10"}, 1},

            {"LCM of 4 and 6?", {"10", "12", "14", "8"}, 2},

            {"(3^2) + (4^2) = ?", {"25", "9", "16", "30"}, 1},

            {"Log base 10 of 1000 is?", {"2", "3", "4", "1"}, 2}
        };
    }
};

class ScienceQuiz : public Quiz {
public:

    void loadQuestions() override {

        questions = {

            {"Water formula?", {"H2O", "O2", "H2", "CO2"}, 1},

            {"Closest planet to Sun?", {"Venus", "Earth", "Mercury", "Mars"}, 3},

            {"Atomic number of Carbon?", {"6", "12", "14", "8"}, 1},

            {"Speed of light unit?", {"m/s", "km/hr", "cm/s", "mph"}, 1},

            {"What gas do plants absorb?", {"Oxygen", "Nitrogen", "Carbon Dioxide", "Helium"}, 3},

            {"Largest organ in human body?", {"Skin", "Heart", "Liver", "Lung"}, 1},

            {"Vitamin from Sun?", {"A", "B", "C", "D"}, 4},

            {"Which cell makes energy?", {"Nucleus", "Mitochondria", "Ribosome", "Golgi"}, 2},

            {"Unit of force?", {"Newton", "Pascal", "Volt", "Joule"}, 1},

            {"Boiling point of water in Celsius?", {"90", "95", "100", "105"}, 3}
        };
    }
};

class GKQuiz : public Quiz {
public:

    void loadQuestions() override {

        questions = {

            {"Capital of India?", {"Mumbai", "Delhi", "Kolkata", "Chennai"}, 2},

            {"UNO full form?",
             {"Union Nations Org",
              "United National Org",
              "United Nations Organization",
              "None"}, 3},

            {"Who wrote 'Geetanjali'?",
             {"Tagore", "Premchand", "Kalidas", "Tulsidas"}, 1},

            {"Largest ocean?",
             {"Atlantic", "Indian", "Arctic", "Pacific"}, 4},

            {"Currency of Japan?",
             {"Yen", "Won", "Dollar", "Rupee"}, 1},

            {"Father of India?",
             {"Nehru", "Gandhi", "Patel", "Tagore"}, 2},

            {"Smallest continent?",
             {"Asia", "Europe", "Australia", "Antarctica"}, 3},

            {"Which country hosted FIFA 2022?",
             {"Qatar", "Russia", "Brazil", "USA"}, 1},

            {"First Indian in space?",
             {"Rakesh Sharma",
              "Kalpana",
              "Vikram Sarabhai",
              "APJ Abdul Kalam"}, 1},

            {"National animal of India?",
             {"Tiger", "Lion", "Elephant", "Leopard"}, 1}
        };
    }
};

int main() {

    srand(time(0));

    printHeader();

    cout << "👤 Enter your name: ";

    string username;

    getline(cin, username);

    cout << "\n📚 Select Topic:\n";
    cout << "1. Math\n";
    cout << "2. Science\n";
    cout << "3. GK\n";

    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    Quiz* quiz = nullptr;

    switch (choice) {

        case 1:
            quiz = new MathQuiz();
            break;

        case 2:
            quiz = new ScienceQuiz();
            break;

        case 3:
            quiz = new GKQuiz();
            break;

        default:
            cout << "❌ Invalid choice!\n";
            return 0;
    }

    quiz->loadQuestions();

    int finalScore = quiz->start();

    delete quiz;

    cout << "\n🙏 Thanks for playing, "
         << username
         << "!\n";

    cout << "🌟 You're amazing! Keep learning and keep shining! 🌟\n";

    cout << "🎉 Come back soon for more challenges on Brain Warrior! 🧠🔥\n";

    return 0;
}
