#pragma once

#include "common.h"

namespace ui {

const ushort kCmdHelpAbout = 100;
const ushort kCmdProgramContentsWindow = 101;
const ushort kCmdProgramAddSubroutine = 102;
const ushort kCmdProgramAddFunction = 103;

class App : public TApplication {
   public:
    App(int argc, char** argv);
    virtual void handleEvent(TEvent& event);

   private:
    static TMenuBar* initMenuBar(TRect r);
    static TStatusLine* initStatusLine(TRect r);
    bool handleCommand(TEvent& event);
    TRect getNewWindowRect(int width, int height);
    void onFileNew();

    int _newWindowX;
    int _newWindowY;
};

}  // namespace ui
