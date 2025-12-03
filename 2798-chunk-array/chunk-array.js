/**
 * @param {Array} arr
 * @param {number} size
 * @return {Array}
 */
var chunk = function(arr, size) {
    const result = [];
    for (let i = 0; i < arr.length; i += size) {
        result.push(arr.slice(i, i + size));
    }
    return result;
};
console.log(chunk([1, 2, 3, 4, 5], 2)); 
console.log(chunk([1, 2, 3, 4, 5, 6], 3)); 