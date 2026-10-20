#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

void encryptWord(const char* original, char* encrypted, int key)
{
    int i = 0;

    while (original[i] != '\0')
    {
        encrypted[i] = original[i] + key;

        if (encrypted[i] > 'z')
            encrypted[i] -= 26;

        i++;
    }

    encrypted[i] = '\0';
}

void revealOneLetter(const char* original, char* encrypted)
{
    while (*original != '\0')
    {
        if (*original != *encrypted)
        {
            *encrypted = *original;
            return;
        }

        original++;
        encrypted++;
    }
}

bool checkAnswer(const char* userGuess, const char* original, int& attempts)
{
    if (strcmp(userGuess, original) == 0)
        return true;

    attempts--;
    return false;
}

bool isLowercaseWord(const char* text)
{
    if (*text == '\0')
        return false;

    while (*text != '\0')
    {
        if (*text < 'a' || *text > 'z')
            return false;

        text++;
    }

    return true;
}

enum class ReadStatus
{
    Ok,
    TooLong,
    End
};

ReadStatus readLine(char* buffer, int capacity)
{
    int i = 0;
    bool tooLong = false;
    char ch;

    while (cin.get(ch))
    {
        if (ch == '\n')
        {
            buffer[i] = '\0';

            if (tooLong)
                return ReadStatus::TooLong;

            return ReadStatus::Ok;
        }

        if (i < capacity - 1)
        {
            buffer[i] = ch;
            i++;
        }
        else
        {
            tooLong = true;
        }
    }

    buffer[i] = '\0';

    if (i == 0 && !tooLong)
        return ReadStatus::End;

    if (tooLong)
        return ReadStatus::TooLong;

    return ReadStatus::Ok;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    const char original[] = "programming";
    char encrypted[50];
    char userGuess[50];

    int key = rand() % 5 + 1;
    int attempts = 3;

    encryptWord(original, encrypted, key);

    cout << "зашифрованное слово: " << encrypted << endl;

    while (attempts > 0)
    {
        cout << "осталось попыток: " << attempts << endl;
        cout << "введите слово или hint: ";

        ReadStatus status = readLine(userGuess, 50);

        if (status == ReadStatus::End)
            return 0;

        if (status == ReadStatus::TooLong)
        {
            cout << "слишком длинный ввод" << endl;
            continue;
        }

        if (strcmp(userGuess, "hint") == 0)
        {
            revealOneLetter(original, encrypted);
            cout << "подсказка: " << encrypted << endl;
            continue;
        }

        if (!isLowercaseWord(userGuess))
        {
            cout << "неверный ввод" << endl;
            continue;
        }

        if (checkAnswer(userGuess, original, attempts))
        {
            cout << "вы победили" << endl;
            return 0;
        }

        cout << "неверно" << endl;
    }

    cout << "вы проиграли" << endl;
    cout << "правильное слово: " << original << endl;

    return 0;
}
