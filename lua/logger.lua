local exports = {}

local function info(message)
    _log_info(debug.getinfo(2).short_src .. ":" .. debug.getinfo(2).currentline .. " " .. message)
end

local function warning(message)
    _log_warning(debug.getinfo(2).short_src .. ":" .. debug.getinfo(2).currentline .. " " .. message)
end

local function error(message)
    _log_error(debug.getinfo(2).short_src .. ":" .. debug.getinfo(2).currentline .. " " .. message)
end

exports.info = info
exports.warning = warning
exports.error = error

return exports
