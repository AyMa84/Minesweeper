#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

struct choice
{
    int row;
    int column;
};
const int MAX = 1000;
int player1s;//dont forget to reset these too
int player2s;
int coins1;
int coins2;
int total;
int totalSafe;
int choice1, choice2;
int HeadsorTails();
choice GetChoice(int, int);
void PutBombs(int, int, int);
void PutNums(int, int);
void ShowLand(int, int, int);
void ShowExtraBombs(int, int);
void Continue(int, int);
void CalculateCoins(int, int, int);
void Resetlands(int, int);
int EditShownLand(int, int, choice, char);////////////////////////////////////////////////////
int land[MAX][MAX];
int ShownLand[MAX][MAX];
int prefer;
int main() {
    do{
        int n, m,NumofBombs, NumofPlayers, s;
        char level;
        struct choice choice;
        cout <<"please enter three integers.for rows,columns and bombs in order" << endl;
        cin >> n >> m >> NumofBombs;
        while(n < 1 || m < 1 || NumofBombs > n * m || NumofBombs < 1) {
            cout <<"invalid value for rows or columns or bombs.please renter" << endl;
            cin >> n >> m >> NumofBombs;
        }
        s = NumofBombs;
        PutBombs(n, m, NumofBombs);// gets the land ready;
        cout << "which level do you want to play with? enter 'e' for easy and 'h' for hard level." << endl;
        cin >> level;
        while(level != 'e' && level != 'h') {
            cout << "valid value for level is only e or h.please renter." << endl;
            cin >> level;
        }
        cout <<"enter the number of players.only 1 or 2 is allowed." << endl;
        cin >> NumofPlayers;
        while(NumofPlayers > 2 || NumofPlayers < 1) {
            cout << "the valid value of number of players is only 1 or 2.please renter." << endl;
            cin >> NumofPlayers;
        }
        total = n * m;
        totalSafe = total - s;
        
        if(NumofPlayers == 1){//one player starts
            int being;//if its 1,means alive,alse means dead
            while(total > 0){
                CalculateCoins(1, n, m);
                choice = GetChoice(n, m);
                being = EditShownLand(n, m, choice, level);
                if(being == 1){
                    ShowLand(n, m, 1);
                }
                else {
                    cout <<"oops! you died!" << endl;
                    Continue(1, 1);
                    if(prefer == 1){
                        Resetlands(n, m);
                        player1s = 0;
                        cout <<"in case you dicided to play with another one in the next round,you will be playing as the player one." << endl;
                        break;
                    }
                    else {
                        cout <<"goodby!" <<endl;
                        return 0;
                    }
            
                }
            }
            if (total == 0) {
                coins1 += 10;
                cout <<"congrats! you won this game!"<< endl;
                cout <<"you have now" << coins1 <<" coins!" <<endl;
                Continue(1, 1);
                switch(prefer) {
                    case 1: {
                        Resetlands(n, m);
                        cout <<"in case you dicided to play with another one in the next round,you will be playing as the player one." << endl;
                        break;
                    }
                    case 2: {
                        cout <<"goodby!";
                        return 0;
                    }
                }
            }
        }  //one player ends

        else {//two players starts
            int turn, being1, being2; 
            turn = HeadsorTails();
            while(total > 0){
                struct choice choice1, choice2;
                if(turn % 2 == 0){
                    cout << "its player number one's turn." << endl;
                    CalculateCoins(1, n, m);
                    choice1 = GetChoice(n, m);
                    being1 = EditShownLand(n, m, choice1, level);
                    if(being1 == 1){
                        ShowLand(n, m, 1);
                    }
                    else {
                        cout <<"oops! player number one died!"<< endl;
                        cout << "player number two won!" << endl;
                        coins2 += 10;
                        cout <<"player number two now has" << coins2 <<"coins" << endl;
                        total = 0;
                    }
                }
                else{
                    cout << "its player number two's turn." << endl;
                    CalculateCoins(2, n, m);
                    choice2 = GetChoice(n, m);
                    being2 = EditShownLand(n, m, choice2, level);
                    if(being2 == 1){
                        ShowLand(n, m, 2);
                    }
                    else {
                        cout <<"oops!player number two died!" << endl;
                        cout <<"player number one won!" << endl;
                        coins1 += 10;
                        cout <<"player number one now has" << coins1 <<"coins" << endl;
                        total = 0;
                    }
                }
                turn++;
            }
            if(total == 0) { //round is over here technically
                if(being1 == 1 || being2 == 1) {//declares the winner if none of them opened a bomb.
                    if(being1 == 1 && being2 == 1) {
                       cout << "you both won." <<endl;
                    }
                    if(player1s > player2s) {
                       cout <<"player number one won!" << endl; 
                    }
                    if(player1s < player2s) {
                        cout <<"player number two won!" << endl;
                    }
                }
                int choice1, choice2;
                Continue(2, 1);
                Continue(2, 2);
                if (choice1 == 1 || choice2 == 1){
                    Resetlands(n, m);
                    player1s = 0;
                    player2s = 0;
                    prefer = 1;
                    if(choice1 == 1 && choice2 != 1){
                        coins2 = 0;
                        cout <<"goodby player two!" <<endl;
                    }
                    if(choice1 != 1 && choice2 == 1){
                        coins1 = coins2;
                        coins2 = 0;
                        cout <<"goodby player one!" <<endl;
                    }
                }
                else{
                    cout <<"goodby!" << endl;
                    return 0;
                }
            }
        }// two players ends
    } while(prefer == 1);
    return 0;
}
void CalculateCoins(int a, int n, int m){
    int prefer;
    cout <<"willing to be shown a bomb?enter 1 if so and any number else for no." << endl;
    cin >> prefer;
    if (a == 1){//player one
        if(prefer == 1) {
            if (coins1 >= 10) {
                coins1 -= 10;
                ShowExtraBombs(n, m);
            }
            else{
                cout <<"sorry! it seems like you dont have enough coins!come back and use this option when you won a game!" << endl;
            }
        }
    }
    else{
        if(prefer == 1) {//its player two deciding
            if (coins2 >= 10) {
                coins2 -= 10;
                ShowExtraBombs(n, m);
            }
            else{
                cout <<"sorry! it seems like you dont have enough coins!come back and use this option when you won a game!" << endl;
            }
        }       
    }
}
void Continue( int Numplayers, int Thenumofplayer){//returning 1 means continue and 2 means quit
    int a;
    cout <<"if you want to continue, enter 1, and if you dont enter 0.";
    cin >> a;
    while(a != 1 && a != 0){
        cout <<"valid value for the thing you enter is only 1 or 0.please renter." << endl;
        cin >> a;
    }
    if (Numplayers == 1){
        if(a == 1){
            prefer = 1;
        }
        else {
            prefer = 2;
        }
    }
    else{
        if(Thenumofplayer == 1){
            if(a == 1) {
                choice1 = 1;
            }
            else{
                choice1 = 2;
            }
        }
        else{
            if (a == 1) {
                choice2 = 1;
            }
            else {
                choice2 = 2;
            }
        }
    }
}    
void Resetlands(int n, int m){
    for(int i; i < n + 1; i++){
        for(int j; j < m + 1; j++){
        land[i][j] = 0;
        ShownLand[i][j] = 0;
        }
    }
}
void PutBombs(int n, int m,int NumofBombs) {
    int i, j;
    while( NumofBombs > 0){
        srand(time(0));
        i = rand() % n;
        srand(time(0));
        j = rand() % m;
        if(land[i][j] < 10){
            land[i][j] = 10;
            NumofBombs--;
            PutNums(i, j);
        }
    }
}
void ShowExtraBombs(int n, int m) {
    int i, j, times = 1;
    while(times > 0) {
        srand(time(0));
        i = rand() % n;
        srand(time(0));
        j = rand() % m;
        if(land[i][j] >= 10) {
            ShownLand[i][j] = 10;
            total--;
            times--;
        }
    }
}
void PutNums(int i, int j) {
    if(j -1 >= 0) {
        if( i - 1 >= 0) {
            land[i - 1][j - 1]++;
        }
        land[i][j - 1]++;
        land[i + 1][j - 1]++;
    }
    if(i - 1 >= 0){
        land[i - 1][j]++;
        land[i - 1][j + 1]++;
    }
    land[i + 1][j]++;
    land[i][j + 1]++;
    land[i + 1][j + 1]++;
}
choice GetChoice(int n, int m){
    choice a;
    cout <<"plese enter the rows and columns of your choice." << endl;
    cin >> a.row >> a.column;
    while( a.row > n || a.column > m || a.row < 1 || a.column < 1) {
        cout << "please enter a number between 1 and" << n <<" for row. and a number between 1 and" << m << "for column." << endl;
        cin >> a.row >> a.column;
    }
    a.row--;
    a.column--;
    return a;
}
void ShowLand(int n, int m, int who){//////////////////////////////
    ///////////////////////////////////////////////////////////////////
    for(int i = 0; i < n; i++){
        for(int s = 0; s < m; s++){
        cout <<"____";
        }
        cout << endl;
        cout <<"|";
        for(int j = 0; j < m; j++){
            if(ShownLand[i][j] == 0){
                cout <<" * |";  
            }
            if(ShownLand[i][j] >= 1 && ShownLand[i][j] <= 8) {
                cout <<" "<< ShownLand[i][j] <<" |";
            }
            if(ShownLand[i][j] == 10) {
                cout <<" F |";
                if(who == 1) {
                    player1s++;
                }
                else{
                    player2s++;
                }
            }
            if(ShownLand[i][j] == 12) {
                cout <<"   |";
            }
        }
        cout << endl;
    }
    for(int i = 0; i < m; i++) {
        cout <<"____";
    }
    cout << endl;
}
int EditShownLand(int n, int m, choice a, char hardness) {
    int t;
    char will;
    cout <<"you want to disable? enter 'y' if you do,and 'n' if you just intend to open the cell.";
    cin >> will;
    while(will != 'y' && will != 'n') {
        cout <<"please enter only y or n" << endl;
        cin >> will;
    }
    if(land[a.row][a.column] >= 10 && will == 'y'){
        ShownLand[a.row][a.column] = 10;//F should be out
        cout <<"NICE!you are safe for now!"<< endl;
        total--;
    }
    if(land[a.row][a.column] >= 10 && will == 'n') {
        cout <<"BOOOM!" <<endl;//returning 3 means that the player has lost
        return 3;
    }
    if(land[a.row][a.column] >= 1 && land[a.row][a.column] <= 8) {
        ShownLand[a.row][a.column] = land[a.row][a.column];//the number should be out
        total--;
        totalSafe--;
    }
    if(land[a.row][a.column] == 0) {
        ShownLand[a.row][a.column] = 12;//empty should be out
        total--;
        totalSafe--;
    }
    if(hardness == 'e'){
        t = 2;
    } 
    else {
        t = 1;
    }    
    if(totalSafe > 0){
        if(t > totalSafe) {
            t = totalSafe;
        }
        int i, j;
        while( t > 0){

             srand(time(0));
            i = rand() % n;
            srand(time(0));
            j = rand() % m;
            if (ShownLand[i][j] == 0) {
                if (land[i][j] == 0){
                    ShownLand[i][j] = 12;
                    totalSafe--;
                    total--;
                }
                if (land[i][j] >= 1 && land[i][j] <= 8){
                    ShownLand[i][j] = land[i][j];
                    totalSafe--;
                    total--;
                }
                if (land[i][j] >= 10){
                    t++;
                }
                t--;
            }
        }
    }
    return 1;
}
int HeadsorTails() {
    int turn;
    char ch;
    char array[] = {'h', 't'};
    cout<<"you are going to play heads or tails to dicide on who should begin!"<< endl;
    cout <<"so player number two which will you pick?enter 'h' for heads and 't' for tails." <<endl;
    cin >> ch;
    while(ch != 'h' && ch != 't') {
        cout << "please enter only h or t" <<endl;
        cin >> ch;
    }
    srand(time(0));
    turn = rand() % 2;
    if(turn == 0){
        cout <<endl;
        if(ch == 'h') {
            cout <<"player number two starts the game!" << endl;
            return 1;
        }
        else {
            cout <<"player number one starts the game!" << endl;
            return 2;
        }
    }
    else{
        if(ch == 't') {
            cout <<"player number two starts the game!" << endl;
            return 1;
        }
        else{
            cout <<"player number one starts the game!" << endl;
        }
    }
    return 2;
}