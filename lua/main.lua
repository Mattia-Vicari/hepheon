
function load()
    logger = require("lua/logger")

    logger.info("Hello World from lua!")
    logger.warning("This is a warning!")
    logger.error("This is an error!")
end