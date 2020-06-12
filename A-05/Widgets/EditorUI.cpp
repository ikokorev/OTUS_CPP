#include "EditorUI.h"
#include "Project/ProjectDialog.h"

void UEditorUI::Init(bool bShouldShowCreateProjectDialog /* = false */)
{
    // ...
    if (bShouldShowCreateProjectDialog)
    {
        // Let's assume we're creating new project via special dialog window here
        UProjectDialog* CreateProjectDialog = new UProjectDialog();
    }
    // ...
}
