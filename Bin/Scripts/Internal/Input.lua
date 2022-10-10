Input = {}

function Input.isKeyDown(Key)
    return isKeyDown(Key)
end

function Input.isMouseDown(Button)
    return isMouseDown(Button)
end

function Input.getMousePosition()
    return getMousePosition()
end

function Input.defaultHandle()
    -- Leave if console is shown
    if Console.isShown() then
        return
    end

    -- Stop game on escape
    if Input.isKeyDown(GTK_ESCAPE) then
        stopGame()
    end

    -- Handle Player's behaviour
    if Player and PlayerControllable then
        if Input.isKeyDown(GTK_W) then Player:pushCommand(GTC_MOVE_UP) end
        if Input.isKeyDown(GTK_A) then Player:pushCommand(GTC_MOVE_LEFT) end
        if Input.isKeyDown(GTK_S) then Player:pushCommand(GTC_MOVE_DOWN) end
        if Input.isKeyDown(GTK_D) then Player:pushCommand(GTC_MOVE_RIGHT) end

        -- Player have to press space many times to attack
        local IsSpaceDown = Input.isKeyDown(GTK_SPACE)
        if IsSpaceDown and CanAttack then
            Player:pushCommand(GTC_ATTACK)
            CanAttack = false
        elseif not IsSpaceDown then
            CanAttack = true
        end
    end
end
