----------------------------------------------------------------------
--| * Cutscene.lua *
----------------------------------------------------------------------

Cutscene = {
    ToSkip = nil, -- TODO(sean) Implement skipping with setting this variable
    All = {},
}

function Cutscene.new(CutsceneActions, funInit, funEnd)
    local ID = #Cutscene.All + 1
    Cutscene.All[ID] = {
        Actions = CutsceneActions,
        Stage = 0,
    }

    return function(TActor)
        local Actions = Cutscene.All[ID].Actions
        local Stage = Cutscene.All[ID].Stage

        if Stage == 0 then
            funInit(TActor)
        end

        while Stage == 0 or Stage > #Actions or not Actions[Stage][2] or Actions[Stage][1]:checkCurrentTask() == GTT_DONE do
            Cutscene.All[ID].Stage = Cutscene.All[ID].Stage + 1
            Stage = Cutscene.All[ID].Stage

            if Stage > #Actions then
                funEnd(TActor)
                return
            end

            Actions[Stage][1]:pushTask(Actions[Stage][3], Actions[Stage][4], Actions[Stage][5])
        end
    end
end
