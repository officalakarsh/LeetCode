/**
 * @param {Function} fn
 * @param {Array} args
 * @param {number} t
 * @return {Function}
 */
var cancellable = function(fn, args, t) {
    
    fn(...args);

    const intervalId = setInterval(() => {
        fn(...args);
    }, t);

    return function cancelFn() {
        clearInterval(intervalId);
    };
};
