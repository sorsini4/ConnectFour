#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Player{
    //members of struct
    string name;
    string letter;
    int answer;
};

//function prototype
void startUpScreen(Player& playerOne, Player& playerTwo);
void isEven(bool& isEven, int& turn);
void playerChoice(Player& player);
void printBoard(vector<string>& row1, vector<string>& row2, vector<string>& row3, vector<string>& row4, vector<string>& row5, vector<string>& row6);
void playersTurn(vector<string>& row1, vector<string>& row2, vector<string>& row3, vector<string>& row4, vector<string>& row5, vector<string>& row6, Player& player);
bool boundsChecking(Player& player);
void newInputNeeded(Player& player);
bool occupiedSpace(vector<string> row6, Player& player);
bool userWon(bool& winner, vector<string>& row1, vector<string>& row2, vector<string>& row3, vector<string>& row4, vector<string>& row5, vector<string>& row6, Player& player);


int main() {
    Player playerOne = {" ", "X"};
    Player playerTwo = {" ", "O"};
    Player player;
    bool evenNum = true;
    bool winner = false;
    //Populating the vectors
    vector <string> row1 = {" | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | "};
    vector <string> row2 = {" | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | "};
    vector <string> row3 = {" | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | "};
    vector <string> row4 = {" | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | "};
    vector <string> row5 = {" | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | "};
    vector <string> row6 = {" | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | ", " ", " | "};

    startUpScreen(playerOne, playerTwo);

    /* Need to make diagonal win. */
    //Player one goes on odd player two on even
    for(int turn = 1; winner != true; turn++){
        isEven(evenNum, turn);
        if(evenNum == false){
            //player one's turn
            player = playerOne;
            printBoard(row1, row2, row3, row4, row5, row6);
            playerChoice(player);
            boundsChecking(player);
            //This while loop will make sure that if it is out of bounds then
            while(boundsChecking(player) == true){
                printBoard(row1, row2, row3, row4, row5, row6);
                newInputNeeded(player);
            }
            occupiedSpace(row6, player);
            while(occupiedSpace(row6, player) == true){
                printBoard(row1, row2, row3, row4, row5, row6);
                newInputNeeded(player);
                boundsChecking(player);
            }
            playersTurn(row1, row2, row3, row4, row5, row6, player);
            if(userWon(winner, row1, row2, row3, row4, row5, row6, player) == true){
                printBoard(row1, row2, row3, row4, row5, row6);
                cout << "Congratulations, " << player.name << " you won!" << endl;
            }
        }
        else{
            //player two's turn
            player = playerTwo;
            printBoard(row1, row2, row3, row4, row5, row6);
            playerChoice(player);
            boundsChecking(player);
            while(boundsChecking(player) == true){
                 printBoard(row1, row2, row3, row4, row5, row6);
                 newInputNeeded(player);
             }
            occupiedSpace(row6, player);
            while(occupiedSpace(row6, player) == true){
                printBoard(row1, row2, row3, row4, row5, row6);
                newInputNeeded(player);
            }
            playersTurn(row1, row2, row3, row4, row5, row6, player);
            if(userWon(winner, row1, row2, row3, row4, row5, row6, player) == true){
                printBoard(row1, row2, row3, row4, row5, row6);
                cout << "Congratulations, " << player.name << " you won!" << endl;
            }
        }
        cout << endl;
    }
    return 0;
}

//This function asks for the players names, and then puts them into the struct.
void startUpScreen(Player& playerOne, Player& playerTwo){
    cout << "********************************************" << endl;
    cout << setw(27) << "Hello players!" << endl << setw(32) << "Welcome to Connect Four." << endl;
    cout << "May the two players please enter your names, " << endl << setw(34) << "seperated by a single space." << endl;
    cout << "********************************************" << endl;
    cin >> playerOne.name;
    cin >> playerTwo.name;
}

//This function will make it so player one goes on an odd number and the even number is
//player twos turn.
void isEven(bool& evenNum, int& turn){
    if(turn % 2 != 0){
        evenNum = false;
    }
    else{
        evenNum = true;
    }
}

//This is a function that will take in the players answer as an integer, and save it to the
//player object for future use in other methods.
void playerChoice(Player& player){
    cout << player.name << ", choose where you would like to go." << endl;
    cout << "(Farthest left = 1, far right = 6)" << endl;
    cin >> player.answer;
}

//This is a for loop that will print out all of the vectors one after another to create the
//board to play on.
void printBoard(vector<string>& row1, vector<string>& row2, vector<string>& row3, vector<string>& row4, vector<string>& row5, vector<string>& row6){
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl <<
        endl;
    cout << setw(4) << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4" << setw(4) << "5" << setw(4) << "6" << endl;
    cout << "--------------------------" << endl;
    for(int i = 0; i < 13; i++){
        cout << row6.at(i);
    }
    cout << endl;
    for(int i = 0; i < 13; i++){
        cout << row5.at(i);
    }
    cout << endl;
    for(int i = 0; i < 13; i++){
        cout << row4.at(i);
    }
    cout << endl;
    for(int i = 0; i < 13; i++){
        cout << row3.at(i);
    }
    cout << endl;
    for(int i = 0; i < 13; i++){
        cout << row2.at(i);
    }
    cout << endl;
    for(int i = 0; i < 13; i++){
        cout << row1.at(i);
    }
    cout << endl;
    cout << "--------------------------" << endl;
}


//This function will take the players answer recieved in the playerChoice function, and then
//put the answer in the corresponding column with the if statements.
void playersTurn(vector<string>& row1, vector<string>& row2, vector<string>& row3, vector<string>& row4, vector<string>& row5, vector<string>& row6, Player& player){
    int index = 1;
    for(int answer = 1; answer < 7; answer++){
        if(player.answer == answer){
            if(row1.at(index) == " "){
                row1.at(index) = player.letter;
            }
            else if(row2.at(index) == " "){
                row2.at(index) = player.letter;
            }
            else if(row3.at(index) == " "){
                row3.at(index) = player.letter;
            }
            else if(row4.at(index) == " "){
                row4.at(index) = player.letter;
            }
            else if(row5.at(index) == " "){
                row5.at(index) = player.letter;
            }
            else if(row6.at(index) == " "){
                row6.at(index) = player.letter;
            }
        }
        index += 2;
    }
}

//This function will check if the players answer is out of bounds, meaning if they enter an
//answer that was larger or smaller than the respective columns 1-6.
bool boundsChecking(Player& player){
    bool outOfBounds = false;
    if(player.answer > 6 || player.answer < 1){
        outOfBounds = true;
        if(player.answer >= 1 && player.answer <= 6){
            outOfBounds = true;
        }
    }
    return outOfBounds;
}

//This function will ask the user for a valid input if they entered an out of bounds number,
//or entered a column that is already full
void newInputNeeded(Player& player){
    cout << player.name << ", please enter a valid input." << endl;
    cin >> player.answer;
}

//This function will find out if the column chosen was already completely populated or not.
bool occupiedSpace(vector<string> row6, Player& player){
    bool occupied = false;
    int index = 1;
    for(int answer = 1; answer < 7; answer++){
        if(player.answer == answer){
            if(row6.at(index) != " "){
                occupied = true;
            }
        }
        index += 2;
    }
        return occupied;
}

//This function will check for vertical, diagonal and horizontal wins for each user. Never got to diagonal win
bool userWon(bool& winner, vector<string>& row1, vector<string>& row2, vector<string>& row3, vector<string>& row4, vector<string>& row5, vector<string>& row6, Player& player){
   /* int column1 = 1;
    int column2 = 3;
    int column3 = 5;
    int column4 = 7;
    int column5 = 9;
    int column6 = 11; */
    int count = 0;
    int win = 4;

    //Checks for vertical win in all rows
    for(int i = 1; i < row1.size(); i++){
        if(row1.at(i) == player.letter){
            count++;
        }
        else{
            count = 0;
        }
        if(row2.at(i) == player.letter){
            count++;
        }
        else{
            count = 0;
        }
        if(row3.at(i) == player.letter){
            count++;
        }
        else{
            count = 0;
        }
        if(row4.at(i) == player.letter){
            count++;
        }
        else{
            count = 0;
        }
        if(row5.at(i) == player.letter){
            count++;
        }
        else{
            count = 0;
        }
        if(row6.at(i) == player.letter){
            count++;
        }
        else{
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    //Each for loop checks for the horizontal win
    for(int i = 1; i < row1.size(); i+=2){
        if(row1.at(i) == player.letter){
            count++;
        }
        if(row1.at(i) != player.letter){
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    for(int i = 1; i < row2.size(); i+=2){
        if(row2.at(i) == player.letter){
            count++;
        }
        if(row2.at(i) != player.letter){
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    for(int i = 1; i < row3.size(); i+=2){
        if(row3.at(i) == player.letter){
            count++;
        }
        if(row3.at(i) != player.letter){
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    for(int i = 1; i < row4.size(); i+=2){
        if(row4.at(i) == player.letter){
            count++;
        }
        if(row4.at(i) != player.letter){
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    for(int i = 1; i < row5.size(); i+=2){
        if(row5.at(i) == player.letter){
            count++;
        }
        if(row5.at(i) != player.letter){
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    for(int i = 1; i < row6.size(); i+=2){
        if(row6.at(i) == player.letter){
            count++;
        }
        if(row6.at(i) != player.letter){
            count = 0;
        }
        if(count == win){
            winner = true;
        }
    }
    return winner;
}
