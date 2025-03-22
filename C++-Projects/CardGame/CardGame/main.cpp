#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Card {
private:
    string color;
    string shape;
    int number;
    string symbol;

public:
    Card(string shape, int number) {
        setCardShape(shape);
        setCardNumber(number);
        setCardSymbol(number);
        setCardColor();
    }

    void setCardShape(string s) {
        if (s == "spades" || s == "diamonds" || s == "hearts" || s == "clubs") {
            shape = s;
        } else {
            shape = "wrong shape";
        }
    }

    void setCardNumber(int n) {
        if (n >= 1 && n <= 13) {
            number = n;
        } else {
            number = 0;
        }
    }

    void setCardSymbol(int n) {
        if (n >= 1 && n <= 13) {
            string symbols[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
            symbol = symbols[n - 1];
        } else {
            symbol = "\0";
        }
    }

    void setCardColor() {
        if (shape == "diamonds" || shape == "hearts") {
            color = "red";
        } else if (shape == "spades" || shape == "clubs") {
            color = "black";
        } else {
            color = "unknown";
        }
    }

    string getCardColor() { return color; }
    string getCardShape() { return shape; }
    int getCardNumber() { return number; }
    string getCardSymbol() { return symbol; }
};

void random_card() {
    string shapes[] = {"spades", "diamonds", "hearts", "clubs"};
    int rand_shape = rand() % 4;
    int rand_number = (rand() % 13) + 1;

    Card card(shapes[rand_shape], rand_number);
    
    cout << "Card Shape: " << card.getCardShape() << endl;
    cout << "Card Symbol: " << card.getCardSymbol() << endl;
    cout << "Card Color: " << card.getCardColor() << endl;
}

int main() {
    srand(time(0));
    random_card();
    return 0;
}
