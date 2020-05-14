#include "Editor/Editor.h"
#include "Editor/EditorLoop.h"
#include <string>

UEditor GEditor;
FEditorLoop GEditorLoop;
bool GIsRequestingExit = false;
bool GIsRunning = false;

int EditorPreInit(const std::string& CmdLine)
{
    return GEditorLoop.PreInit(CmdLine);
}

int EditorInit()
{
    return GEditorLoop.Init();
}

void EditorUpdate()
{
    GEditorLoop.Update();
}

int GuardedMain(const std::string& CmdLine)
{    
    int ErrorLevel = EditorPreInit(CmdLine);

    // Exit if PreInit failed
    if (ErrorLevel != 0)
    {
        return ErrorLevel;
    }    

    ErrorLevel = EditorInit();

    while (!GIsRequestingExit)
    {
        EditorUpdate();
    }

    return ErrorLevel;
}

/* Exists only for test purposes. */
void SimulateUserActivity(UEditor& Editor)
{
    Editor.GetEditorUI().DocumentsPanel.CreateNewDocumentButton.OnButtonClicked.Broadcast();
    Editor.GetEditorUI().DocumentsPanel.CreateNewDocumentButton.OnButtonClicked.Broadcast();
}