#include <unistd.h>
#include "Lexer.h"
#include "Parser.h"
#include "VarManager.h"
#include "Sleep.h"

int main(int, char *argv[]) {
    //creating manger that will hold all the information of the varibles
    VarManager *manager = new VarManager();
    //flag lets us know that parser keep working
    manager->flag = 1;
    Lexer *lexer = new Lexer();
    if (argv[1] == NULL) {
        cout << "filename not provided" << endl;
        return 0;
    }
    Parser *par = new Parser(lexer->readFile(argv[1]), manager);
    par->parserLexer();
    manager->flag = 0;

    delete lexer;
    delete par;
    delete manager;
}

