//
//  canvas.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef canvas_h
#define canvas_h

using namespace std;

enum Difficulty
{
    Easy,
    Medium,
    Hard,
    Paranoid
};

class Canvas
{
private:
    Difficulty difficulty;
    int strikes;
    int stage = 0;
    vector<vector<string>> graph;
public:
    Canvas(Difficulty difficulty = Easy)
    {
        this->difficulty = difficulty;
        switch (difficulty) {
            case Easy:
                strikes = 12;
                graph = {
                    {"         \n         \n         \n         \n         \n         \n"},
                    {"         \n         \n         \n         \n         \n===      \n"},
                    {"         \n |       \n |       \n |       \n |       \n===      \n"},
                    {" +-----+ \n |       \n |       \n |       \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |       \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |     O \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===   /  \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===   / \\\n"},
                    {" +-----+ \n |    \\O/\n |     | \n |    / \\\n |       \n===      \n"},
                    {" +-----+ \n |     X \n |    /|\\\n |    / \\\n |       \n===      \n"}
                };
                break;
            case Medium:
                strikes = 9;
                graph = {
                    {"         \n         \n         \n         \n         \n         \n"},
                    {"         \n         \n         \n         \n         \n===      \n"},
                    {"         \n |       \n |       \n |       \n |       \n===      \n"},
                    {" +-----+ \n |       \n |       \n |       \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |       \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===   / \\\n"},
                    {" +-----+ \n |    \\O/\n |     | \n |    / \\\n |       \n===      \n"},
                    {" +-----+ \n |     X \n |    /|\\\n |    / \\\n |       \n===      \n"}
                };
                break;
            case Hard:
                strikes = 6;
                graph = {
                    {"         \n         \n         \n         \n         \n         \n"},
                    {" +-----+ \n |     | \n |     | \n |       \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===   / \\\n"},
                    {" +-----+ \n |    \\O/\n |     | \n |    / \\\n |       \n===      \n"},
                    {" +-----+ \n |     X \n |    /|\\\n |    / \\\n |       \n===      \n"}
                };
                break;
            case Paranoid:
                strikes = 4;
                graph = {
                    {"         \n         \n         \n         \n         \n         \n"},
                    {" +-----+ \n |     | \n |     | \n |       \n |       \n===      \n"},
                    {" +-----+ \n |     | \n |     | \n |    \\O/\n |     | \n===   / \\\n"},
                    {" +-----+ \n |    \\O/\n |     | \n |    / \\\n |       \n===      \n"},
                    {" +-----+ \n |     X \n |    /|\\\n |    / \\\n |       \n===      \n"}
                };
                break;
            default:
                break;
        }
    }
    
    void print()
    {
        if (stage != 0)
            cout << graph[stage][0];
    }
    
    bool setStage(int num)
    {
        if (num > graph.size()) return false;
        stage = num;
        return true;
    }
    
    int attemptsLeft()
    {
        return strikes - stage;
    }
    
    /// Adds a strike. Returns `true` if total strike exceeds limit.
    bool strike()
    {
        stage++;
        return stage >= strikes;
    }
    
    Difficulty getDifficulty()
    {
        return difficulty;
    }
};

#endif /* canvas_h */
