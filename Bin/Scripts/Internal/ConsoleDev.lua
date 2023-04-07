function mission(Name, Location)
    Mission.switch("Scripts/Mission" .. tostring(Name) .. ".lua", Location or 1)
end