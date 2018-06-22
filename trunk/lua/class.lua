function register_parent(child, parent, parent_name)
    child[parent_name] = parent
    child.parent_table = {}
    child.parent_table[parent_name] = parent

    if parent.parent_table then
        for k,v in pairs(parent.parent_table) do
            child.parent_table[k] = v
            child[k] = v
        end
    end

    local metable = {}
    setmetatable(child,metable)
    metable.__index = parent
    metable.__newindex = parent
end
