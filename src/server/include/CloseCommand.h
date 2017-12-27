//
// Created by abby on 26/12/17.
//

#ifndef EX1_CLOSECOMMAND_H
#define EX1_CLOSECOMMAND_H

using namespace std;

class CloseCommand: public Command{
private:
    GameCollection *gameCollection;
public:
    CloseCommand(GameCollection *gameCollection);
    void execute(vector<string> args);
};

#endif //EX1_CLOSECOMMAND_H
