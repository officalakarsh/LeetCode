/**
 * @param {number} n
 * @param {number[]} batteries
 * @return {number}
 */
var maxRunTime = function(n, batteries) {
    batteries.sort((a, b) => a - b);
    let total = batteries.reduce((a, b) => a + b, 0);

    let left = 0, right = Math.floor(total / n);

    const canRun = (t) => {
        let power = 0;
        for (let b of batteries) {
            power += Math.min(b, t);
        }
        return power >= t * n;
    };

    while (left < right) {
        let mid = Math.floor((left + right + 1) / 2);
        if (canRun(mid)) left = mid;
        else right = mid - 1;
    }

    return left;
};
