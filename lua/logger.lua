function info(message)
    c_log_info(debug.getinfo(2).short_src .. ":" .. debug.getinfo(2).currentline .. " " .. message)
end

function warning(message)
    c_log_warning(debug.getinfo(2).short_src .. ":" .. debug.getinfo(2).currentline .. " " .. message)
end

function error(message)
    c_log_error(debug.getinfo(2).short_src .. ":" .. debug.getinfo(2).currentline .. " " .. message)
end

exports = {}

exports.info = info
exports.warning = warning
exports.error = error

return exports
