#include "EditorLoop.h"
#include "Editor.h"
#include "Projects/ProjectManager.h"
#include "Misc/CommandLine.h"
#include "Misc/Paths.h"
#include "Misc/Parse.h"
#include "Widgets/EditorUI.h"
#include <string>
#include <iostream>

extern UEditor GEditor;
extern bool GIsRequestingExit;
extern bool GIsRunning;

bool ParseProjectPathFromCmdLine(const std::string& CmdLine, std::string& OutProjectFilePath)
{
    // This is very rough example of how we would parse project file path from cmd line args
    // and store it. I'm using std::string.c_str method just for compile compatibility.
    bool ParseResult = FParse::Command(FCommandLine::Get().c_str, "-ProjectFilePath", &OutProjectFilePath.c_str);
    if (ParseResult)
    {
        FPaths::SetProjectFilePath(OutProjectFilePath);
    }

    return ParseResult;
}

int FEditorLoop::PreInit(const std::string& CmdLine)
{
    FCommandLine::Set(CmdLine);

    std::string ProjectFilePath {""};
    if (ParseProjectPathFromCmdLine(CmdLine, ProjectFilePath))
    {
        //SetProjectName(); @todo - remove
        FProjectManager::GetInstance().LoadProjectFromFile(ProjectFilePath);
    }

    return 0;
}

int FEditorLoop::Init()
{
    GIsRunning = true;
    
    bool bIsProjectLoaded = FProjectManager::GetInstance().HasLoadedProject();
    int ErrorLevel = GEditor.Init(bIsProjectLoaded);

    return ErrorLevel;
}

void FEditorLoop::Update()
{
    // ...
    
    // main editor update
    GEditor.Update();
    
    // ...
}

void FEditorLoop::Exit()
{
    GIsRunning = false;
    GIsRequestingExit = true;
}