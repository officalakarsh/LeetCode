/**
 * @param {Object|Array} obj
 * @return {Object|Array}
 */
var compactObject = function(obj) {
    if (obj === null || typeof obj !== 'object') {
        return Boolean(obj) ? obj : null;
    }

    if (Array.isArray(obj)) {
        const result = [];
        for (let val of obj) {
            const compacted = compactObject(val);
            if (Boolean(compacted)) result.push(compacted);
        }
        return result;
    }
    const result = {};
    for (let key in obj) {
        const compacted = compactObject(obj[key]);
        if (Boolean(compacted)) {
            result[key] = compacted;
        }
    }
    return result;
};
