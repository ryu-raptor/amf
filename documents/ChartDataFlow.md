# 譜面のデータの流れ

ChartBuilder
|- NotesBuilder <- TraceBuilder

TraceBuilder -> sharedptr<vector<Trace>>
sharedptr<vector<Trace>> -> NotesBuilder -> sharedptr<vector<Note>>


