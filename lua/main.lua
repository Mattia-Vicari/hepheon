function load()
    -- load modules
    logger = require("lua/logger")
    settings = require("lua/settings")

    -- perform setup actions
    settings.set()
end