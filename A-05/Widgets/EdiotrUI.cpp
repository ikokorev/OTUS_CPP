#include "EditorUI.h"
#include "EditorProjectGeneration/Widgets/CreateProjectDialog.h"

void UEditorUI::Init(bool bShouldShowCreateProjectDialog /* = false */)
{
    // ...
    if (bShouldShowCreateProjectDialog)
    {
        // Let's assume we're creating new project via special dialog window here
        UCreateProjectDialog* CreateProjectDialog = new UCreateProjectDialog();
    }
    // ...
}