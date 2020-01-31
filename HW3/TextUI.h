#ifndef _TEXT_UI_H_
#define _TEXT_UI_H_

using namespace std;
#include <vector>

class TextUI {

public:
    TextUI();

    string MainMenu();

    void ElectionChoice();

    void RegisterCandidates();

    void Campaign();

private:
  vector<string> main_menu_;
};


#endif  // _TEXT_UI_H_
