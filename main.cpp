#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enGameChoice
{
    Stone = 1, Paper = 2, Scissors = 3
};

enum enWinner
{
    Player1 = 1, Computer = 2, Draw = 3
};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;
    do
    {
        cout << "Your Choice: 1[Stone], 2[Paper], 3[Scissors]?" << endl;
        cin >> Choice;
    } while(Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if(RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch(RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
        case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player1;
}

string ChoiceName (enGameChoice Choice)
{
    string ArrGameChoices[3] = {"Stone", "Paper", "Scissors"};
    return ArrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string ArrWinnerName[3] = {"Player1", "Computer", "Draw"};
    return ArrWinnerName[Winner - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch(Winner)
    {
    case Player1:
        system("color 2F"); // Green
        break;
    case Computer:
        system("color 4F"); // Red
        break;
    default:
        system("color 6F"); // Yellow
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{

    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : " << RoundInfo.WinnerName << endl;
    cout << "__________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if(Player1WinTimes > ComputerWinTimes)
    {
        return enWinner::Player1;
    }
    else if(ComputerWinTimes > Player1WinTimes)
    {
        return enWinner::Computer;
    }
    else
    {
        return enWinner::Draw;
    }
}

short ReadHowManyRounds()
{
    short GameRounds = 1;
    do
    {
    cout << "How Many Rounds 1 to 10 ? \n";
    cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds >10);
    return GameRounds;
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for(short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound " << GameRound << " Begins:\n";
        stRoundInfo RoundInfo;
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
        if(RoundInfo.Winner == enWinner::Player1)
        {
            Player1WinTimes++;
        }
        else if(RoundInfo.Winner == enWinner::Computer)
        {
            ComputerWinTimes++;
        }
        else
        {
            DrawTimes++;
        }
        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for(int i=1; i<=NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain;
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << endl << Tabs(2) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while(PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
