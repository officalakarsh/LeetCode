/**
 * @param {number[][]} points
 * @return {number}
 */
var countTrapezoids = function(points) {
    const MOD = 1_000_000_007n;
    const yCount = new Map();

    for (let [x, y] of points) {
        yCount.set(y, (yCount.get(y) || 0n) + 1n);
    }

    const segments = [];
    for (let [y, c] of yCount) {
        if (c >= 2n) {
            segments.push([y, (c * (c - 1n) / 2n) % MOD]);
        }
    }

    // sort by y-coordinate
    segments.sort((a, b) => a[0] - b[0]);

    let prefix = 0n;
    let total = 0n;

    for (let [y, seg] of segments) {
        total = (total + seg * prefix) % MOD;
        prefix = (prefix + seg) % MOD;
    }

    return Number(total);
};
