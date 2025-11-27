/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {
    const cache = new Map(); 
    return function(...args) {
        
        const key = JSON.stringify(args);

        if (cache.has(key)) {
            return cache.get(key);
        } else {
            const result = fn(...args); 
            cache.set(key, result);   
            return result;
        }
    };
}


let callCount = 0;
const memoizedFn = memoize(function(a, b) {
    callCount += 1;
    return a + b;
});

console.log(memoizedFn(2, 3));
console.log(memoizedFn(2, 3)); 
console.log(memoizedFn(3, 2)); 
console.log(callCount);
