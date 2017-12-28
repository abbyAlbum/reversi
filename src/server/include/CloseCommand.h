//
// Created by abby on 26/12/17.
//

#ifndef EX1_CLOSECOMMAND_H
#define EX1_CLOSECOMMAND_H

using namespace std;

class CloseCommand: public Command{
private:
    GameCollection *gc;
public:
    CloseCommand();
    void execute(void *args);
};

#endif //EX1_CLOSECOMMAND_H
