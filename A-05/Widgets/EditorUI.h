#pragma once

#include "Project/ProjectActionsPanel.h"
#include "Framework/Canvas.h"
#include "Framework/DrawingField.h"
#include "Instruments/InstrumentPanels/FigureInstrumentsPanel.h"
#include "Instruments/InstrumentPanels/PrimaryInstrumentsPanel.h"

/**
 * @brief A canvas on which draw operations are performed.
 */
class UEditorUI : public UCanvas
{

public:
    void Init(bool bShouldShowCreateProjectDialog = false);
    
    UDrawingField DrawingField;
    UProjectActionsPanel ProjectActionsPanel;
    UFigureInstrumentsPanel FiguresPanel;
    UPrimaryInstrumentsPanel PrimaryInstrumentsPanel;
};