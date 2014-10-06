-- util
util = {}

-- Benchmark
function util.Benchmark(func, _amount)
	local time_start = uptime() * 1000
	
	for index = 0, _amount or 1, 1 do
		func()
	end
	
	local time_end = uptime() * 1000
	return time_end-time_start
end

-- ACCESSOR_FUNC
function util.ACCESSOR_FUNC(meta, name, var)
	meta["Get" .. name] = function(s)
		return s[var]
	end
	meta["Set" .. name] = function(s, val)
		s[var] = val
	end
end