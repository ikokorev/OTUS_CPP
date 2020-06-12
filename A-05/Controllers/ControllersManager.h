#pragma once

#include "Interfaces/Controller.h"
#include "ProjectActionsController.h"
#include "EraseController.h"
#include "FigureDrawController.h"
#include "MediatorController.h"
#include "EditorStateController.h"
#include "Widgets/EditorUI.h"

/** 
 * @brief Manager of all redactor's controllers
 */
class UControllersManager : public IController
{

public:

    UControllersManager() = default;
    UControllersManager(UEditorUI& EditorUI);

    void BindControllersToUIEvents(UEditorUI& EditorUI);

private:

    UProjectActionsController ProjectActionsController;
    UFigureDrawController FigureDrawController;  
    UEraseController EraseController;
    UEditorStateController EditorStateController;
    UMediatorController MediatorController;  
};