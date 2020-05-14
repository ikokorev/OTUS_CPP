#include "ControllersManager.h"

UControllersManager::UControllersManager(UEditorUI& EditorUI)
{
    BindControllersToUIEvents(EditorUI);
    // BindControllerWithEditorState(EditorState);
}

void UControllersManager::BindControllersToUIEvents(UEditorUI& EditorUI)
{
    DocumentController.BindToDocPanelEvents(EditorUI.DocumentsPanel);

}