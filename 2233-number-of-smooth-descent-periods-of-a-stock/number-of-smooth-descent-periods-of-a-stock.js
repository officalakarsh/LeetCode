/**
 * @param {number[]} prices
 * @return {number}
 */
var getDescentPeriods = function(prices) {
    let ans = 0;
    let curr = 0;

    for (let i = 0; i < prices.length; i++) {
        if (i > 0 && prices[i] === prices[i - 1] - 1) {
            curr += 1;
        } else {
            curr = 1;
        }
        ans += curr;
    }

    return ans;
};

