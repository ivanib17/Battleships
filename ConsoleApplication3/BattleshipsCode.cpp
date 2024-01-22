/**
*
* Solution to course project # 01
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Ivan Bogdanov
* @idnumber 9MI0600379
* @compiler VC
*
* kod
*
*/



#include <iostream>
#include <fstream>

//library for random number
#include <cstdlib>

using namespace std;
//these functions validate that the input is a number and if it is not we input again
void insertOnlyNumber1(char*& arr, int& x)
{
    char temp = 'A';
    int count = 0;
    while (temp != '\n')
    {
        cin.get(temp);
        if (count < x)
        {
            arr[count] = temp;
        }
        else
        {
            x++;
            char* tem = new char[x];
            for (int i = 0; i < count; i++)
            {
                tem[i] = arr[i];
            }
            delete[] arr;
            arr = new char[x];
            for (int i = 0; i < x; i++)
            {
                arr[i] = tem[i];
            }
            delete[] tem;
            arr[count] = temp;
        }
        count++;
    }
}


int convertStringToInt(char* p, int size)
{
    int number = 0;
    for (int i = 0; i < size; i++)
    {
        number = number * 10 + (p[i] - '0');
    }
    return number;
}


bool checkIfStringHasOnlyNumbers(char* p, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (p[i] < '0' || p[i] > '9')
        {
            return false;
        }
    }
    return true;
}


int insertOnlyNumber2()
{
    int x = 1, a = -1, tempor = 0;
    bool continues = 0;
    char* p = new char[x];
    while (continues == 0)
    {
        insertOnlyNumber1(p, x);
        continues = checkIfStringHasOnlyNumbers(p, x);
        if (continues == 1)
        {
            tempor = convertStringToInt(p, x - 1);
            return tempor;
        }
        else
        {
            cout << "Entry is not a number!" << endl << "Enter again:";
        }
        x = 1;
        delete[] p;
        p = new char[x];
        continues = 0;
    }
    return 0;
}

//Prints the inputed board
void printBoard(int**& board, const int& size)
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

//the player chooses the amount of ships the game is being played with
void chooseNumberOfShips(int& cruisers, int& submarines, int& battleships, int& carriers, const int& size, int& allFields)
{

    //we validate that all the choosen ships are a valid number
    cout << "Choose number of cruisers:";
    cruisers = insertOnlyNumber2();
    allFields = cruisers * 2;

    //if the number of ship fields is bigger than the fields on the entire board we choose another number of ships
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of cruisers:";
        cruisers = insertOnlyNumber2();
        allFields = cruisers * 2;
    }
    cout << "Choose number of submarines:";
    submarines = insertOnlyNumber2();
    allFields = cruisers * 2 + submarines * 3;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of submarines:";
        submarines = insertOnlyNumber2();
        allFields = cruisers * 2 + submarines * 3;
    }
    cout << "Choose number of battleships:";
    battleships = insertOnlyNumber2();
    allFields = cruisers * 2 + submarines * 3 + battleships * 4;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of battleships:";
        battleships = insertOnlyNumber2();
        allFields = cruisers * 2 + submarines * 3 + battleships * 4;
    }
    cout << "Choose number of carriers:";
    carriers = insertOnlyNumber2();
    allFields = cruisers * 2 + submarines * 3 + battleships * 4 + carriers * 5;
    while (allFields > size * size)
    {
        cout << "Not enough space on the board!" << endl << "Choose number of carriers:";
        carriers = insertOnlyNumber2();
        allFields = cruisers * 2 + submarines * 3 + battleships * 4 + carriers * 5;
    }
}

//checks if there is space for the current ship on the board
bool canPlaceShip(int** board, const int& sizeOfBoard, const int& sizeOfShip)
{
    int count;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        count = 0;
        for (int j = 0; j < sizeOfBoard; j++)
        {
            if (board[i][j] == 0)
            {
                count++;
                if (count == sizeOfShip)
                {
                    return 1;
                }
            }
            else
            {
                count = 0;
            }
        }
    }
    for (int i = 0; i < sizeOfBoard; i++)
    {
        count = 0;
        for (int j = 0; j < sizeOfBoard; j++)
        {
            if (board[j][i] == 0)
            {
                count++;
                if (count == sizeOfShip)
                {
                    return 1;
                }
            }
            else
            {
                count = 0;
            }
        }
    }
    return 0;
}

//saves the coordinates of the placed ships of the current player
void saveShipCoordinates(int*& shipsCoordinates, int& startingIndex, const int& sizeOfBoard, const int& sizeOfShip, int xCoordinate, int yCoordinate, const char& orientation)
{
    int j = startingIndex;
    if (orientation == 'v')
    {
        for (int i = startingIndex; i < j + sizeOfShip; i++)
        {

            shipsCoordinates[i] = sizeOfBoard * (yCoordinate - 1) + xCoordinate;
            yCoordinate++;
            startingIndex++;

        }
        shipsCoordinates[j + sizeOfShip] = 0;
        startingIndex++;
    }
    else
    {
        for (int i = startingIndex; i < j + sizeOfShip; i++)
        {
            shipsCoordinates[i] = sizeOfBoard * (yCoordinate - 1) + xCoordinate;
            xCoordinate++;
            startingIndex++;
        }
        shipsCoordinates[j + sizeOfShip] = 0;
        startingIndex++;
    }
}

//the player chooses where to place his current ship
void placeShips(int** board, int*& shipsCoordinates, int& sizeOfShipArray, int& startingIndex, const int& sizeOfBoard, const int& sizeOfShip)
{
    cout << "Choose vertical(v) or horizontal(h) orientation:";
    char s[2];
    cin >> s;

    //validates that the choosen orientation is horizontal or vertical
    while ((s[0] != 'v' && s[0] != 'h') || s[1] != '\0')
    {
        cout << "Not a valid orientation!" << endl << "Choose vertical(v) or horizontal(h) orientation:";
        cin >> s;
    }

    //we enter the starting coordinates of the ship and validate if they are numbers
    cout << "Choose x coordiantes:";
    int x, y, checkField;
    cin.ignore();
    x = insertOnlyNumber2();
    cout << "Choose y coordinates:";
    y = insertOnlyNumber2();
    checkField = 0;
    if (s[0] == 'v')
    {

        //we check the ship placement to see if there is another ship there or if it is outside the board
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
            placeShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, sizeOfShip);
            return;
        }

        //if the placement is valid we place the ship vertically and save it's coordinates
        for (int i = 0; i < sizeOfShip; i++)
        {
            board[y + i - 1][x - 1] = sizeOfShip;
        }
        saveShipCoordinates(shipsCoordinates, startingIndex, sizeOfBoard, sizeOfShip, x, y, s[0]);
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
            placeShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, sizeOfShip);
            return;
        }

        //if the placement is valid we place the ship horizontally and save it's coordinates
        for (int i = 0; i < sizeOfShip; i++)
        {
            board[y - 1][x + i - 1] = sizeOfShip;
        }
        saveShipCoordinates(shipsCoordinates, startingIndex, sizeOfBoard, sizeOfShip, x, y, s[0]);
    }
    return;
}

//the current player places all their ships on the board
void placeAllShips(int** board, int*& shipsCoordinates, int& sizeOfShipArray, int& startingIndex, int& sizeOfBoard, int& cruisers, int& submarines, int& battleships, int& carriers, int& allFields, const int& player)
{

    //the current player starts placing his ships until there are none left
    int cruisers1 = cruisers, submarines1 = submarines, battleships1 = battleships, carriers1 = carriers;
    if (cruisers != 0)
    {
        cout << "Place cruisers:" << " " << cruisers1 << " " << "left" << endl;
    }
    for (int i = 0; i < cruisers; i++)
    {

        //if the current ship can be placed the player proceeds to place it
        if (canPlaceShip(board, sizeOfBoard, 2))
        {
            placeShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, 2);
            cruisers1--;
            printBoard(board, sizeOfBoard);
            if (cruisers1 != 0)
            {
                cout << "Place cruisers:" << " " << cruisers1 << " " << "left" << endl;
            }
        }

        //if the current ship can not be placed we either return to choosing the number of ships if it was player1's turn to not get softlocked or we start the placing procedure again if it was player2's turn
        else
        {
            cout << "Cannot place this ship!" << endl;
            for (int i = 0; i < sizeOfBoard; i++)
            {
                for (int j = 0; j < sizeOfBoard; j++)
                {
                    board[i][j] = 0;
                }
            }
            if (player == 1)
            {
                cout << "Returning to choosing number of ships; " << endl;
                chooseNumberOfShips(cruisers, submarines, battleships, carriers, sizeOfBoard, allFields);
                sizeOfShipArray = allFields + cruisers + submarines + battleships + carriers;
                delete[] shipsCoordinates;
                int* shipsCoordinates = new int[sizeOfShipArray];
                printBoard(board, sizeOfBoard);
                cout << "Payer" << player << "'s turn" << endl;
                placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
                return;
            }
            printBoard(board, sizeOfBoard);
            cout << "Payer" << player << "'s turn" << endl;
            placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
            return;
        }
    }
    if (submarines != 0)
    {
        cout << "Place submarines:" << " " << submarines1 << " " << "left" << endl;
    }
    for (int i = 0; i < submarines; i++)
    {
        if (canPlaceShip(board, sizeOfBoard, 3))
        {
            placeShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, 3);
            submarines1--;
            printBoard(board, sizeOfBoard);
            if (submarines1 != 0)
            {
                cout << "Place submarines:" << " " << submarines1 << " " << "left" << endl;
            }
        }
        else
        {
            cout << "Cannot place this ship! Returning to choosing number of ships;" << endl;
            for (int i = 0; i < sizeOfBoard; i++)
            {
                for (int j = 0; j < sizeOfBoard; j++)
                {
                    board[i][j] = 0;
                }
            }
            if (player == 1)
            {
                chooseNumberOfShips(cruisers, submarines, battleships, carriers, sizeOfBoard, allFields);
                sizeOfShipArray = allFields + cruisers + submarines + battleships + carriers;
                delete[] shipsCoordinates;
                int* shipsCoordinates = new int[sizeOfShipArray];
                printBoard(board, sizeOfBoard);
                cout << "Payer" << player << "'s turn" << endl;
                placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
                return;
            }
            printBoard(board, sizeOfBoard);
            cout << "Payer" << player << "'s turn" << endl;
            placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
            return;
        }
    }
    if (battleships != 0)
    {
        cout << "Place battleships:" << " " << battleships1 << " " << "left" << endl;
    }
    for (int i = 0; i < battleships; i++)
    {
        if (canPlaceShip(board, sizeOfBoard, 4))
        {
            placeShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, 4);
            battleships1--;
            printBoard(board, sizeOfBoard);
            if (battleships1 != 0)
            {
                cout << "Place battleships:" << " " << battleships1 << " " << "left" << endl;
            }
        }
        else
        {
            cout << "Cannot place this ship! Returning to choosing number of ships;" << endl;
            for (int i = 0; i < sizeOfBoard; i++)
            {
                for (int j = 0; j < sizeOfBoard; j++)
                {
                    board[i][j] = 0;
                }
            }
            if (player == 1)
            {
                chooseNumberOfShips(cruisers, submarines, battleships, carriers, sizeOfBoard, allFields);
                sizeOfShipArray = allFields + cruisers + submarines + battleships + carriers;
                delete[] shipsCoordinates;
                int* shipsCoordinates = new int[sizeOfShipArray];
                printBoard(board, sizeOfBoard);
                cout << "Payer" << player << "'s turn" << endl;
                placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
                return;
            }
            printBoard(board, sizeOfBoard);
            cout << "Payer" << player << "'s turn" << endl;
            placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
            return;
        }
    }
    if (carriers != 0)
    {
        cout << "Place carriers:" << " " << carriers1 << " " << "left" << endl;
    }
    for (int i = 0; i < carriers; i++)
    {
        if (canPlaceShip(board, sizeOfBoard, 5))
        {
            placeShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, 5);
            carriers1--;
            printBoard(board, sizeOfBoard);
            if (carriers1 != 0)
            {
                cout << "Place carriers:" << " " << carriers1 << " " << "left" << endl;
            }
        }
        else
        {
            cout << "Cannot place this ship! Returning to choosing number of ships;" << endl;
            for (int i = 0; i < sizeOfBoard; i++)
            {
                for (int j = 0; j < sizeOfBoard; j++)
                {
                    board[i][j] = 0;
                }
            }
            if (player == 1)
            {
                chooseNumberOfShips(cruisers, submarines, battleships, carriers, sizeOfBoard, allFields);
                sizeOfShipArray = allFields + cruisers + submarines + battleships + carriers;
                delete[] shipsCoordinates;
                int* shipsCoordinates = new int[sizeOfShipArray];
                printBoard(board, sizeOfBoard);
                cout << "Payer" << player << "'s turn" << endl;
                placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
                return;
            }
            printBoard(board, sizeOfBoard);
            cout << "Payer" << player << "'s turn" << endl;
            placeAllShips(board, shipsCoordinates, sizeOfShipArray, startingIndex, sizeOfBoard, cruisers, submarines, battleships, carriers, allFields, player);
            return;
        }
    }
}

//uses the saved coordinates of the player's ship to check if a ship has been flooded
bool checkFloodedShip(int*& shipsCoordinates, const int& sizeOfShipArray)
{
    int count = 0;
    for (int i = 0; i < sizeOfShipArray; i++)
    {
        if (shipsCoordinates[i] == 0)
        {

            //if we reached a zero we check all the array elements until we get another 0
            int j = i + 1;
            while (shipsCoordinates[j] != 0)
            {

                //if we get an element different from -1 our count goes up
                if (shipsCoordinates[j] != -1)
                {
                    count++;
                }
                j++;
            }

            //if the count is 0 and we have checked at least 2 elements it means there has been a flooded ship
            if (count == 0 && j != i + 1)
            {
                j = i + 1;
                while (shipsCoordinates[j] != 0)
                {
                    shipsCoordinates[j] = 0;
                    j++;
                }
                return 1;
            }
            count = 0;
        }

        //we check if the first save ship has been flooded since our array doenst start with 0
        if (i == 0 && shipsCoordinates[i] == -1)
        {
            int j = i;
            while (shipsCoordinates[j] != 0)
            {
                if (shipsCoordinates[j] != -1)
                {
                    count++;
                }
                j++;
            }
            if (count == 0)
            {
                j = i;
                while (shipsCoordinates[j] != 0)
                {
                    shipsCoordinates[j] = 0;
                    j++;
                }
                return 1;
            }
            count = 0;
        }
    }
    return 0;
}

//the current player attacks a field on the enemy board
void attackField(int** playerBoard, int** visualBoard, int*& shipsCoordinates, const int& sizeOfShipArray, const int& sizeOfBoard, const int& player, int& allFields)
{
    cout << "Player" << player << " " << "chooses a field to attack. Enter x coordiantes:";
    int x, y;

    //validates that the coordinates are numbers
    x = insertOnlyNumber2();
    cout << "Enter y coordinates:";
    y = insertOnlyNumber2();

    //validates that the field is on the board
    if ((x - 1) >= sizeOfBoard || (x - 1) < 0 || (y - 1) >= sizeOfBoard || (y - 1) < 0)
    {
        cout << "Field is not on board!" << endl;
        attackField(playerBoard, visualBoard, shipsCoordinates, sizeOfShipArray, sizeOfBoard, player, allFields);
        return;
    }

    //checks if the field has already been shot
    if (visualBoard[y - 1][x - 1] == 1 || visualBoard[y - 1][x - 1] == -1)
    {
        cout << "Field already hit!" << endl;
        attackField(playerBoard, visualBoard, shipsCoordinates, sizeOfShipArray, sizeOfBoard, player, allFields);
        return;
    }

    //checks if ship has been hit or flooded
    if (playerBoard[y - 1][x - 1] != 0)
    {
        allFields--;
        visualBoard[y - 1][x - 1] = 1;
        for (int i = 0; i < sizeOfShipArray; i++)
        {
            if (shipsCoordinates[i] == (y - 1) * sizeOfBoard + x)
            {
                shipsCoordinates[i] = -1;
            }
        }
        if (checkFloodedShip(shipsCoordinates, sizeOfShipArray) == 1)
        {
            cout << "Ship flooded!" << endl;
            return;
        }
        cout << "Ship hit!" << endl;
    }
    else
    {
        visualBoard[y - 1][x - 1] = -1;
        cout << "No ship hit" << endl;
    }
    return;
}

//computer places all his ships
void computerPlaceAllships(int** playerBoard, int** board, int*& shipsCoordinatesComputer, int*& shipsCoordinatesPlayer, int& sizeOfShipArray, int& startingIndex, int& sizeOfBoard)
{
    for (int i = 0; i < sizeOfBoard; i++) 
    {
        for (int j = i; j < sizeOfBoard; j++) 
        {
            board[i][j] = playerBoard[j][i];
        }
    }
    for (int i = 0; i < sizeOfShipArray; i++)
    {
        if (shipsCoordinatesPlayer[i] != 0)
        {
            int x, y;
            x = shipsCoordinatesPlayer[i] % sizeOfBoard;
            y = (shipsCoordinatesPlayer[i] - x) / sizeOfBoard;
            shipsCoordinatesComputer[i] = x * sizeOfBoard + y;
        }
        else
        {
            shipsCoordinatesComputer[i] = 0;
        }
    }
}




void computerAttackField(int** playerBoard, int** visualBoard, int*& shipsCoordinates, const int& sizeOfShipArray, const int& sizeOfBoard, const int& player, int& allFields)
{
    bool check = 0;
    int count = 0;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            if (visualBoard[i][j] == 1)
            {
                check = 1;
                count++;
            }
        }
    }
    if (check == 1)
    {
        for (int i = 0; i < sizeOfBoard; i++)
        {
            for (int j = 0; j < sizeOfBoard; j++)
            {
                if (visualBoard[i][j] == 1)
                {
                    if (i > 0)
                    {
                        if (visualBoard[i - 1][j] == 0)
                        {
                            if (playerBoard[i - 1][j] != 0)
                            {
                                visualBoard[i - 1][j] = 1;
                                if (checkFloodedShip(shipsCoordinates, sizeOfShipArray) == 1)
                                {
                                    cout << "Ship flooded!" << endl;
                                }
                                else
                                {
                                    cout << "Ship hit!" << endl;
                                }
                            }
                            else
                            {
                                visualBoard[i - 1][j] = -1;
                                cout << "Ship missed!" << endl;
                            }
                            return;
                        }
                    }
                    if (j > 0)
                    {
                        if (visualBoard[i][j - 1] == 0)
                        {
                            if (playerBoard[i][j - 1] != 0)
                            {
                                visualBoard[i][j - 1] = 1;
                                if (checkFloodedShip(shipsCoordinates, sizeOfShipArray) == 1)
                                {
                                    cout << "Ship flooded!" << endl;
                                }
                                else
                                {
                                    cout << "Ship hit!" << endl;
                                }
                            }
                            else
                            {
                                visualBoard[i][j - 1] = -1;
                                cout << "Ship missed!" << endl;
                            }
                            return;
                        }
                    }
                    if (i < sizeOfBoard - 1)
                    {
                        if (visualBoard[i + 1][j] == 0)
                        {
                            if (playerBoard[i + 1][j] != 0)
                            {
                                visualBoard[i + 1][j] = 1;
                                if (checkFloodedShip(shipsCoordinates, sizeOfShipArray) == 1)
                                {
                                    cout << "Ship flooded!" << endl;
                                }
                                else
                                {
                                    cout << "Ship hit!" << endl;
                                }
                            }
                            else
                            {
                                visualBoard[i + 1][j] = -1;
                                cout << "Ship missed!" << endl;
                            }
                            return;
                        }
                    }
                    if (j < sizeOfBoard - 1)
                    {
                        if (visualBoard[i][j + 1] == 0)
                        {
                            if (playerBoard[i][j + 1] != 0)
                            {
                                visualBoard[i][j + 1] = 1;
                                if (checkFloodedShip(shipsCoordinates, sizeOfShipArray) == 1)
                                {
                                    cout << "Ship flooded!" << endl;
                                }
                                else
                                {
                                    cout << "Ship hit!" << endl;
                                }
                            }
                            else
                            {
                                visualBoard[i][j + 1] = -1;
                                cout << "Ship missed!" << endl;
                            }
                            return;
                        }
                    }
                }
            }
        }

    }
    else
    {
        srand(time(NULL));
        int x, y;
        x = rand() % sizeOfBoard;
        y = rand() % sizeOfBoard;
        while (visualBoard[x][y] != 0)
        {
            x = rand() % sizeOfBoard;
            y = rand() % sizeOfBoard;
        }
        if (playerBoard[x][y] != 0)
        {
            visualBoard[x][y] = 1;
            if (checkFloodedShip(shipsCoordinates, sizeOfShipArray) == 1)
            {
                cout << "Ship flooded!" << endl;
            }
            else
            {
                cout << "Ship hit!" << endl;
            }
        }
        else
        {
            visualBoard[x][y] = -1;
            cout << "Ship missed!" << endl;
        }
        return;
    }
}

void fileOutput(int**& board1, int**& board2, int**& playerBoard1, int**& playerBoard2, int*& ships1Coordiantes, int*& ships2Coordiantes, int& sizeOfBoard, int& sizeOfShipArray, int& turn, int& allFields1, int& allFields2)
{
    ifstream from("saveBoard.txt");
    from >> allFields1;
    from >> allFields2;
    from >> sizeOfShipArray;
    from >> sizeOfBoard;
    from >> turn;
    delete[] board1;
    delete[] board2;
    delete[] playerBoard1;
    delete[] playerBoard2;
    delete[] ships1Coordiantes;
    delete[] ships2Coordiantes;
    board1 = new int* [sizeOfBoard];
    board2 = new int* [sizeOfBoard];
    playerBoard1 = new int* [sizeOfBoard];
    playerBoard2 = new int* [sizeOfBoard];
    ships1Coordiantes = new int[sizeOfShipArray];
    ships2Coordiantes = new int[sizeOfShipArray];
    for (int i = 0; i < sizeOfBoard; i++)
    {
        board1[i] = new int[sizeOfBoard];
        board2[i] = new int[sizeOfBoard];
        playerBoard1[i] = new int[sizeOfBoard];
        playerBoard2[i] = new int[sizeOfBoard];
        for (int j = 0; j < sizeOfBoard; j++)
        {
            from >> board1[i][j];
        }
    }
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            from >> board2[i][j];
        }
    }
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            from >> playerBoard1[i][j];
        }
    }
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            from >> playerBoard2[i][j];
        }
    }
    for (int i = 0; i < sizeOfShipArray; i++)
    {
        from >> ships1Coordiantes[i];
    }
    for (int i = 0; i < sizeOfShipArray; i++)
    {
        from >> ships2Coordiantes[i];
    }
}

void fileInput(int** board1, int** board2, int** playerBoard1, int** playerBoard2, int* ships1Coordiantes, int* ships2Coordiantes, const int& sizeOfBoard, const int& sizeOfShipArray, int& turn, int& allFields1, int& allFields2)
{
    ofstream too("saveBoard.txt");
    too << allFields1 << " ";
    too << allFields2 << " ";
    too << sizeOfShipArray << " ";
    too << sizeOfBoard << " ";
    too << turn << " " << endl;
    too << endl;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            too << board1[i][j];
            if (j != sizeOfBoard - 1)
            {
                too << " ";
            }
        }
        too << endl;
    }
    too << endl;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            too << board2[i][j];
            if (j != sizeOfBoard - 1)
            {
                too << " ";
            }
        }
        too << endl;
    }
    too << endl;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            too << playerBoard1[i][j];
            if (j != sizeOfBoard - 1)
            {
                too << " ";
            }
        }
        too << endl;
    }
    too << endl;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            too << playerBoard2[i][j];
            if (j != sizeOfBoard - 1)
            {
                too << " ";
            }
        }
        too << endl;
    }
    too << endl;
    for (int i = 0; i < sizeOfShipArray; i++)
    {
        too << ships1Coordiantes[i] << " ";
    }
    too << endl;
    for (int i = 0; i < sizeOfShipArray; i++)
    {
        too << ships2Coordiantes[i] << " ";
    }

}

int main()
{
    cout << "Wanna continue from save?";
    int start;
    start = insertOnlyNumber2();
    if (start == 1)
    {
        int n, turn, sizeOfShipArray, allFields1, allFields2;
        int* ships1Coordinates = new int[1];
        int* ships2Coordinates = new int[1];

        //player boards are where the players store their ships and the neutral boards are the boards being shown when the game begins
        int** player1Board = new int* [1];
        int** player2Board = new int* [1];
        int** neutralBoard1 = new int* [1];
        int** neutralBoard2 = new int* [1];
        fileOutput(neutralBoard1, neutralBoard2, player1Board, player2Board, ships1Coordinates, ships2Coordinates, n, sizeOfShipArray, turn, allFields1, allFields2);

        cout << "Choose game mode: vs player(p) or vs computer(c)";
        char s[2];
        cin >> s;
        while ((s[0] != 'p' && s[0] != 'c') || s[1] != '\0')
        {
            cout << "Not a valid gamemode!" << endl << "Choose game mode: vs player(p) or vs computer(c)";
            cin >> s;
        }
        if (s[0] == 'p')
        {
            while (allFields1 != 0 && allFields2 != 0)
            {
                printBoard(neutralBoard1, n);
                printBoard(neutralBoard2, n);

                //on odd the turns player1 attacks and on even tursn player2 attacks
                if (turn % 2 == 1)
                {
                    attackField(player2Board, neutralBoard2, ships2Coordinates, sizeOfShipArray, n, 1, allFields2);
                }
                else
                {
                    attackField(player1Board, neutralBoard1, ships1Coordinates, sizeOfShipArray, n, 2, allFields1);
                }
                turn++;
                fileInput(neutralBoard1, neutralBoard2, player1Board, player2Board, ships1Coordinates, ships2Coordinates, n, sizeOfShipArray, turn, allFields1, allFields2);
            }
            cout << "Game Over!" << endl;
            printBoard(neutralBoard1, n);
            printBoard(neutralBoard2, n);

            //checks which player has won
            if (allFields2 == 0)
            {
                cout << "Player1 wins!" << endl;
            }
            else
            {
                cout << "Player2 wins!" << endl;
            }
        }
        else//gamemode vs computer
        {
            while (allFields1 != 0 && allFields2 != 0)
            {
                printBoard(neutralBoard1, n);
                printBoard(neutralBoard2, n);

                //on odd the turns player1 attacks and on even tursn player2 attacks
                if (turn % 2 == 1)
                {
                    attackField(player2Board, neutralBoard2, ships2Coordinates, sizeOfShipArray, n, 1, allFields2);
                }
                else
                {
                    computerAttackField(player1Board, neutralBoard1, ships1Coordinates, sizeOfShipArray, n, 2, allFields1);
                }
                turn++;
                fileInput(neutralBoard1, neutralBoard2, player1Board, player2Board, ships1Coordinates, ships2Coordinates, n, sizeOfShipArray, turn, allFields1, allFields2);
            }
            cout << "Game Over!" << endl;
            printBoard(neutralBoard1, n);
            printBoard(neutralBoard2, n);

            //checks which player has won
            if (allFields2 == 0)
            {
                cout << "Player1 wins!" << endl;
            }
            else
            {
                cout << "Computer wins!" << endl;
            }
        }
        for (int i = 0; i < n; i++)
        {
            delete[] player1Board[i];
            delete[] player2Board[i];
            delete[] neutralBoard1[i];
            delete[] neutralBoard2[i];
        }
        delete[] player1Board;
        delete[] player2Board;
        delete[] neutralBoard1;
        delete[] neutralBoard2;
        delete[] ships1Coordinates;
        delete[] ships2Coordinates;
        return 0;
    }
    if (start == 0)
    {
        int n, turn = 1;
        int cruisers = 0, submarines = 0, battleships = 0, carriers = 0, allFields, sizeOfShipArray;

        //player boards are where the players store their ships and the neutral boards are the boards being shown when the game begins

        cout << "Enter board size:";

        //validates that n is a number
        n = insertOnlyNumber2();

        //validates that the board size will have place for carriers
        while (n < 5)
        {
            cout << "Board must be 5x5 or more!" << endl << "Enter board size:";
            n = insertOnlyNumber2();
        }
        int** player1Board = new int* [n];
        int** player2Board = new int* [n];
        int** neutralBoard1 = new int* [n];
        int** neutralBoard2 = new int* [n];
        for (int i = 0; i < n; i++)
        {
            player1Board[i] = new int[n];
            player2Board[i] = new int[n];
            neutralBoard1[i] = new int[n];
            neutralBoard2[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                player1Board[i][j] = 0;
                player2Board[i][j] = 0;
                neutralBoard1[i][j] = 0;
                neutralBoard2[i][j] = 0;
            }
        }
        printBoard(neutralBoard1, n);

        //we declare and choose the number of ships the game will be played with
        chooseNumberOfShips(cruisers, submarines, battleships, carriers, n, allFields);
        sizeOfShipArray = allFields + cruisers + submarines + battleships + carriers;
        int* ships1Coordinates = new int[sizeOfShipArray];
        int* ships2Coordinates = new int[sizeOfShipArray];
        cout << "Choose game mode: vs player(p) or vs computer(c)";
        char s[2];
        cin >> s;
        while ((s[0] != 'p' && s[0] != 'c') || s[1] != '\0')
        {
            cout << "Not a valid gamemode!" << endl << "Choose game mode: vs player(p) or vs computer(c)";
            cin >> s;
        }
        if (s[0] == 'p')//gamemode player vs player has been chosen
        {
            printBoard(player1Board, n);
            cout << "Payer1's turn" << endl;
            int startingIndex = 0;
            placeAllShips(player1Board, ships1Coordinates, sizeOfShipArray, startingIndex, n, cruisers, submarines, battleships, carriers, allFields, 1);
            printBoard(player2Board, n);
            cout << "Payer2's turn" << endl;
            startingIndex = 0;
            placeAllShips(player2Board, ships2Coordinates, sizeOfShipArray, startingIndex, n, cruisers, submarines, battleships, carriers, allFields, 2);
            cout << "Game begins!" << endl;

            //until every ship field has been shot the game continues
            int allFields1 = allFields;
            int allFields2 = allFields;
            while (allFields1 != 0 && allFields2 != 0)
            {
                printBoard(neutralBoard1, n);
                printBoard(neutralBoard2, n);

                //on odd the turns player1 attacks and on even tursn player2 attacks
                if (turn % 2 == 1)
                {
                    attackField(player2Board, neutralBoard2, ships2Coordinates, sizeOfShipArray, n, 1, allFields2);
                }
                else
                {
                    attackField(player1Board, neutralBoard1, ships1Coordinates, sizeOfShipArray, n, 2, allFields1);
                }
                turn++;
                fileInput(neutralBoard1, neutralBoard2, player1Board, player2Board, ships1Coordinates, ships2Coordinates, n, sizeOfShipArray, turn, allFields1, allFields2);
            }
            cout << "Game Over!" << endl;
            printBoard(neutralBoard1, n);
            printBoard(neutralBoard2, n);

            //checks which player has won
            if (allFields2 == 0)
            {
                cout << "Player1 wins!" << endl;
            }
            else
            {
                cout << "Player2 wins!" << endl;
            }
        }
        else//gamemode player vs computer has been chosen
        {
            printBoard(player1Board, n);
            cout << "Payer1's turn" << endl;
            int startingIndex = 0;
            placeAllShips(player1Board, ships1Coordinates, sizeOfShipArray, startingIndex, n, cruisers, submarines, battleships, carriers, allFields, 1);
            computerPlaceAllships(player1Board, player2Board, ships2Coordinates, ships1Coordinates, sizeOfShipArray, startingIndex, n);
            cout << "Game begins!" << endl;
            int allFields1 = allFields;
            int allFields2 = allFields;
            while (allFields1 != 0 && allFields2 != 0)
            {
                printBoard(neutralBoard1, n);
                printBoard(neutralBoard2, n);

                //on odd the turns player1 attacks and on even tursn player2 attacks
                if (turn % 2 == 1)
                {
                    attackField(player2Board, neutralBoard2, ships2Coordinates, sizeOfShipArray, n, 1, allFields2);
                }
                else
                {
                    computerAttackField(player1Board, neutralBoard1, ships1Coordinates, sizeOfShipArray, n, 2, allFields1);
                }
                turn++;
                fileInput(neutralBoard1, neutralBoard2, player1Board, player2Board, ships1Coordinates, ships2Coordinates, n, sizeOfShipArray, turn, allFields1, allFields2);
            }
            cout << "Game Over!" << endl;
            printBoard(neutralBoard1, n);
            printBoard(neutralBoard2, n);

            //checks which player has won
            if (allFields2 == 0)
            {
                cout << "Player1 wins!" << endl;
            }
            else
            {
                cout << "Computer wins!" << endl;
            }
        }

        //delete all boards and arrays
        for (int i = 0; i < n; i++)
        {
            delete[] player1Board[i];
            delete[] player2Board[i];
            delete[] neutralBoard1[i];
            delete[] neutralBoard2[i];
        }
        delete[] player1Board;
        delete[] player2Board;
        delete[] neutralBoard1;
        delete[] neutralBoard2;
        delete[] ships1Coordinates;
        delete[] ships2Coordinates;
        return 0;
    }
    return 0;
}
