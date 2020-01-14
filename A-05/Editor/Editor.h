#pragma once

#include "Widgets/EditorUI.h"
#include "Controllers/ControllersManager.h"

#include "Documents/Document.h"
#include "EditorState.h"

class UEditor
{

public:

    UEditorUI& GetEditorUI() { return EditorUI; }

protected:

    UEditorUI EditorUI;
    UControllersManager ControllersManager {EditorUI};

    UEditorState EditorState;
    UDocument CurrentDocument;
};