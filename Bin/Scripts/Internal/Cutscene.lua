Cutscene = {}

function Cutscene.new(FunGetActions, FunChangeAndGetActionStage, FunInit, FunEnd)
    return function(TActor)
        if FunChangeAndGetActionStage(0) == 0 then
            FunInit(TActor)
        end

        local Actions = FunGetActions()
        local Stage = FunChangeAndGetActionStage(0)

        while Stage == 0 or Stage > #Actions or not Actions[Stage][2] or Actions[Stage][1]:checkCurrentTask() == GTT_DONE do
            Stage = FunChangeAndGetActionStage(1)

            if Stage > #Actions then
                FunEnd(TActor)
                return
            end

            Actions[Stage][1]:pushTask(Actions[Stage][3], Actions[Stage][4], Actions[Stage][5])
        end
    end
end
