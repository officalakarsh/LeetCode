/**
 * @param {Function} fn
 * @return {Function}
 */
var once = function(fn) {
    let called = false; 

    return function(...args) {
        if (!called) {
            called = true;       
            return fn(...args); 
        } else {
            return undefined;
        }
    };
};


let fn = (a, b, c) => (a + b + c);
let onceFn = once(fn);

console.log(onceFn(1, 2, 3));
console.log(onceFn(2, 3, 6));
console.log(onceFn(5, 5, 5)); 
