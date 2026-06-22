#include <bits/stdc++.h>
using namespace std;

enum Symbol
{
    X,
    O,
    EMPTY
};

class Move
{
public:
    int row;
    int col;
    Symbol s;
    Move(int r, int c, Symbol sym) : row(r), col(c), s(sym) {}
};

class Player
{
public:
    virtual Move move() = 0;
    virtual string getName() = 0;
    virtual Symbol getSymbol() = 0;
    virtual ~Player() = default; // dont assign 0 to pure virtual destructor, it will force u to provide definition for it
};

class HumanPlayer : public Player
{

    string name;
    Symbol symbol;

public:
    HumanPlayer(string n, Symbol s)
    {
        name = n;
        symbol = s;
    }

    Symbol getSymbol() override
    {
        return symbol;
    }

    string getName() override
    {
        return name;
    }

    Move move() override
    {
        int r;
        int c;
        cout << "Plese enter your move: row,col" << endl;
        cin >> r >> c;
        return Move(r, c, symbol);
    }
};

class Board
{

    vector<vector<Symbol>> board;
    int row;
    int col;

public:
    Board(int r, int c)
    {
        row = r;
        col = c;
        board.resize(row, vector<Symbol>(col, EMPTY));
    }

    bool isValidMove(Move m)
    {
        int r = m.row;
        int c = m.col;
        if (r < 0 || r >= row || c < 0 || c >= col)
            return false;
        if (board[r][c] != EMPTY)
            return false;
        return true;
    }

    void makeMove(Move m)
    {
        board[m.row][m.col] = m.s;
    }

    int getRow()
    {
        return row;
    }
    int getCol()
    {
        return col;
    }

    Symbol getValue(int r, int c)
    {
        return board[r][c];
    }
    //     Q: Can we optimize to O(1)?

    // 👉 YES (very important LLD upgrade)

    // Idea:

    // Maintain counters:

    // rowCount[row][symbol]
    // colCount[col][symbol]
    // diagCount[symbol]
    // antiDiagCount[symbol]

    // Then:

    bool checkDraw()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == EMPTY)
                    return false;
            }
        }
        return true;
    }

    void display()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == X)
                    cout << "X ";
                else if (board[i][j] == O)
                    cout << "O ";
                else
                    cout << "- ";
            }
            cout << endl;
        }
    }
};

class GameEvaluatioStrategy
{
public:
    virtual bool checkWinner(Board &b, int r, int c, Symbol s) = 0;
    virtual ~GameEvaluatioStrategy() = default;
};

class StandardGameEvaluationStrategy : public GameEvaluatioStrategy
{
public:
    bool checkWinner(Board &b, int r, int c, Symbol s) override
    {
        int row = b.getRow();
        int col = b.getCol();

        {
            // row check
            int winner = 1;
            for (int j = 0; j < col; j++)
            {
                if (b.getValue(r, j) != s)
                {
                    winner = 0;
                    break;
                }
            }
            if (winner)
                return true;

            // col check
            winner = 1;
            for (int i = 0; i < row; i++)
            {
                if (b.getValue(i, c) != s)
                {
                    winner = 0;
                    break;
                }
            }
            if (winner)
                return true;

            // frwd diagonal check
            if (r == c)
            {
                winner = 1;
                for (int i = 0; i < row; i++)
                {
                    if (b.getValue(i, i) != s)
                    {
                        winner = 0;
                        break;
                    }
                }
                if (winner)
                    return true;
            }

            // bkwd diagonal check
            if ((row - 1) - c == r)
            {
                winner = 1;
                for (int j = col - 1; j >= 0; j--)
                {
                    if (b.getValue((row - 1) - j, j) != s)
                    {
                        winner = 0;
                        break;
                    }
                }
                if (winner)
                    return true;
            }

            return false;
        }
    }
};

class TicTacToe
{

    Board board;
    vector<Player *> players;
    GameEvaluatioStrategy *evaluationStrategy;
    int turn = 0;

public:
    TicTacToe(int r, int c, Player *p1, Player *p2, GameEvaluatioStrategy *strategy) : board(r, c)
    {
        players.push_back(p1);
        players.push_back(p2);
        evaluationStrategy = strategy;
    }

    void Play()
    {

        int n = players.size();

        while (true)
        {

            board.display();
            Player *currPlayer = players[turn % n];

            Move m = currPlayer->move();

            if (board.isValidMove(m))
            {
                // Make the move
                board.makeMove(m);

                if (evaluationStrategy->checkWinner(board, m.row, m.col, currPlayer->getSymbol()))
                {
                    cout << "Player " << currPlayer->getName() << " wins!" << endl;
                    break;
                }
            }
            else
            {
                cout << "Invalid move, try again" << endl;
                continue;
            }

            turn++;

            if (board.checkDraw())
            {
                cout << "It's a draw!" << endl;
                break;
            }
        }
    }
};

int main()
{

    unique_ptr<GameEvaluatioStrategy> evaluationStrategy = make_unique<StandardGameEvaluationStrategy>();
    unique_ptr<Player> p1 = make_unique<HumanPlayer>("Player 1", X);
    unique_ptr<Player> p2 = make_unique<HumanPlayer>("Player 2", O);

    TicTacToe game(3, 3, p1.get(), p2.get(), evaluationStrategy.get());
    game.Play();

    return 0;
}