#pragma once

class UEditor;

class FEditorLoop
{
public:
    int PreInit(const std::string& CmdLine);
    int Init();
    
    void Update();
    void Exit();
};

