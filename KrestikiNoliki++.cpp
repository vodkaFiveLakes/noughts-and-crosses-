#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

bool Game_Cycle = false, Game_status = false, menu_status = false;
short current_player = 0, current_action = 0;
wstring current_player_name_1 = L"", current_player_name_2 = L"";


class Game_menu
{
public:
    void Menu()
    {
        Game_Cycle = true;
        short Select_Option;
        system("cls");
        wcout << L"Крестики-нолики++" << endl;
        cout << endl;
        wcout << L"1) Начать игру" << endl;
        wcout << L"2) Справка" << endl;
        wcout << L"3) Выйти из игры" << endl;
        cout << "> ";
        cin >> Select_Option;
        switch (Select_Option)
        {
            case 1:
            current_action = 2;
            break;
            case 2:
            current_action = 3;
            break;
            case 3:
            current_action = 4;
            break;
            default:
            current_action = 1;
            break;
        }
    }
    void Create_Player_Name()
    {
        system("cls");
        wcout << L"Игрок 1 введите своё имя: ";
        wcin >> current_player_name_1;
        wcin.clear();
        cout << endl;
        system("cls");
        wcout << L"Игрок 2 введите своё имя: ";
        wcin >> current_player_name_2;
        wcin.clear();
        Sleep(1000);
        system("cls");
        menu_status = false;
        Game_status = true;
    }
    void Help()
    {
        system("cls");
        wcout << L"Как играть?\nИгрок 1 должен выстраить линию из трёх крестиков.\nИгрок 2 должен выстраить линию из трёх ноликов.\nПервый кто выстраит линию из знаков первым тот победил.\nКак ходить?\nНужно вести адресс строки и адресс столбца (порядок не важен), после чего нужно нажать на Enter\nАдреса строки и столбца подписанны на игровом поле.\nУдачной вам игры :)" << endl;
        cin.ignore();
        cin.get();
        cin.clear();
        current_action = 1;
    }
};

class Game
{
    bool Game_won = false;
    short message_ID = 0;
    char PlayerSymbol[3][3] = { {' ', ' ', ' '},
                                {' ', ' ', ' '},
                                {' ', ' ', ' '} }; //Символы игроков
    /* Таблица (Образец)
         |a|b|c| 
        -|-|-|-|-
        1|X|O|O| 
        -|-|-|-|-
        2|O|X|O| 
        -|-|-|-|-
        3|O|O|X| 
        -|-|-|-|-
    */
    public:
    
    
        Game ()
        {
            current_player = 1;
            Table_Render();
        }

        ~Game ()
        {
            Game_status = false;
        }

        void Table_Render() //Метод для рендеринга поля и символов
        {
            system("cls");
            char Table[9][10] = { {' ', '|', 'a', '|', 'b', '|', 'c', '|', ' ', '\n'},
                                  {'-', '|', '-', '|', '-', '|', '-', '|', '-', '\n'},
                                  {'1', '|', PlayerSymbol[0][0], '|', PlayerSymbol[0][1], '|', PlayerSymbol[0][2], '|', ' ', '\n'},
                                  {'-', '|', '-', '|', '-', '|', '-', '|', '-', '\n'},
                                  {'2', '|', PlayerSymbol[1][0], '|', PlayerSymbol[1][1], '|', PlayerSymbol[1][2], '|', ' ', '\n'},
                                  {'-', '|', '-', '|', '-', '|', '-', '|', '-', '\n'},
                                  {'3', '|', PlayerSymbol[2][0], '|', PlayerSymbol[2][1], '|', PlayerSymbol[2][2], '|', ' ', '\n'},
                                  {'-', '|', '-', '|', '-', '|', '-', '|', '-', '\n'},
                                  {' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '\n'} }; //Игровое поле
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    cout << Table[i][j];
                }
            }
            switch (message_ID)
            {
                case 1:
                wcout << L"Код ошибки \"ERROR:(WRONG_ARGUMENT)\"" << endl;
                break;
                case 2:
                wcout << L"Клетка занята" << endl;
                break;
                default:
                break;
            }
        }

        void First_Player_move()
        {
            int addres = -1, index = -1;
            string answer;
            char* user_input = new char[2];
            wcout << L"Сейчас ход " << current_player_name_1 << L":" << endl;
            cin >> answer;
            strncpy(user_input, answer.c_str(), 2);
            
            
            for (int i = 0; i < 2; i++)
            {
                //wcout << L"Вы можете сделать только один ход" << endl;
                
                switch (user_input[i])
                {
                case 'A': case 'a':
                    addres = 0;
                    break;

                case 'B': case 'b':
                    addres = 1;
                    break;

                case 'C': case 'c':
                    addres = 2;
                    break;
                }

                switch (user_input[i])
                {
                    case '1':
                        index = 0;
                        break;
                    case '2':
                        index = 1;
                        break;
                    case '3':
                        index = 2;
                        break;
                }
                
            }
            if (addres == -1 || index == -1)
            {
                cin.clear();
                current_player = 1;
                message_ID = 1;
            }
            else
            {
                if (PlayerSymbol[index][addres] != 'O' && PlayerSymbol[index][addres] != 'X')
                {
                    if (addres != -1 && index != -1)
                    {
                        PlayerSymbol[index][addres] = 'X';
                        cin.clear();
                        PlayerWinCheck(1);
                        if (Game_won == false && Game_status == true)
                        {
                            current_player = 2;
                            message_ID = 0;
                        }
                    }
                }
                else
                {
                    cin.clear();
                    current_player = 1;
                    message_ID = 2;
                }
            }
            delete[] user_input;
        }

        void Second_Player_move()
        {
            int addres = -1, index = -1;
            string answer;
            wcout << L"Сейчас ход "<< current_player_name_2 << ":" << endl;
            cin >> answer;
            char* user_input = new char[2];
            strncpy(user_input, answer.c_str(), 2);

            for (int i = 0; i < 2; i++)
            {
                switch (user_input[i])
                {
                case 'A': case 'a':
                    addres = 0;
                    break;

                case 'B': case 'b':
                    addres = 1;
                    break;

                case 'C': case 'c':
                    addres = 2;
                    break;
                }

                switch (user_input[i])
                {
                case '1':
                    index = 0;
                    break;
                case '2':
                    index = 1;
                    break;
                case '3':
                    index = 2;
                    break;
                }
            }
            
            if (addres == -1 || index == -1)
            {
                cin.clear();
                current_player = 2;
                message_ID = 1;
            }
            else
            {
                if (PlayerSymbol[index][addres] != 'X' && PlayerSymbol[index][addres] != 'O')
                {
                    if (addres != -1 && index != -1)
                    {
                        PlayerSymbol[index][addres] = 'O';
                        cin.clear();
                        PlayerWinCheck(2);
                        if (Game_won == false && Game_status == true)
                        {
                            current_player = 1;
                            message_ID = 0;
                        }
                    }
                }
                else
                {
                    cin.clear();
                    message_ID = 2;
                    current_player = 2;
                }

            }
            delete[] user_input;
        }
    void PlayerWinCheck(short PlayerID)
    {
        char Symbol = ' ';
            
        switch (PlayerID)
        {
            case 1:
                Symbol = 'X';
                if (PlayerSymbol[0][0] == Symbol && PlayerSymbol[0][1] == Symbol && PlayerSymbol[0][2] == Symbol ||
                    PlayerSymbol[1][0] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[1][2] == Symbol ||
                    PlayerSymbol[2][0] == Symbol && PlayerSymbol[2][1] == Symbol && PlayerSymbol[2][2] == Symbol ||
                    PlayerSymbol[0][0] == Symbol && PlayerSymbol[1][0] == Symbol && PlayerSymbol[2][0] == Symbol ||
                    PlayerSymbol[0][1] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[2][1] == Symbol ||
                    PlayerSymbol[0][2] == Symbol && PlayerSymbol[1][2] == Symbol && PlayerSymbol[2][2] == Symbol ||
                    PlayerSymbol[0][0] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[2][2] == Symbol ||
                    PlayerSymbol[2][0] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[0][2] == Symbol)
                {
                    system("cls");
                    wcout << current_player_name_1 << L" победил" << endl;
                    
                    Sleep(1000);
                    menu_status = true;
                    current_action = 1;
                    Game_won = true;
                    Game_status = false;
                }
            
                break;
            case 2:
                Symbol = 'O';
                if (PlayerSymbol[0][0] == Symbol && PlayerSymbol[0][1] == Symbol && PlayerSymbol[0][2] == Symbol ||
                    PlayerSymbol[1][0] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[1][2] == Symbol ||
                    PlayerSymbol[2][0] == Symbol && PlayerSymbol[2][1] == Symbol && PlayerSymbol[2][2] == Symbol ||
                    PlayerSymbol[0][0] == Symbol && PlayerSymbol[1][0] == Symbol && PlayerSymbol[2][0] == Symbol ||
                    PlayerSymbol[0][1] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[2][1] == Symbol ||
                    PlayerSymbol[0][2] == Symbol && PlayerSymbol[1][2] == Symbol && PlayerSymbol[2][2] == Symbol ||
                    PlayerSymbol[0][0] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[2][2] == Symbol ||
                    PlayerSymbol[2][0] == Symbol && PlayerSymbol[1][1] == Symbol && PlayerSymbol[0][2] == Symbol)
                {
                    system("cls");
                    wcout << current_player_name_2 << L" победил" << endl;
                    
                    Sleep(1000);
                    menu_status = true;
                    current_action = 1;
                    Game_won = true;
                    Game_status = false;
                }
                break;
        }
            short Check_Cage_is_not_NULL = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (PlayerSymbol[i][j] != ' ')
                    {
                        Check_Cage_is_not_NULL++;
                        
                    }
                }
            }
            if (Check_Cage_is_not_NULL >= 9 && Game_won != true)
            {
                system("cls");
                wcout << L"Ничья" << endl;
                
                Sleep(1000);
                menu_status = true;
                current_action = 1;
                Game_won = false;
                Game_status = false;
            }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian"); //Нужно для корректного отображения кириллицы в консоле Windows
    SetConsoleCP(1251);
    Game_menu game_menu;
    current_action = 1;
    Game_Cycle = true;
    menu_status = true;
    while (Game_Cycle)
    {
        while (menu_status)
        {
            switch (current_action)
            {
            case 1:
                game_menu.Menu();
                break;
            case 2:
                game_menu.Create_Player_Name();
                break;
            case 3:
                game_menu.Help();
                break;
            case 4:
                exit(0);
                Game_Cycle = false;
                break;
            default:
                game_menu.Menu();
                break;
            }
        }
        Game Game;
        if (menu_status == false)
        {
            while (Game_status) // Игровой цикл
            {
                switch (current_player)
                {
                case 1:
                    Game.Table_Render();
                    Game.First_Player_move();
                    break;
            
                case 2:
                    Game.Table_Render();
                    Game.Second_Player_move();
                    break;
                }
            }
        }
    }
    return 0;
}