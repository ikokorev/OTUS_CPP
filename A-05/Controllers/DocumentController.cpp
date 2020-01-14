#include "DocumentController.h"
#include "Delegates/MulticastDelegate.h"
#include <iostream>

void UDocumentController::BindToDocPanelEvents(UDocumentsPanel& DocumentsPanel)
{
    DocumentsPanel.CreateNewDocumentButton.OnButtonClicked.BindFunction(std::bind(&UDocumentController::CreateDocument, this));
    DocumentsPanel.CreateNewDocumentButton.OnButtonClicked.BindFunction(std::bind(&UDocumentController::ImportDocument, this));
}

void UDocumentController::CreateDocument()
{
    std::cout << "UDocumentController::CreateDocument()" << std::endl;
}
 
void UDocumentController::ImportDocument()
{
    std::cout << "UDocumentController::ImportDocument()" << std::endl;
}

void UDocumentController::ExportDocument()
{
}
