#include "ControllersManager.h"

UControllersManager::UControllersManager(UEditorUI& EditorUI)
{
    BindControllersToUIEvents(EditorUI);
}

void UControllersManager::BindControllersToUIEvents(UEditorUI& EditorUI)
{
    DocumentController.BindToDocPanelEvents(EditorUI.DocumentsPanel);

}