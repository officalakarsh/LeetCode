/**
 * @param {string} corridor
 * @return {number}
 */
var numberOfWays = function(corridor) {
    const MOD = 1000000007;

    let seatCount = 0;
    for (let ch of corridor) {
        if (ch === 'S') seatCount++;
    }

    if (seatCount === 0 || seatCount % 2 !== 0) return 0;

    let ways = 1;
    let seatsInSection = 0;
    let plantCount = 0;

    for (let ch of corridor) {
        if (ch === 'S') {
            seatsInSection++;

            if (seatsInSection === 3) {
                ways = (ways * (plantCount + 1)) % MOD;
                seatsInSection = 1;
                plantCount = 0;
            }
        } else if (ch === 'P' && seatsInSection === 2) {
            plantCount++;
        }
    }

    return ways;
};
