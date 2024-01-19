#include <iostream>
using namespace std;
void printBattlefield(int** board, int size)
{
    cout << "  ";
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i + 1;
        cout << "|";
        for (int j = 0; j < size; j++)
        {
            cout << board[i][j];
            if (j != size - 1)
            {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
}
void chooseNumberOfShips(int& cruisers, int& submarines, int& battleships, int& carriers, int size, int& allFields)
{
    cout << "Choose number of cruisers:";
    cin >> cruisers;
    allFields = cruisers * 2;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of cruisers:";
        cin >> cruisers;
        allFields = cruisers * 2;
    }
    cout << "Choose number of submarines:";
    cin >> submarines;
    allFields = cruisers * 2 + submarines * 3;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of submarines:";
        cin >> submarines;
        allFields = cruisers * 2 + submarines * 3;
    }
    cout << "Choose number of battleships:";
    cin >> battleships;
    allFields = cruisers * 2 + submarines * 3 + battleships * 4;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of battleships:";
        cin >> battleships;
        allFields = cruisers * 2 + submarines * 3 + battleships * 4;
    }
    cout << "Choose number of carriers:";
    cin >> carriers;
    allFields = cruisers * 2 + submarines * 3 + battleships * 4 + carriers * 5;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of carriers:";
        cin >> carriers;
        allFields = cruisers * 2 + submarines * 3 + battleships * 4 + carriers * 5;
    }
}
bool canPlaceShip(int** board, int sizeOfBoard, int sizeOfShip)
{
    int counter = 0;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; i < sizeOfBoard; i++)
        {
            if (board[i][j] == sizeOfShip)
            {
                counter++;
                if (counter == sizeOfShip)
                {
                    return 1;
                }
            }
            else
            {
                counter = 0;
            }
        }
    }
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; i < sizeOfBoard; i++)
        {
            if (board[j][i] == sizeOfShip)
            {
                counter++;
                if (counter == sizeOfShip)
                {
                    return 1;
                }
            }
            else
            {
                counter = 0;
            }
        }
    }
    return 0;
}
void placeShips(int** board, int sizeOfBoard, int sizeOfShip)
{
    cout << "Choose vertical(v) or horizontal(h) orientation:";
    char s[2];
    cin >> s;
    while ((s[0] != 'v' && s[0] != 'h') || s[1] != '\0')
    {
        cout << "Not a valid orientation!" << endl << "Choose vertical(v) or horizontal(h) orientation:";
        cin >> s;
    }
    cout << "Choose x and y coordinates:";
    int x, y, checkField;
    cin >> x >> y;
    checkField = 0;
    if (s[0] == 'v')
    {
        for (int i = 0; i < sizeOfShip; i++)
        {
            if ((y + i - 1) >= sizeOfBoard || (y + i - 1) < 0 || (x - 1) >= sizeOfBoard || (x - 1) < 0)
            {
                checkField++;
                continue;
            }
            if (board[y + i - 1][x - 1] != 0)
            {
                checkField++;
            }
        }
        if (checkField != 0)
        {
            cout << "Can't place ship there!" << endl;
            placeShips(board, sizeOfBoard, sizeOfShip);
            return;
        }
        for (int i = 0; i < sizeOfShip; i++)
        {
            board[y + i - 1][x - 1] = sizeOfShip;
        }
    }
    else
    {
        for (int i = 0; i < sizeOfShip; i++)
        {
            if ((y - 1) >= sizeOfBoard || (y - 1) < 0 || (x + i - 1) >= sizeOfBoard || (x + i - 1) < 0)
            {
                checkField++;
                continue;
            }
            if (board[y - 1][x + i - 1] != 0)
            {
                checkField++;
            }
        }
        if (checkField != 0)
        {
            cout << "Can't place ship there!" << endl;
            placeShips(board, sizeOfBoard, sizeOfShip);
            return;
        }
        for (int i = 0; i < sizeOfShip; i++)
        {
            board[y - 1][x + i - 1] = sizeOfShip;
        }
    }
    return;
}
void placeAllShips(int** board, int sizeOfBoard, int cruisers, int submarines, int battleships, int carriers)
{
    int cruisers1 = cruisers;
    int submarines1 = submarines;
    int battleships1 = battleships;
    int carriers1 = carriers;
    if (cruisers != 0)
    {
        cout << "Place cruisers:" << " " << cruisers1 << " " << "left" << endl;
    }
    for (int i = 0; i < cruisers; i++)
    {
        placeShips(board, sizeOfBoard, 2);
        cruisers1--;
        printBattlefield(board, sizeOfBoard);
        if (cruisers1 != 0)
        {
            cout << "Place cruisers:" << " " << cruisers1 << " " << "left" << endl;
        }
        else
        {

        }
    }
    if (submarines != 0)
    {
        cout << "Place submarines:" << " " << submarines1 << " " << "left" << endl;
    }
    for (int i = 0; i < submarines; i++)
    {
        placeShips(board, sizeOfBoard, 3);
        submarines1--;
        printBattlefield(board, sizeOfBoard);
        if (submarines1 != 0)
        {
            cout << "Place submarines:" << " " << submarines1 << " " << "left" << endl;
        }
    }
    if (battleships != 0)
    {
        cout << "Place battleships:" << " " << battleships1 << " " << "left" << endl;
    }
    for (int i = 0; i < battleships; i++)
    {
        placeShips(board, sizeOfBoard, 4);
        battleships1--;
        printBattlefield(board, sizeOfBoard);
        if (battleships1 != 0)
        {
            cout << "Place battleships:" << " " << battleships1 << " " << "left" << endl;
        }
    }
    if (carriers != 0)
    {
        cout << "Place carriers:" << " " << carriers1 << " " << "left" << endl;
    }
    for (int i = 0; i < carriers; i++)
    {
        placeShips(board, sizeOfBoard, 5);
        carriers1--;
        printBattlefield(board, sizeOfBoard);
        if (carriers1 != 0)
        {
            cout << "Place carriers:" << " " << carriers1 << " " << "left" << endl;
        }
    }
}
void attackField(int** playerBoard, int** visualBoard, int sizeOfBoard, int player, int& allFields)
{
    cout << "Player" << player << " " << "chooses a field to attack. Enter x and y coordiantes:";
    int x, y;
    cin >> x >> y;
    if ((x - 1) >= sizeOfBoard || (x - 1) < 0 || (y - 1) >= sizeOfBoard || (y - 1) < 0)
    {
        cout << "Field is not on board!" << endl;
        attackField(playerBoard, visualBoard, sizeOfBoard, player, allFields);
        return;
    }
    if (visualBoard[y - 1][x - 1] == 1 || visualBoard[y - 1][x - 1] == -1)
    {
        cout << "Field already hit!" << endl;
        attackField(playerBoard, visualBoard, sizeOfBoard, player, allFields);
        return;
    }
    if (playerBoard[y - 1][x - 1] != 0)
    {
        allFields--;
        visualBoard[y - 1][x - 1] = 1;
        int counter = 0;
        cout << "Ship hitted!" << endl;
    }
    else
    {
        visualBoard[y - 1][x - 1] = -1;
        cout << "No ship hit" << endl;
    }
    return;
}
int main()
{
    cout << "Enter board size:";
    int n;
    cin >> n;
    while (n < 5)
    {
        cout << "Board must be 5x5 or more!" << endl << "Enter board size:";
        cin >> n;
    }
    int** player1Zone = new int* [n];
    for (int i = 0; i < n; i++)
    {
        player1Zone[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            player1Zone[i][j] = 0;
        }
    }
    int** player2Zone = new int* [n];
    for (int i = 0; i < n; i++)
    {
        player2Zone[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            player2Zone[i][j] = 0;
        }
    }
    int** neutralBoard1 = new int* [n];
    for (int i = 0; i < n; i++)
    {
        neutralBoard1[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            neutralBoard1[i][j] = 0;
        }
    }
    int** neutralBoard2 = new int* [n];
    for (int i = 0; i < n; i++)
    {
        neutralBoard2[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            neutralBoard2[i][j] = 0;
        }
    }
    printBattlefield(neutralBoard1, n);
    int cruisers = 0;
    int submarines = 0;
    int battleships = 0;
    int carriers = 0;
    int allFields;
    chooseNumberOfShips(cruisers, submarines, battleships, carriers, n, allFields);
    printBattlefield(player1Zone, n);
    cout << "Payer1's turn" << endl;
    placeAllShips(player1Zone, n, cruisers, submarines, battleships, carriers);
    printBattlefield(player2Zone, n);
    cout << "Payer2's turn" << endl;
    placeAllShips(player2Zone, n, cruisers, submarines, battleships, carriers);
    cout << "Game begins!" << endl;
    int turn = 1;
    int allFields1 = allFields;
    int allFields2 = allFields;
    while (allFields1 != 0 && allFields2 != 0)
    {
        printBattlefield(neutralBoard1, n);
        printBattlefield(neutralBoard2, n);
        if (turn % 2 == 1)
        {
            attackField(player2Zone, neutralBoard2, n, 1, allFields2);
        }
        else
        {
            attackField(player1Zone, neutralBoard1, n, 2, allFields1);
        }
        turn++;
    }
    cout << "Game Over!" << endl;
    if (allFields2 == 0)
    {
        printBattlefield(neutralBoard1, n);
        printBattlefield(neutralBoard2, n);
        cout << "Player1 wins!" << endl;
    }
    else
    {
        printBattlefield(neutralBoard1, n);
        printBattlefield(neutralBoard2, n);
        cout << "Player2 wins!" << endl;
    }
    return 0;
}
