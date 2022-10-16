----------------------------------------------------------------------
--| * Saver.lua *
----------------------------------------------------------------------

Saver = {}

function Saver.save(Path, Location)
	local File = io.open("Save", "w+")
	if not File then
		GT_LOG(PR_WARNING, "Couldn't open <Save> file")
		return
	end

	File:write(string.format("return { Path = \"%s\", Location = %d }\n", Path, Location))
	File:close()
end

function Saver.delete()
	os.remove("Save")
end

function Saver.hasSave()
	local Test = io.open("Save", "r")
	if Test then
		Test:close()
		return true
	end
	return false
end
