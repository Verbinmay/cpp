//
//  main.cpp
//  jon
//
//  Created by Mark Maistrenko on 10.01.23.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>
#include <cctype>

using namespace std;

void clearing();
void beginningOfDrawning(int rr);
void middleOfDrawning(string tt);
void endOfDrawning(int uu);

int main(int argc, const char *argv[])
{
    cout << "The game has started , you will need to guess the word." << endl;
    int counterOfBegginingTheGame = 0; // Возобновляет игру при желании
    do
    {
        int numberOfLetter;
        int checkForCorrectNumber = 0; // Проверяет правильность введенного числа
        do
        {
            cout << "Choose a number of letters from 4 to 7 " << endl;
            cin >> numberOfLetter;
            if (numberOfLetter >= 4 && numberOfLetter <= 7)
            {
                checkForCorrectNumber++;
            }
            else
            {
                clearing();
            }
        } while (checkForCorrectNumber < 1);

        string nameTXT;

        nameTXT = to_string(numberOfLetter) + ".txt"; // Название нужного нам файла

        vector<string> allWords;

        ifstream inFile(nameTXT);
        if (!inFile.is_open())
        {

            cout << "Can't open the file " << nameTXT << '\n';
        }
        else
        {

            // Считает сколько строк и вынимает файлы из файла в вектор allWords
            int numberOfStrings = 0;
            char *str = new char[numberOfLetter];

            while (!inFile.eof())
            {
                inFile.getline(str, numberOfLetter + 1, '\n');

                allWords.push_back(str);
                numberOfStrings++;
            }
            inFile.close();
            delete[] str;

            // Рандомный номер

            int randomNum = 1 + rand() % numberOfStrings;

            // Нахождение этой строки в векторе

            string hiddenWord = allWords[randomNum];

            // Преобразование строки в массив строк по буквам

            string normalChar[numberOfLetter];
            char *chars = new char[hiddenWord.length() + 1];
            hiddenWord.copy(chars, hiddenWord.length());
            chars[hiddenWord.length()] = '\0';
            for (int aa = 0; aa < hiddenWord.length(); aa++)
            {
                char o1 = chars[aa];
                string o2;
                o2.push_back(o1);
                normalChar[aa] = o2;
            }

            // Вступление

            int counterOfWin = 0;                    // Cчитает моментальное угадывание слова
            int attempts = numberOfLetter + 3;       // Счетчик попыток угадать слово
            string invisibleLetters[numberOfLetter]; // Отображает слово, заменяя букры чертами _
            for (int bb = 0; bb < numberOfLetter; bb++)
            {
                invisibleLetters[bb] = "_";
            }

            vector<string> enteredWords = {""}; // Вектор с уже введенными словами
            string verifiedWord;                // Cтрока , введенная пользователем, после прохождения проверок

            do
            {
                int counterOfRequestTheWord = 0;
                do
                {
                    cout << '\n'
                         << "Here is your word , you have " << attempts << " attempts to guess it " << endl;

                    // Выводит подчеркивания по одному на экран

                    for (string &сс : invisibleLetters)
                    {
                        cout << сс << ' ';
                    };

                    // Запрос слова

                    cout << '\n'
                         << '\n'
                         << "Insert your word here" << endl;
                    string newWord;
                    cin >> newWord;

                    transform(newWord.begin(), newWord.end(), newWord.begin(), static_cast<int (*)(int)>(std::tolower)); // Нижний регистр

                    // Механизм поиска необходимого слова в словаре

                    bool fileSearchingInVector = false;
                    for (int dd = 0; dd < numberOfStrings; dd++)
                    {
                        if (newWord == allWords[dd])
                        {
                            fileSearchingInVector = true;
                            break;
                        }
                    };

                    // Преобразование и сверка

                    if (newWord.length() != numberOfLetter)
                    {
                        cout << "Lenth of your word sould be equal to: " << numberOfLetter << endl;
                        clearing();
                    }
                    else if (fileSearchingInVector == false)
                    {
                        cout << "This word is not included in our dictionary" << endl;
                        clearing();
                    }
                    else
                    {
                        verifiedWord = newWord;
                        counterOfRequestTheWord++;
                    };
                } while (counterOfRequestTheWord < 1);

                // проверки закончены

                int checkOfUsedWord = 0; // Проверка на повторяющийся ввод идентичного слова
                for (int ff = 0; ff < numberOfLetter + 4; ff++)
                {
                    if (enteredWords[ff] == verifiedWord)
                    {
                        checkOfUsedWord++;
                    }
                }

                if (verifiedWord == hiddenWord)
                {
                    cout << "Congratulations! You won with " << attempts << " attemps remaining!" << endl;
                    counterOfWin++;
                    break;
                }
                else
                {
                    if (checkOfUsedWord > 0)
                    {
                        cout << "This word you have already used. Please, insert another one." << endl;
                        continue;
                    }
                    else
                    {
                        // Создание массива со строчками для введенного слова
                        string verifiedWordArr[numberOfLetter];
                        char *yourWordArr = new char[verifiedWord.length() + 1];
                        verifiedWord.copy(yourWordArr, verifiedWord.length());
                        yourWordArr[verifiedWord.length()] = '\0';
                        for (int gg = 0; gg < verifiedWord.length(); gg++)
                        {
                            char i1 = yourWordArr[gg];
                            string i2;
                            i2.push_back(i1);
                            verifiedWordArr[gg] = i2;
                        }

                        // Массивы на все три случая

                        string goodExp[numberOfLetter];
                        string normalExp[numberOfLetter];
                        string badExp[numberOfLetter];
                        for (int hh = 0; hh < numberOfLetter; hh++)
                        {
                            badExp[hh] = verifiedWordArr[hh];
                        };

                        int linesCounter = 0; // Нужен для рисования

                        // Распихиваем строки букв по соответствующим массивам

                        for (int jj = 0; jj < numberOfLetter; jj++)
                        {
                            for (int kk = 0; kk < numberOfLetter; kk++)
                            {
                                if (verifiedWordArr[jj] == normalChar[kk] && jj == kk)
                                {
                                    goodExp[jj] = normalChar[kk];
                                    badExp[jj] = "";
                                    invisibleLetters[jj] = verifiedWord[kk];
                                }
                                else if (verifiedWordArr[jj] == normalChar[kk])
                                {
                                    int normalLettersInWordCounter = 0;
                                    for (int ll = 0; ll < numberOfLetter; ll++)
                                    {
                                        if (normalExp[ll] == verifiedWordArr[jj])
                                        {
                                            normalLettersInWordCounter++;
                                        }
                                    };
                                    if (normalLettersInWordCounter == 0)
                                    {
                                        linesCounter++;
                                        for (int mm = 0; mm < numberOfLetter; mm++)
                                        {
                                            if (normalExp[mm] == "")
                                            {
                                                normalExp[mm] = normalChar[kk];
                                                break;
                                            }
                                        };
                                    };

                                    badExp[jj] = "";
                                }
                            }
                        }

                        //                         _ _ _ _
                        //                        |s|o|m|e|
                        //                         - - - -
                        //
                        // Рисование ответа программы

                        cout << '\n'
                             << "Right char and place: " << endl;

                        beginningOfDrawning(numberOfLetter);
                        for (auto nn : goodExp)
                        {
                            if (nn == "")
                            {
                                cout << nn << " |";
                            }
                            else
                            {
                                cout << nn << "|";
                            }
                        }

                        endOfDrawning(numberOfLetter);

                        cout << '\n'
                             << "right char: " << endl;
                        beginningOfDrawning(linesCounter);

                        for (auto oo : normalExp)
                        {
                            middleOfDrawning(oo);
                        }

                        endOfDrawning(linesCounter);

                        cout << '\n'
                             << "wrong char and place: " << endl;
                        int schetchikWrongChar = 0;
                        for (int pp = 0; pp < numberOfLetter; pp++)
                        {
                            if (badExp[pp] != "")
                            {
                                schetchikWrongChar++;
                            }
                        };

                        beginningOfDrawning(schetchikWrongChar);
                        for (auto qq : badExp)
                        {
                            middleOfDrawning(qq);
                        }
                        endOfDrawning(schetchikWrongChar);

                        enteredWords[(numberOfLetter + 4) - attempts - 1] = verifiedWord;
                        attempts--;
                    }
                }
            } while (counterOfWin < 1 && attempts > 0);

            if (attempts == 0)
            {
                cout << '\n'
                     << "You died" << endl;
                cout << '\n'
                     << "You word was: " << hiddenWord << endl;
            }

            cout << "Would you like to play again? Press 1 to finish the game or 0 to restart " << endl;
            cin >> counterOfBegginingTheGame;
        }

    } while (counterOfBegginingTheGame != 1);
    cin.get();
    return 0;
};

void clearing()
{
    cin.clear();
    fflush(stdin);
}

void beginningOfDrawning(int rr)
{
    for (int ss = 0; ss < rr; ss++)
    {
        cout << " _";
    };
    cout << '\n'
         << "|";
};

void middleOfDrawning(string tt)
{
    if (tt == "")
    {
        cout << tt << "";
    }
    else
    {
        cout << tt << "|";
    }
};

void endOfDrawning(int uu)
{
    cout << '\n';
    for (int ww = 0; ww < uu; ww++)
    {
        cout << " -";
    };
};

