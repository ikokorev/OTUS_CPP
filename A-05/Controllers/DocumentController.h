#pragma once

#include "Interfaces/Controller.h"
#include "Widgets/Documents/DocumentsPanel.h"
#include <string>

/**
 * @brief A controller for work with documents.
 */
class UDocumentController : public IController
{

public:

    void BindToDocPanelEvents(UDocumentsPanel& DocumentsPanel);

    void CreateDocument();
    void ImportDocument();
    void ExportDocument();
};