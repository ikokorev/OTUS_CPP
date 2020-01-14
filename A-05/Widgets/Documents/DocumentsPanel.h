#pragma once

#include "Widgets/BaseClasses/VerticalPanel.h"
#include "DocumentsPanelButton.h"

/**
 * @brief A panel for working with documents.
 */
class UDocumentsPanel : public UVerticalPanel
{

public:

    UDocumentsPanelButton CreateNewDocumentButton;
    UDocumentsPanelButton ImportDocumentButton;
    UDocumentsPanelButton ExportDocumentButton;
};