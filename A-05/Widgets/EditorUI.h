#pragma once

#include "BaseClasses/Canvas.h"
#include "BaseClasses/DrawingField.h"
#include "Documents/DocumentsPanel.h"
#include "Instruments/InstrumentPanels/FigureInstrumentsPanel.h"
#include "Instruments/InstrumentPanels/PrimaryInstrumentsPanel.h"

/**
 * @brief A canvas on which draw operations are performed.
 */
class UEditorUI : public UCanvas
{

public:
    // All UI elements here please
    UDrawingField DrawingField;
    UDocumentsPanel DocumentsPanel;
    UFigureInstrumentsPanel FiguresPanel;
    UPrimaryInstrumentsPanel PrimaryInstrumentsPanel;
};