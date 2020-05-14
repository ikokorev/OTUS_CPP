#include "Editor.h"

int UEditor::Init(bool bIsProjectLoaded /* = false */)
{
    int ErrorLevel = 0;
    // ...
    InitEditorUI(!bIsProjectLoaded);
    // ...
    return ErrorLevel;
}

   void UEditor::InitEditorUI(bool bShouldShowCreateProjectDialog /*= false*/)
   {
       EditorUI.Init(bShouldShowCreateProjectDialog);
   }