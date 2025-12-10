flowchart TD
    Start([開始 Start]) --> Init[初始化 Agents & 設定 Seed]
    
    subgraph Base_Workflow [Base Workflow (嘗試 1)]
        direction TB
        BaseDraft[DraftAgent<br/>(初稿生成)] --> BaseRefine[RefinementAgent<br/>(優化翻譯)]
        BaseRefine --> BaseEval[EvalScoreAgent<br/>(評估與打分)]
    end
    
    Init --> BaseDraft
    BaseEval --> CheckBase{總分 >= 門檻?}
    
    CheckBase -- 是 (Pass) --> EndSuccess([結束: 返回最終翻譯])
    CheckBase -- 否 (Fail) --> PrepComplex[記錄評語與失敗翻譯<br/>準備進入 Complex Loop]
    
    subgraph Complex_Workflow [Complex Workflow (最多循環 3 次)]
        direction TB
        PrepComplex --> CheckFirstLoop{是否為<br/>第 1 次循環?}
        
        CheckFirstLoop -- 是 --> RunResearch[ResearchAgent<br/>(搜尋背景知識)]
        RunResearch --> RunContext[ContextAgent<br/>(上下文分析)]
        RunContext --> ComplexDraft
        
        CheckFirstLoop -- 否 (使用現有資料) --> ComplexDraft[DraftAgent<br/>(帶入 Research/Context)]
        
        ComplexDraft --> ComplexRefine[RefinementAgent<br/>(帶入上一輪 Feedback)]
        ComplexRefine --> ComplexEval[EvalScoreAgent<br/>(評估與打分)]
        
        ComplexEval --> UpdateBest[更新最佳成績<br/>(Best Score So Far)]
        UpdateBest --> CheckComplex{總分 >= 門檻?}
    end
    
    CheckComplex -- 是 (Pass) --> EndSuccess
    CheckComplex -- 否 (Fail) --> CheckMaxLoops{是否達到<br/>最大循環次數?}
    
    CheckMaxLoops -- 否 --> UpdateFeedback[更新 Feedback:<br/>包含本次失敗翻譯與評語]
    UpdateFeedback --> ComplexDraft
    
    CheckMaxLoops -- 是 --> EndBestEffort([結束: 返回歷史最高分翻譯<br/>(Best Effort)])

    style Start fill:#f9f,stroke:#333,stroke-width:2px
    style EndSuccess fill:#9f9,stroke:#333,stroke-width:2px
    style EndBestEffort fill:#ff9,stroke:#333,stroke-width:2px
    style CheckBase fill:#ccf,stroke:#333,stroke-width:2px
    style CheckComplex fill:#ccf,stroke:#333,stroke-width:2px
