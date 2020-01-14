#include <iostream>
#include "Editor/Editor.h"

int main()
{
    UEditor MyEditor;
    MyEditor.GetEditorUI().DocumentsPanel.CreateNewDocumentButton.OnButtonClicked.Broadcast();
    MyEditor.GetEditorUI().DocumentsPanel.CreateNewDocumentButton.OnButtonClicked.Broadcast();

    return 0;
}