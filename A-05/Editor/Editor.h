#pragma once

#include "Widgets/EditorUI.h"
#include "Controllers/ControllersManager.h"

#include "Documents/Document.h"
#include "EditorState.h"

class UEditor
{

public:

    int Init(bool bIsProjectLoaded = false);
    UEditorUI& GetEditorUI() { return EditorUI; }
    void Update() {};

protected:

    void InitEditorUI(bool bShouldShowCreateProjectDialog = false);

    UEditorUI EditorUI;
    UControllersManager ControllersManager {EditorUI};

    UEditorState EditorState;
    UDocument CurrentDocument;
};