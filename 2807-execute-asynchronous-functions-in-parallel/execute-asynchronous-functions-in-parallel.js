/**
 * @param {Array<Function>} functions
 * @return {Promise<any>}
 */
var promiseAll = function(functions) {
    return new Promise((resolve, reject) => {
        const results = [];
        let completed = 0;

        if (functions.length === 0) {
            resolve([]);
            return;
        }

        functions.forEach((fn, index) => {
            
            fn()
                .then(value => {
                    results[index] = value;
                    completed++;

                    if (completed === functions.length) {
                        resolve(results);
                    }
                })
                .catch(err => {
                    
                    reject(err);
                });
        });
    });
};
