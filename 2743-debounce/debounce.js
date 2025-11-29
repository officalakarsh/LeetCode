/**
 * @param {Function} fn
 * @param {number} t milliseconds
 * @return {Function}
 */
var debounce = function(fn, t) {
    let timerId = null;

    return function(...args) {
        if (timerId !== null) {
            clearTimeout(timerId);
        }
        
        timerId = setTimeout(() => {
            fn(...args);
        }, t);
    };
};
