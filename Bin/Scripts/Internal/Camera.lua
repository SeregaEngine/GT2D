Camera = {}

function Camera.attach(TEntity)
    attachCamera(TEntity.Pointer)
end

function Camera.detach()
    detachCamera()
end

function Camera.setPosition(X, Y)
    setCameraPosition(X, Y)
end

function Camera.getPosition()
    return getCameraPosition()
end

function Camera.setBounds(Rect)
    setCameraBounds(Rect[1], Rect[2], Rect[3], Rect[4])
end
